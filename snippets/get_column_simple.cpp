auto stmt = db->createStatement(
    "SELECT (fCol, iCol1, iCol2, txtCol) FROM myTable;", 
    true);

// Get column as double.
double col1;
stmt.column(0, col1);

// Get column as int32.
int32_t col2;
stmt.column(1, col2);

// Get column as int64.
int64_t col3;
stmt.column(2, col3);

// Get column as string.
std::string col4;
stmt.column(3, col4);
