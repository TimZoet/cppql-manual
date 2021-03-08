auto db = sql::Database::open("...");

// Create and immediately prepare statement.
auto stmt1 = db->createStatement("SELECT * FROM myTable;", 
                                 true);

if (!stmt1->isPrepared()) throw ...;

// Create statement...
auto stmt2 = db->createStatement("SELECT * FROM myTable;", 
                                 false);
// ...and prepare later.
if (!stmt2->prepare()) throw ...;