Update Query
============

The :code:`sql::UpdateQuery` class can be used to prepare a statement that updates existing rows in a table. It is
constructed using the :code:`update` method of the :code:`sql::TypedTable` class. The generated code is of the format
:code:`UPDATE <table> SET (<cols>) = (<vals>) WHERE <expr> ORDER BY <expr> LIMIT <val> OFFSET <val>;`.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, double> table(...);

    auto query = table.update();
    auto stmt = query.compile();
    stmt(64, 8.0f, 13.0);

Already, this default query can be compiled into a :code:`sql::UpdateStatement` (see :doc:`/statements/update`). When
invoked, you can supply the new values for each column. Without a filter, all existing rows will be affected.

There are two versions of the :code:`update` method. The first takes a list of columns, which can be a reordered subset
of all table columns. The second takes a list of integer template parameters which specify the indices of the columns.
This index list too can be a reordered subset.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, double> table(...);

    // Update second and third column only.
    auto query = table.update(table.col<1>(), table.col<2>());
    auto stmt = query.compile();
    stmt(5.0f, 10.0);

    // Update third column only.
    auto query = table.insert<2>();
    auto stmt = query.compile();
    stmt(9.0);

Where
-----

To add a :code:`WHERE` clause to limit which rows are updated, a filter expression can be applied to the query using
the :code:`where` method.

.. code-block:: cpp

    sql::TypedTable<int64_t, float> table(...);
    auto query = table.update()
                      .where(table.col<1>() >= 10.0f);

Order By
--------

To add an :code:`ORDER BY` clause (which is really only useful combined with a :code:`LIMIT OFFSET` clause), an
order by expression can be applied to the query using the :code:`orderBy` method.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, uint32_t> table(...);
    auto query = table.update()
                      .where(table.col<1>() >= 10.0f)
                      .orderBy(sql::ascending(table.col<2>()) + 
                               sql::descending(table.col<1>()));

.. note::

    By default, Sqlite does not support limiting the number of deleted rows. See
    `this ticket <https://github.com/TimZoet/cppql/issues/37>`_.

Limit and Offset
----------------

To add a :code:`LIMIT OFFSET` clause (which is really only useful combined with an :code:`ORDER BY` clause), a
fixed pair of limit and offset integer values can be applied to the query using the :code:`limitOffset` method.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, uint32_t> table(...);
    auto query = table.update()
                      .where(table.col<1>() >= 10.0f)
                      .orderBy(sql::ascending(table.col<2>()) + 
                               sql::descending(table.col<1>()))
                      .limitOffset(100, 10);
