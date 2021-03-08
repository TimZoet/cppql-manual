auto stmt = db->createStatement(
    "INSERT INTO myTable VALUES (?, ?, ?);", 
    true);

// Bind a 32-bit integer.
stmt.bindInt(0, 10);
// Bind a double.
stmt.bindDouble(1, 4.55);
// Bind null.
stmt.bindNull(2);