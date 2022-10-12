Database
========

The :code:`sql::Database` class is a wrapper around a sqlite database connection. The snippet below shows various ways
in which a database file can be created and/or opened. There are several static methods that only require a path to a
file and will return an opened (and possible newly created) database. Alternatively, you can directly construct a
database from an already opened connection handle. Note that in all cases, the handle is managed by the database object.
The connection is automatically closed when the object goes out of scope.

.. code-block:: cpp

    std::filesystem::path file = ...;

    // Open an existing database.
    auto db = sql::Database::open(file);
    // Create a new database.
    auto db = sql::Database::create(file);
    // Open or create a database.
    auto [db, created] = sql::Database::openOrCreate(file);

    // Pass a connection handle directly to the constructor.
    sqlite3* handle = ...;
    auto db = std::make_unique<sql::Database>(handle);


At any time, you can retrieve the handle by calling the :code:`get` method. Since this library does not have wrappers
around all C API functions, you may find yourself using this method from time to time in order to call some of the more
obscure :code:`sqlite3_` functions.
