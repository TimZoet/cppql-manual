// Create TypedTable from t, 
// which should be a table with matching column types.
sql::ext::TypedTable<int32_t, float, ...> table(t);
const auto col1 = table.col<1>();

// Prepare object to select first 2 columns of all rows
// where 2nd column is in the range 10-20.
auto select = table.select<0, 1>(col1 >= 10 && col1 <= 20, true);