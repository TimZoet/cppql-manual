// Create a new table.
auto& table = db->createTable("myTable");
...

// Drop table.
db->dropTable("myTable");

// Can't do this, table reference has been invalidated.
table.anything();