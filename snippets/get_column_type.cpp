auto stmt = db->createStatement(
    "SELECT (floatCol) FROM myTable;", 
    true);

if (stmt.columnType(0) != sql::Column::Type::Real)
    throw std::runtime_error("Help!");

float col;
stmt.column(0, col);