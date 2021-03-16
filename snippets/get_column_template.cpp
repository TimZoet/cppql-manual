auto stmt = db->createStatement(
    "SELECT (intCol, floatCol, blobCol) FROM myTable;", 
    true);

int32_t i = stmt.column<int32_t>(0);
double d = stmt.column<double>(1);
std::vector<Foo> foo = stmt.column<std::vector<Foo>>(2);
