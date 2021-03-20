// Create a normal table.
auto& table = db->createTable("myTable");
table.createColumn("c1", sql::Column::Type::Int);
table.createColumn("c2", sql::Column::Type::Real);
table.createColumn("c3", sql::Column::Type::Text);
table.createColumn("c3", sql::Column::Type::Blob);
table.commit();

// Create a typed table wrapping around the new table.
sql::ext::TypedTable<
    int64_t,
    float,
    std::string,
    std::vector<int32_t>
> typedTable(table);