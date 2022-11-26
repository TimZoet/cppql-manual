Count Query
===========

The :code:`sql::CountQuery` class can be used to prepare a statement counting the number of rows in a table. It is
constructed using the :code:`count` method of the :code:`sql::TypedTable` class. The generated code is of the format
:code:`SELECT COUNT(*) FROM <table> WHERE <expr>;`.

.. code-block:: cpp

    sql::TypedTable<...> table(...);

    auto query = table.count();

Already, this default query can be compiled into a :code:`sql::CountStatement` (see :doc:`/statements/count`). When
invoked, the statement will return the total number of rows in the table.

.. code-block:: cpp

    auto stmt = query.compile();
    const auto count = stmt();

Where
-----

To add a :code:`WHERE` clause to filter the result rows, a filter expression can be applied to the query using the
:code:`where` method.

.. code-block:: cpp

    sql::TypedTable<int64_t, float> table(...);
    auto query = table.count().where(table.col<1>() >= 10.0f);
