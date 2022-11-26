Select Query
============

The :code:`sql::SelectQuery` class can be used to prepare a statement that selects rows from a table. It is constructed
using the :code:`select` method of the :code:`sql::TypedTable` and :code:`sql::Join` classes. The generated code is of
the format :code:`SELECT <cols> FROM <table> JOIN <tables...> WHERE <expr> GROUP BY <cols> <HAVING> <expr> <union>
ORDER BY <expr> LIMIT <val> OFFSET <val>;`

.. code-block:: cpp

    sql::TypedTable<int64_t, float, double> table(...);

    auto query = table.select();
    auto stmt = query.compile();
    for (std::tuple<int64_t, float, double> row : stmt)
        ...

Already, this default query can be compiled into a :code:`sql::SelectStatement` (see :doc:`/statements/select`). When
invoked, you can iterate over it to retrieve results. Without a filter, all rows will be returned.

Instead of returning tuples, a query that automatically constructs a custom type can be created using the 
:code:`selectAs` method.

.. code-block:: cpp

    struct Row
    {
        int64_t   id;
        float   val0;
        double  val1;
    };

    ...

    auto query = table.selectAs<Row>();
    auto stmt = query.compile();
    for (Row row : stmt)
        ...

There are two versions of the :code:`select` and :code:`selectAs` methods. The first takes a list of columns, which can
be a reordered subset of all table columns. The second takes a list of integer template parameters which specify the
indices of the columns. This index list too can be a reordered subset.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, double> table(...);

    // Select third and second column.
    auto query = table.select(table.col<2>(), table.col<1>());
    auto stmt = query.compile();
    for (std::tuple<double, float> row : stmt)
        ...

    // Select first column only.
    auto query = table.selectAs<int64_t, 0>();
    auto stmt = query.compile();
    for (int64_t row : stmt)
        ...

Note that only the column based version also accepts aggregates. The index based version can merely retrieve columns
directly.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, double> table(...);

    auto query = table.select(sql::min(table.col<1>()), sql::max(table.col<2>()));

Where
-----

To add a :code:`WHERE` clause to limit which rows are returned, a filter expression can be applied to the query using
the :code:`where` method.

.. code-block:: cpp

    sql::TypedTable<int64_t, float> table(...);
    auto query = table.select()
                      .where(table.col<1>() >= 10.0f);

Order By
--------

To add an :code:`ORDER BY` clause, an order by expression can be applied to the query using the :code:`orderBy` method.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, uint32_t> table(...);
    auto query = table.select()
                      .where(table.col<1>() >= 10.0f)
                      .orderBy(sql::ascending(table.col<2>()) + 
                               sql::descending(table.col<1>()));

Limit and Offset
----------------

To add a :code:`LIMIT OFFSET` clause, a fixed pair of limit and offset integer values can be applied to the query using
the :code:`limitOffset` method.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, uint32_t> table(...);
    auto query = table.select()
                      .where(table.col<1>() >= 10.0f)
                      .orderBy(sql::ascending(table.col<2>()) + 
                               sql::descending(table.col<1>()))
                      .limitOffset(100, 10);

Group By and Having
-------------------

To add a :code:`GROUP BY` clause, a list of columns by which to group can be applied to the query using the
:code:`groupBy` method. Additionally, a :code:`HAVING` clause can be added by passing a filter expression to the
:code:`having` method.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, uint32_t> table(...);
    auto query = table.select(sql::avg<float>(table.col<1>()))
                      .groupBy(table.col<2>())
                      .having(sql::min(table.col<2>()) >= 0);

Unions
------

To create unions between two or more queries, you can chain calls to the :code:`unions` method.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, uint32_t> table(...);
    
    auto query = table.select<1, 2>()
                      .where(table.col<1>() > 5.0f)
                 
                 .unions(sql::UnionOperator::Intersect,
                 
                 table.select<1, 2>()
                      .where(table.col<2>() != 33)
                 );

                 .unions(sql::UnionOperator::Intersect,
                 
                 table.select<1, 2>()
                      .where(table.col<1>() < -400.0f)
                 );
