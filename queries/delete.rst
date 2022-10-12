Delete
======

To remove rows from a table, you can construct a :code:`sql::Delete` object from a :code:`sql::TypedTable`. This objects
holds a statement of the form :code:`DELETE FROM <table> WHERE <expr>`.

.. code-block:: cpp

    // Create typed table.
    sql::TypedTable<int32_t, ...> table(...);

    // Prepare object to delete rows by primary key.
    int32_t id = -1;
    auto del = table.del(table.col<0>() == &id, false);

The first parameter is the expression by which to filter. The second parameter indicates whether expression parameters
should be bound immediately upon creation. After construction, the object can be invoked one or more times.

.. code-block:: cpp

    // Delete all rows with IDs 1-10.
    for (id = 1; id <= 10; id++)
        del(true);
    
There are two overloads of :code:`operator()`. The first does not take any parameters and runs the delete statement
without (re)binding any parameters. The second accepts a boolean parameter which, if true, will result in all parameters
being bound before running the delete. If the filter expression does not have dynamic parameters it is best to bind upon
construction and then invoke the parameterless function. This will result in the best performance.

Order By and Limit
------------------
