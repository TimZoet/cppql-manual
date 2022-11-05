Limit and Offset
================

For all queries that contain a :code:`LIMIT <X> OFFSET <Y>` clause, it is possible to use the
:code:`sql::LimitExpression` class to control the number of returned rows.

.. code-block:: cpp

    // Assuming some table with an int column.
    sql::TypedTable<int32_t> table(...);

    // Select 10 rows that match filter, skipping the first 5.
    auto select = table.select(
        table.col<0>() >= 33,
        std::nullopt,
        sql::LimitExpression{.limit = 10, .offset = 5},
        sql::BindParameters::All
    );
