struct Foo{...};

auto stmt = db->createStatement(
    "SELECT (blob1, blob2) FROM myTable;", 
    true);

// Get column as Foo.
Foo foo;
stmt.column(0, foo);

// Get column as std::vector<float>.
std::vector<float> floats;
stmt.column(1, floats);
