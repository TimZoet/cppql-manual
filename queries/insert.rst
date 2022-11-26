Insert Query
============

The :code:`sql::InsertQuery` class can be used to prepare a statement that inserts new values into a table. It is
constructed using the :code:`insert` method of the :code:`sql::TypedTable` class. The generated code is of the format
:code:`INSERT INTO <table> (<cols>) VALUES (<vals>);`.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, double> table(...);

    auto query = table.insert();
    auto stmt = query.compile();
    stmt(64, 8.0f, 13.0);

Already, this default query can be compiled into a :code:`sql::InsertStatement` (see :doc:`/statements/insert`). When
invoked, you can supply the values that must be inserted as a new row.

There are two versions of the :code:`insert` method. The first takes a list of columns, which can be a reordered subset
of all table columns. The second takes a list of integer template parameters which specify the indices of the columns.
This index list too can be a reordered subset. Unspecified columns, if any, will automatically receive a default value.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, double> table(...);

    // First column will receive default value on insert. Other values must be specified.
    auto query = table.insert(table.col<1>(), table.col<2>());
    auto stmt = query.compile();
    stmt(5.0f, 10.0);

    // First column will receive default value on insert. Other values must be specified in reverse order.
    auto query = table.insert<2, 1>();
    auto stmt = query.compile();
    stmt(9.0, -54.0f);

To insert default values for all columns, you must provide an empty template parameter list.

.. code-block:: cpp

    // All columns will receive default values.
    auto query = table.insert<>();
    auto stmt = query.compile();
    stmt();
