std::filesystem::path file = ...;

// Open an existing database.
auto db = sql::Database::open(file);
// Create a new database.
auto db = sql::Database::create(file);
// Open or create a database.
auto db = sql::Database::openOrCreate(file);

// Pass a connection handle directly to the constructor.
sqlite3* handle = ...;
auto db = std::make_unique<sql::Database>(handle);