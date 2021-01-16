// Create a new table and add some columns.
auto& table = db->createTable("myTable");
auto& c1 = table.createColumn("c1", sql::Column::Type::Int);
auto& c2 = table.createColumn("c2", sql::Column::Type::Real);
auto& c3 = table.createColumn("c3", sql::Column::Type::Text);
auto& c4 = table.createColumn("c3", sql::Column::Type::Blob);

// Mark one of the columns as the primary key.
c1.setPrimaryKey(true);
c1.setNotNull(true);
c1.setAutoIncrement(true);

// Run CREATE TABLE statement.
table.commit();