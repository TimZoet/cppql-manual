// Assuming some table with an int and float column.
sql::ext::TypedTable<int32_t, float> table(...);
auto col0 = table.col<0>();
auto col1 = table.col<1>();

// Select all rows that match the expression.
... = table.select(col0 > 10 && col1 <= 4.5f, true);