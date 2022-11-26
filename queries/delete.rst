Delete Query
============

The :code:`sql::DeleteQuery` class can be used to prepare a statement for deleting rows from a table. It is constructed
using the :code:`del` method of the :code:`sql::TypedTable` class. The generated code is of the format
:code:`DELETE FROM <table> WHERE <expr> ORDER BY <expr> LIMIT <val> OFFSET <val>;`.

.. code-block:: cpp

    sql::TypedTable<...> table(...);

    auto query = table.del();

Already, this default query can be compiled into a :code:`sql::DeleteStatement` (see :doc:`/statements/delete`). When
invoked, the statement will remove all rows in the table.

.. code-block:: cpp

    auto stmt = query.compile();
    stmt();

Where
-----

To add a :code:`WHERE` clause to limit which rows are deleted, a filter expression can be applied to the query using
the :code:`where` method.

.. code-block:: cpp

    sql::TypedTable<int64_t, float> table(...);
    auto query = table.del()
                      .where(table.col<1>() >= 10.0f);

Order By
--------

To add an :code:`ORDER BY` clause (which is really only useful combined with a :code:`LIMIT OFFSET` clause), an order by
expression can be applied to the query using the :code:`orderBy` method.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, uint32_t> table(...);
    auto query = table.del()
                      .where(table.col<1>() >= 10.0f)
                      .orderBy(sql::ascending(table.col<2>()) + 
                               sql::descending(table.col<1>()));

.. note::

    By default, Sqlite does not support limiting the number of deleted rows. See
    `this ticket <https://github.com/TimZoet/cppql/issues/37>`_.

Limit and Offset
----------------

To add a :code:`LIMIT OFFSET` clause (which is really only useful combined with an :code:`ORDER BY` clause), a fixed
pair of limit and offset integer values can be applied to the query using the :code:`limitOffset` method.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, uint32_t> table(...);
    auto query = table.del()
                      .where(table.col<1>() >= 10.0f)
                      .orderBy(sql::ascending(table.col<2>()) + 
                               sql::descending(table.col<1>()))
                      .limitOffset(100, 10);
