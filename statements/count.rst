Count Statement
===============

The :code:`sql::CountStatement` class manages a prepared statement for retrieving the number of rows in a table. It can
be constructed using a :code:`sql::CountQuery` (see :doc:`/queries/count`).

.. code-block:: cpp

    sql::TypedTable<int64_t, float> table(...);
    auto query = table.count().where(table.col<1>() >= 10.0f);
    auto stmt = query.compile().bind(sql::BindParameters::All);

When invoked, the statement is stepped through and reset all at once. The number of rows is returned immediately.

.. code-block:: cpp

    const auto count = stmt();
