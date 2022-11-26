Update Statement
================

The :code:`sql::UpdateStatement` class manages a prepared statement for updating existing rows in a table. It can be 
constructed using a :code:`sql::UpdateQuery` (see :doc:`/queries/update`).

.. code-block:: cpp

    sql::TypedTable<int64_t, float> table(...);
    int64_t id = 0;
    auto query = table.update<1>().where(table.col<0>() == &id);
    auto stmt = query.compile();

When invoked, the statement is stepped through and reset all at once. The passed values are applied to matching rows
immediately.

.. code-block:: cpp

    for (; id < 10; id++)
        stmt.bind(sql::BindParameters::Dynamic)(5.0f);
