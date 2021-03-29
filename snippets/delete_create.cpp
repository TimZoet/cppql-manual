// Create table.
auto& t = db->createTable("myTable");
t.createColumn<int32_t>("col1")
    .setAutoIncrement(true)
    .setPrimaryKey(true)
    .setNotNull(true);
t.createColumn...;
t.commit();

// Create typed table.
sql::ext::TypedTable<int32_t, ...> table(t);

// Prepare object to delete rows by primary key.
int32_t id = -1;
auto del = table.del(table.col<0>() == &id, false);