Queries
=======

.. toctree::
    :maxdepth: 3
    :titlesonly:
    :hidden:

    queries/count
    queries/delete
    queries/insert
    queries/join
    queries/select
    queries/update

The query classes can be used to construct various statement objects (see :doc:`/statements`). They are constructed
through :code:`sql::TypedTable` instances. By chaining method calls such as :code:`where`, :code:`orderBy`, etc., you
can construct complex queries with all the clauses Sqlite supports.

.. code-block:: cpp

    sql::TypedTable<int64_t, float> table(...);
    auto query = table.select();
                      .where(table.col<1>() >= 10.0f)
                      .orderBy(sql::ascending(table.col<1>()))
                      .limitOffset(10, 20);

All these methods try to catch as many errors as possible during compilation, protecting you from building invalid
queries. For instance, you cannot:

* Add a :code:`WHERE` clause twice;
* Pass columns from another table;
* Add a :code:`USING` or :code:`ON` clause when doing a natural join;
* ...and more.

Not all errors are caught at compile time, though. Since all validation is based on the type system, two distinct tables
with the same columns are indistinguishable.

.. code-block:: cpp

    // Two typed tables. Assume they refer to two distinct tables.
    // However, these tables just so happen to have the same columns.
    sql::TypedTable<int64_t, float> tableA(...);
    sql::TypedTable<int64_t, float> tableB(...);

    // This will compile. The error is only caught at runtime and results in an exception.
    auto query = tableA.select(tableB.col<0>());

Compilation
-----------

All query objects have a :code:`compile` method that generates the SQL code string, prepares a :code:`sql::Statement`
object and then wraps it in the appropriate typed statement object. After compilation, you can still use the query
object to construct more specific queries and statements.

.. code-block:: cpp

    sql::TypedTable<int64_t, float> table(...);
    auto query0 = table.select();
                       .where(table.col<1>() >= 10.0f);
    auto stmt0 = query0.compile();
    
    auto query1 = query0.limitOffset(10, 100);
    auto stmt1 = query1.compile();
