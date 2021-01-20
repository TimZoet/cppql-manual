// Create TypedTable from t, 
// which should be a table with matching column types.
sql::ext::TypedTable<int32_t, ...> table(t);

// Prepare object to delete rows by primary key.
int32_t id = -1;
auto del = table.del(table.col<0>() == &id, false);