Statement
=========

The :code:`sql::Statement` class is a wrapper around a sqlite statement object. It has methods to prepare queries, bind
parameters and retrieve results. Similar to the :code:`sql::Database`, it does not support all C API functions. Use the
:code:`get` method to retrieve the internal handle.

Preparing Statements
--------------------

Statements can be created through the :code:`createStatement` method of a database. The first parameter is the SQL query
to be executed. The second parameter indicates whether the statement should be prepared immediately.

.. code-block:: cpp

    auto db = sql::Database::open("...");

    // Create and immediately prepare statement.
    auto stmt1 = db->createStatement("SELECT * FROM myTable;", 
                                    true);

    if (!stmt1->isPrepared()) throw ...;

    // Create statement...
    auto stmt2 = db->createStatement("SELECT * FROM myTable;", 
                                    false);
    // ...and prepare later.
    if (!stmt2->prepare()) throw ...;

Statements are only valid as long as the database they belong to is valid. Calling any method on a statement after the
database went out of scope will result in unpredictable behaviour.

Once a statement is prepared, the :code:`step` and :code:`reset` methods can be called. These correspond directly to the
:code:`sqlite3_step` and :code:`sqlite3_reset` C functions.

Binding Parameters
------------------

The :code:`sqlite3_bind_*` functions can all be called through methods on the statement object. There is also a template
method that can bind multiple parameters at once and is a bit more flexible in the types it accepts. Depending on the
:code:`CPPQL_BIND\_ZERO_BASED_INDICES` config variable, these methods use either 1-based or 0-based indices.

The :code:`bindInt`, :code:`bindInt64`, :code:`bindFloat`, :code:`bindDouble` and :code:`bindNull` methods are pretty
self-explanatory. They directly pass on the value parameter to the appropriate C function.

.. code-block:: cpp

    auto stmt = db->createStatement("INSERT INTO myTable VALUES (?, ?, ?);", true);

    // Bind a 32-bit integer.
    stmt.bindInt(0, 10);
    // Bind a double.
    stmt.bindDouble(1, 4.55);
    // Bind null.
    stmt.bindNull(2);

Sqlite offers 3 ways of binding text: by taking ownership of the data, by copying it, or by assuming the data will exist
until the statement is freed or different data is bound. Each of these ways has a corresponding method:
:code:`bindText`, :code:`bindTransientText` and :code:`bindStaticText` respectively.

.. code-block:: cpp

    auto stmt = db->createStatement("INSERT INTO myTable VALUES (?, ?, ?);", true);

    // Pass text into function together with delete function.
    const char* txt0 = "abcde";
    stmt.bindText(0, txt0, 6, [](void* p){ delete[] static_cast<const char*>(p); });

    // Tell sqlite to copy text because it is 
    // deallocated before the statement's lifetime ends.
    {
        std::string txt1 = "abcde";
        stmt.bindTransientText(1, txt1);
    }

    // Assuming myString will not go out of scope 
    // before stmt, we can bind it like this.
    stmt.bindStaticText(2, myString);

The blob binding methods follow the same principle as the ones for binding text.

To clear all bindings, call the :code:`clearBindings` method.

In addition to the various methods that only bind a single value, there is a template :code:`bind` method that can take
an arbitrary number of parameters of any type. The first parameter is the index of the first column to bind a value to.
For each subsequent parameter, a call to the appropriate bind function is made. Binding integral and floating point
types is a bit more flexible since automatic casts are performed. See the table at the bottom of this section. Binding
text and blobs requires some more care. In order to distinguish between the various types of ownership, you must wrap a
pointer in a :code:`sql::Text` or :code:`sql::Blob` object. There are several utility functions (e.g.
:code:`toStaticBlob`) to quickly put (vectors of) objects in wrappers.

.. code-block:: cpp

    const char* txt = new char[6]{"abcde"};
    std::vector<float> vec = { 0.5f, 1.5f, 2.5f};
    auto dest = [](void* p){delete[] static_cast<const char*>(p);}
    stmt.bind(
        0,
        10,
        4.55,
        sql::Text{.data = txt, .size = 6, .destructor = dest},
        sql::toStaticBlob(vec)
    );

You can also pass :code:`std::optional` values to the template bind method. If the optional does not hold a value, the
:code:`bindNull` method is called for that parameter.

.. csv-table:: 
    :file: /_static/tables/statement_mapping.csv
    :header-rows: 1

Getting Columns
---------------

Similar to the bind functions. the :code:`sqlite3_column_*` functions to retrieve results are all available through
methods on the statement object.

Getting integers, floats and strings is straightforward. Just call the :code:`column` method with the (0-based) index
and pass a variable by reference. Any required conversions are performed by sqlite itself.

.. code-block:: cpp

    auto stmt = db->createStatement("SELECT (fCol, iCol1, iCol2, txtCol) FROM myTable;", true);

    // Get column as double.
    double col1;
    stmt.column(0, col1);

    // Get column as int32.
    int32_t col2;
    stmt.column(1, col2);

    // Get column as int64.
    int64_t col3;
    stmt.column(2, col3);

    // Get column as string.
    std::string col4;
    stmt.column(3, col4);

If you wish to verify a column type before retrieving the value, call the :code:`columnType` method, which wraps around
the :code:`sqlite3_column_type` function.

.. code-block:: cpp

    auto stmt = db->createStatement("SELECT (floatCol) FROM myTable;", true);

    if (stmt.columnType(0) != sql::Column::Type::Real)
        throw std::runtime_error("Help!");

    float col;
    stmt.column(0, col);

Blob values can be retrieved as (vectors of) arbitrary types.

.. code-block:: cpp

    struct Foo{...};

    auto stmt = db->createStatement("SELECT (blob1, blob2) FROM myTable;", true);

    // Get column as Foo.
    Foo foo;
    stmt.column(0, foo);

    // Get column as std::vector<float>.
    std::vector<float> floats;
    stmt.column(1, floats);

On top of the separate methods there is also a template method that returns columns by value. Furthermore, it will
perform some integer casts when necessary, similar to what the :code:`bind` method does.

.. code-block:: cpp

    auto stmt = db->createStatement("SELECT (intCol, floatCol, blobCol) FROM myTable;", true);

    int32_t i = stmt.column<int32_t>(0);
    double d = stmt.column<double>(1);
    std::vector<Foo> foo = stmt.column<std::vector<Foo>>(2);
