SelectOne Statement
===================

The :code:`sql::SelectOneStatement` class wraps around a :code:`sql::SelectStatement` instance. It uses the instance to
return just one result row. It can be constructed using a :code:`sql::SelectQuery` (see :doc:`/queries/select`).

.. code-block:: cpp

    sql::TypedTable<int64_t, float, double> table(...);
    auto query = table.select()
                      .where(table.col<0>() == 32);
    auto stmt = query.compile().bind(sql::BindParameters::All);

When invoked, it will iterate over all rows returned by the :code:`sql::SelectStatement` it wraps. If not exactly one
row is returned, an exception is thrown.

.. code-block:: cpp

    std::tuple<int64_t, float, double> row = stmt();
