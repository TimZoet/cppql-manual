Queries
=======

.. toctree::
    :maxdepth: 3
    :titlesonly:
    :hidden:

    queries/count
    queries/delete
    queries/insert
    queries/select
    queries/update

The :code:`INSERT`, :code:`DELETE`, :code:`SELECT` and :code:`UPDATE` statements can all be constructed directly from a
:code:`sql::TypedTable`. Calling the various :code:`select`, :code:`insert`, etc. methods of a typed table will return a
reusable query object. This query objects holds a :code:`sql::Statement`.

.. code-block:: cpp

    // Assuming a table with 2 columns.
    sql::TypedTable<int64_t, std::string> typedTable(...);

    // Insert some data using a sql::Insert query object.
    // Constructs a statement that will roughly look like this:
    // "INSERT INTO tableName VALUES (?, ?);"
    auto insert = typedTable.insert();
    insert(12, sql::toText("ghi"));
    insert(-4, sql::toText("abc"));
    insert(8, sql::toText("def"));
    insert(14, sql::toText("jkl"));

    // Retrieve data using a sql::Select query object. Only 1 column is retrieved,
    // so we can directly construct a std::string from it instead of having to rely on a std::tuple.
    // Constructs a statement that will roughly look like this:
    // "SELECT stringColumn FROM tableName WHERE intColumn >= 0 ORDER BY intColumn ASC;"
    auto select = typedTable.select<std::string, 1>(
        typedTable.col<0>() >= 0,
        +typedTable.col<0>(),
        sql::BindParameters::All
    );

    // Iterate over the query object to step through the rows.
    for (const auto& str : select)
        std::cout << str; // Should print defghijkl.

All query objects offer a C++ only interface to the underlying table and are valid as long as the table they operate on
is valid. To prevent repeated creation of the same statements, which is very expensive, you should try and reuse them as
much as possible. 
