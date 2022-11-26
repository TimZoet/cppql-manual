Parameters
==========

Expressions that take parameters (e.g. comparison expressions used in the :code:`WHERE` clause) can hold them in fixed
or dynamic form.

The following example uses a single fixed parameter (note that fixed parameters include normal variables, not just
constants known at compile time). The value is passed on from the query to the statement when compiled. It can (or
rather, needs to) be bound. It can never be modified.

.. code-block:: cpp

    // Construct query with a single fixed parameter.
    sql::TypedTable<int64_t, float> table(...);
    auto query = table.select().where(table.col<1>() >= 42.0f);
    auto stmt = query.compile().bind(sql::BindParameters::Fixed);

Adding a dynamic parameter is done by using a pointer to a value. Note that the expression does not take ownership of
the pointer. The referenced value should remain valid for the lifetime of the query and statement objects. After
updating the variable, you can rebind dynamic parameters on the statement.

.. code-block:: cpp

    // Construct query with a single dynamic parameter.
    float comp = 42.0f;
    sql::TypedTable<int64_t, float> table(...);
    auto query = table.select().where(table.col<1>() >= &comp);
    auto stmt = query.compile();

    // Bind dynamic parameters and iterate over results.
    for (auto row : stmt.bind(sql::BindParameters::Dynamic)) {...}

    // Update value. Then (re)bind dynamic parameters and iterate over new results.
    comp = 66.6f;
    for (auto row : stmt.bind(sql::BindParameters::Dynamic)) {...}
