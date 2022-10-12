Limit and Offset
================

For all queries that contain a :code:`LIMIT <X> OFFSET <Y>` clause, it is possible to use the
:code:`sql::LimitExpression` class to control the number of returned rows.

.. code-block:: cpp

    // Assuming some table with an int column.
    sql::TypedTable<int32_t> table(...);
    auto col0 = table.col<0>();

    // Select first 10 rows that match filter.
    ... = table.select(
        col0 >= 33,
        sql::LimitExpression{.limit = 10},
        true
    );
