// Assuming some table with at least 3 columns.
sql::ext::TypedTable<...> table(...);
auto col0 = table.col<0>();
auto col1 = table.col<1>();
auto col2 = table.col<2>();

// Order by col1 ASC, col0 DESC, col2 ASC.
... = table.selectAll(+col1 - col0 + col2);