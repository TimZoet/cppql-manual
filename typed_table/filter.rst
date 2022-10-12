Filter
======

For all queries that contain a :code:`WHERE` clause, you can write a filter expression. Such an expression combines one
or more column objects and comparisons to values.

.. code-block:: cpp

    // Assuming some table with an int and float column.
    sql::TypedTable<int32_t, float> table(...);
    auto col0 = table.col<0>();
    auto col1 = table.col<1>();

    // Select all rows that match the expression.
    ... = table.select(col0 > 10 && col1 <= 4.5f, true);

The above example uses fixed parameters (note that fixed parameters include normal variables, not just constants known
at compile time). It is also possible to use dynamic parameters. These values can be rebound to the statement between
executions of the same query. Adding a dynamic parameter is done by using a pointer to a value. Note that the expression
does not take ownership of the pointer. The referenced value should remain valid for the lifetime of the query object.

.. code-block:: cpp

    // A filter expression with dynamic parameters.
    int32_t param0 = 10;
    float   param1 = 4.5f;
    ... = table.select(col0 > &param0 && col1 <= &param1, true);

    // Do stuff with query...

    // Update parameters.
    param0 = 20;
    param1 = 13.33f;

    // Do more stuff with updated query...
