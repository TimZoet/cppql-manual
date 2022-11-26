Insert Statement
================

The :code:`sql::InsertStatement` class manages a prepared statement for inserting new rows into a table. It can be 
constructed using a :code:`sql::InsertQuery` (see :doc:`/queries/insert`).

.. code-block:: cpp

    sql::TypedTable<int64_t, float, double> table(...);

    auto query = table.insert<1, 2>();
    auto stmt = query.compile();

When invoked, the statement is stepped through and reset all at once. The passed values are inserted as a new row
immediately.

.. code-block:: cpp

    for (size_t i = 0; i < 10; i++)
        stmt(static_cast<float>(i + 1), static_cast<double>(i * 2));
