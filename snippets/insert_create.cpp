// Create table.
auto& t = db->createTable("myTable");
t.createColumn<int32_t>("col1")
    .setAutoIncrement(true)
    .setPrimaryKey(true)
    .setNotNull(true);
t.createColumn<float>("col2");
t.createColumn<std::string>("col3");
t.commit();

// Create typed table.
sql::ext::TypedTable<int64_t, float, std::string> table(t);

// Create insert statement.
auto insert = table.insert();