Delete
======

To remove rows from a table, you can construct a :code:`sql::Delete` object from a :code:`sql::TypedTable`. This object
holds a statement of the form :code:`DELETE FROM <table> WHERE <expr>`.

.. code-block:: cpp

    // Create typed table.
    sql::TypedTable<int32_t, ...> table(...);

    // Prepare object to delete rows by primary key.
    int32_t id = -1;
    auto del = table.del(table.col<0>() == &id, sql::BindParameters::None);

Calling the count object will immediately delete all rows that match the filter expression. Optionally, you can pass a
parameter to indicate whether fixed or dynamic filter parameters should be (re)bound.

.. code-block:: cpp

    // Delete all rows with IDs 1-10.
    for (id = 1; id <= 10; id++)
        del(sql::BindParameters::Dynamic);

Order By, Limit and Offset
--------------------------

The delete statement supports the :doc:`/typed_table/expressions/order_by` and
:doc:`/typed_table/expressions/limit_offset` expressions.

.. code-block:: cpp

    sql::TypedTable<int32_t, float> table(...);

    // This query will delete all rows...
    auto del = table.del(
        table.col<1>() >= 10.0f,             // with col1 >= 10.0f
        -table.col<1>(),                     // ordered by col1 DESC
        sql::LimitExpression{.limit = 10},   // limited to the first 10
        sql::BindParameters::All
    );

    del();

.. note::

    By default, Sqlite does not support limiting the number of deleted rows. See
    `this ticket <https://github.com/TimZoet/cppql/issues/37>`_.
