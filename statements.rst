Statements
==========

.. toctree::
    :maxdepth: 3
    :titlesonly:
    :hidden:

    statements/count
    statements/delete
    statements/insert
    statements/select
    statements/select_one
    statements/update

There are several statement classes that manage a :code:`sql::Statement` object (see :doc:`/core/statement`). They take
care of binding parameters, stepping through the statement, etc. Constructing them is done through :doc:`/queries`. For
optimal performance, you should reuse statements as much as possible.

Binding Parameters
------------------

Statements do not bind any parameters when constructed or invoked. This needs to be done manually. An exception to this
are the new/updated column values passed to the insert and update statements, which are bound automatically.

Typically, you'll want to bind any fixed parameters directly after compiling a statement, but dynamic parameters only
just before they are used. This should give the best performance. This can be achieved by passing the appropriate
:code:`sql::BindParameters` enum value to the :code:`bind` methods of the statements.

.. code-block:: cpp

    sql::TypedTable<int64_t, float> table(...);
    int64_t id = 0;
    auto query = table.update<1>().where(table.col<0>() == &id && table.col<1>() < 0.0f);

    // Compile query and instantly bind fixed parameters.
    auto stmt = query.compile().bind(sql::BindParameters::Fixed);

    for (id = 100; id < 200; id++)
    {
        // Bind dynamic parameters when the variable has been incremented.
        stmt.bind(sql::BindParameters::Dynamic);

        stmt(500.0f);
    }
