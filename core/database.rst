Database
========

The :code:`sql::Database` class is a wrapper around a sqlite database connection. The snippet below shows various ways
in which a database file can be created and/or opened. There are several static methods that only require a path to a
file and will return an opened (and possible newly created) database. Alternatively, you can directly construct a
database from an already opened connection handle. Note that in all cases, the handle is managed by the database object.
By default the connection is automatically closed when the object goes out of scope, though this can be changed.

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

Destruction
-----------

On destruction of the :code:`sql::Database`, it will optionally close the connection and shutdown the sqlite library.
This can be modified through the :code:`setClose` and :code:`setShutdown` methods. By default, the :code:`sqlite3_close`
is called.

If you wish to extract the connection handle from the database object, you should disable both closing and shutdown
before it goes out of scope:

.. code-block:: cpp

    // Disable calling of close and shutdown functions.
    db->setClose(sql::Database::Close::Off);
    db->setShutdown(sql::Database::Shutdown::Off);

    // Extract handle from db.
    sqlite3* handle = db->get();

    // db can now safely go out of scope.
    ...

Disabling shutdown can also be useful if you are opening multiple databases. This prevents sqlite from repeatedly
re-initializing, which is of course a bit of a waste. By default, shutdown is enabled. This can be disabled through a
build variable, though. Refer to the build instructions for more information.
