Table
=====

The :code:`sql::Table` class does not explicitly wrap any sqlite object. It offers a number of convenient methods to
create, drop and inspect the tables in a database.

Creating Tables
---------------

New tables can be created through the :code:`createTable` method of the database. It returns a reference to a new
:code:`sql::Table` instance. The table has a method to create new :code:`Column` s. In turn, this object has some
methods to set e.g. not null contraints. None of these functions actually run any SQL statements. This is done once you
call the table's :code:`commit` method. 

.. code-block:: cpp

    // Create a new table and add some columns.
    auto& table = db->createTable("myTable");
    auto& c1 = table.createColumn("c1", sql::Column::Type::Int);
    auto& c2 = table.createColumn("c2", sql::Column::Type::Real);
    auto& c3 = table.createColumn("c3", sql::Column::Type::Text);
    auto& c4 = table.createColumn("c3", sql::Column::Type::Blob);

    // Mark one of the columns as the primary key.
    c1.setPrimaryKey(true);
    c1.setNotNull(true);
    c1.setAutoIncrement(true);

    // Run CREATE TABLE statement.
    table.commit();

Since the :code:`createColumn` and :code:`set` methods all return a reference to the column, you can also chain calls.

.. code-block:: cpp

    table.createColumn("col1", sql::Column::Type::Int)
       .setPrimaryKey(true)
       .setNotNull(true)
       .setAutoIncrement(true);

Adding a foreign key column is straightforward. Just replace the type parameter by another column object.

.. code-block:: cpp

    // Create first table.
    auto& table1 = db->createTable("table1");
    auto& id = table1.createColumn("id", sql::Column::Type::Int);

    // Create second table with column 
    // referencing column from first table.
    auto& table2 = db->createTable("table2");
    table2.createColumn("fk", id);

    // Make sure to commit referenced table(s) 
    // before committing table with foreign key.
    table1.commit();
    table2.commit();

Because no :code:`CREATE TABLE` query is run until the :code:`commit` method is called, any queries involving that
table will obviously fail until that happens. Also, references to tables are only valid as long as the database object
is not deallocated. When this deallocation happens, any uncommitted tables are lost.

Registering Tables
------------------

When a database is opened, the tables in that database are automatically registered. Note that this does not include all
internal tables whose names starts with :code:`sqlite`. To interact with those tables, you will have to use the C API.
No functionality for this is exposed at a higher level.

If a table is created without using the :code:`createTable` method described above, for example by creating a
:code:`sql::Statement` object with a :code:`CREATE TABLE` query, the new table is not automatically registered. This
must be done manually through the :code:`registerTable` method of the :code:`sql::Database` class.

.. code-block:: cpp

    // Create table through raw query.
    auto stmt = db->createStatement("CREATE TABLE myTable (col1 INTEGER, col2 TEXT);", true);
    stmt.step();

    // Manually register new table.
    db->registerTable("myTable");

    // New table can now be retrieved.
    auto& table = db->getTable("myTable");

Dropping Tables
---------------

Registered tables can be deleted using the :code:`dropTable` method of the database. This will run a :code:`DROP TABLE`
query. Note that any references to the table instance are invalidated.

.. code-block:: cpp

    // Create a new table.
    auto& table = db->createTable("myTable");
    ...

    // Drop table.
    db->dropTable("myTable");

    // Can't do this, table reference has been invalidated.
    table.anything();
