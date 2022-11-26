Aggregates
==========

There are 6 built-in aggregate functions: :code:`avg`, :code:`count`, :code:`max`, :code:`min`, :code:`sum` and
:code:`total`. All functions take a column and can be used directly in various clauses.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, uint32_t> table(...);

    auto query = table.select(sql::avg(table.col<1>()));

Return Type
-----------

All aggregate functions have a default return type. This can be overridden using the first template parameter.

.. code-block:: cpp

    auto query = table.select(sql::avg<double>(table.col<1>()));

Distinct
--------

Enabling :code:`DISTINCT` is done using the second template parameter.

.. code-block:: cpp

    auto query = table.select(sql::sum<int64_t, true>(table.col<2>()));
