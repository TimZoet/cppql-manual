// Create table through raw query.
auto stmt = db->createStatement(
    "CREATE TABLE myTable (col1 INTEGER, col2 TEXT);", true);
stmt.step();

// Manually register new table.
db->registerTable("myTable");

// New table can now be retrieved.
auto& table = db->getTable("myTable");