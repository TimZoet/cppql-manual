Select Statement
================

The :code:`sql::SelectStatement` class manages a prepared statement to retrieve rows from a table (or unions and joins
of tables). It can be constructed using a :code:`sql::SelectQuery` (see :doc:`/queries/select`).

.. code-block:: cpp

    sql::TypedTable<int64_t, float, double> table(...);
    auto query = table.select()
                      .where(table.col<1>() >= 10.0f);
    auto stmt = query.compile().bind(sql::BindParameters::All);

The :code:`sql::SelectStatement` is an iterable object. When invoked, a new iterator is constructed that performs a step
each time it is incremented, until all rows have been retrieved. At that point, the statement is reset and can be
iterated over again.

.. code-block:: cpp

    for (std::tuple<int64_t, float, double> row : stmt)
        ...

If you do not iterate over the results until all rows have been returned, the statement is not yet reset. This can be
done explicitly through the :code:`reset` method. Obviously, this invalidates any existing iterator.

.. code-block:: cpp

    for (auto row : stmt)
    {
        // Terminate early.
        if (rollDice() == 6)
            break;
        
        ...
    }

    // Explicitly reset before executing the statement again.
    stmt.reset();

    for (auto row : stmt) {...}
