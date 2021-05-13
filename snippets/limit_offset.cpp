// Assuming some table with an int column.
sql::ext::TypedTable<int32_t> table(...);
auto col0 = table.col<0>();

// Select first 10 rows that match filter.
... = table.select(col0 >= 33,
                   sql::ext::LimitExpression{.limit = 10},
                   true);