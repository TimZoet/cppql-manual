// Create typed table.
sql::ext::TypedTable<...> table(...);

// Create count statement that will return the 
// number of rows that match the filter expression.
auto count = table.count(table.col<0>() >= 10, true);