// Create typed table.
sql::ext::TypedTable<int64_t, float, std::string> table(...);

// Create update statement that will update the 2nd and 3rd 
// columns for all rows that match the filter expression.
int64_t param = 0;
auto update = table.update<1, 2>(table.col<0>() == &param, false);

