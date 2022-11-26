Delete Statement
================

The :code:`sql::DeleteStatement` class manages a prepared statement for removing rows from a table. It can be
constructed using a :code:`sql::DeleteQuery` (see :doc:`/queries/delete`).

.. code-block:: cpp

    sql::TypedTable<int64_t, float> table(...);
    auto query = table.del()
                      .where(table.col<1>() >= 10.0f);
    auto stmt = query.compile().bind(sql::BindParameters::All);

When invoked, the statement is stepped through and reset all at once. The rows are removed immediately.

.. code-block:: cpp

    stmt();
