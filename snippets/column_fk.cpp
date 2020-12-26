// Create first table.
auto& table1 = db->createTable("table1");
auto& id = table1.createColumn("id", sql::Column::Type::Int);

// Create second table with column 
// referencing column from first table.
auto& table2 = db->createTable("table2");
table2.createColumn("fk", id);

// Make sure to commit referenced table(s) 
// before committing table with foreign key.
table1.commit();
table2.commit();