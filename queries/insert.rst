Insert
======

To insert new rows into a table, you can construct a :code:`sql::Insert` object from a :code:`sql::TypedTable`. This
object holds a statement of the form :code:`INSERT INTO <table> VALUES <vals>`.

.. code-block:: cpp

    // Create typed table.
    sql::TypedTable<int64_t, float, std::string> table(...);

    // Create insert statement.
    auto insert = table.insert();

The insert object is callable with either separate values for each column, or a tuple.

.. code-block:: cpp

    // Insert separate values.
    insert(1, 10.0f, "abc"s);

    // Insert tuple.
    auto row = std::make_tuple<int64_t, float, std::string>(2, 20.0f, "def"s);
    insert(row);

To insert blobs, you must use the wrapper classes as described in Section~\ref{section:statement:bind}.

.. code-block:: cpp

    // Create insert.
    sql::TypedTable<int64_t, std::vector<float>> table(...);
    auto insert = table.insert();

    // Insert vector.
    std::vector<float> floats = {1.0f, 2.0f, 3.0f};
    insert(nullptr, sql::toStaticBlob(floats));

A single insert object reuses the same prepared statement each time a row is added. It can be called any number of
times. Multiple insert objects do not share this statement. To limit the number of times new statements are prepared,
reuse the same insert object as much as you can.

Default Values
--------------

To insert the default value for a column, or to have e.g. primary keys properly auto increment, simply pass a
:code:`nullptr` instead of a value.

.. code-block:: cpp

    insert(nullptr, 10.0f, "abc"s);

It is also possible to specify the columns you wish to give an explicit value.

.. code-block:: cpp

    // Specify just one column.
    auto insert = table.insert<2>();

    // Insert string and use default values for rest.
    insert("mnop");

    // Specify 0 columns.
    auto insert2 = table.insert<>();

    // Insert default values for all columns.
    insert2();
