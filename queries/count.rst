Count
=====

To count the number rows in a table, you can construct a :code:`sql::Count` object from a :code:`sql::TypedTable`. This
object holds a statement of the form :code:`SELECT COUNT(*) FROM <table> WHERE <expr>`.

.. code-block:: cpp

    // Create typed table.
    sql::TypedTable<...> table(...);

    // Create count statement that will return the 
    // number of rows that match the filter expression.
    auto count = table.count(table.col<0>() >= 10, true);

Calling the count object will directly return the number of rows that match the filter expression. Optionally, you can
pass a boolean parameter to indicate whether filter parameters should be rebound.

.. code-block:: cpp

    auto rowCount = count(false);

The :code:`countAll` method of the :code:`sql::TypedTable` can be used to count all rows in a table, without a filter
expression.
