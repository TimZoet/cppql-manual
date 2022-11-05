Update
======

To update the rows in a table, you can construct a :code:`sql::Update` object from a :code:`sql::TypedTable`. This
object holds a statement of the form
:code:`UPDATE <table> SET <cols> = <vals> WHERE <expr> ORDER BY <expr> LIMIT <val> OFFSET <val>`. Its interface is very
similar to the :code:`sql::Insert` class.

.. code-block:: cpp

    // Create typed table.
    sql::TypedTable<int64_t, float, std::string> table(...);

    // Create update statement that will update the 2nd and 3rd 
    // columns for all rows that match the filter expression.
    int64_t param = 0;
    auto update = table.update<1, 2>(
        table.col<0>() == &param,
        std::nullopt,
        std::nullopt,
        sql::BindParameters::None
    );

The update object is callable with either separate values for each column, or a tuple.  Optionally, you can pass a
parameter to indicate whether fixed or dynamic filter parameters should be (re)bound.

.. code-block:: cpp

    // Update 2 rows.
    param = 1;
    update(sql::BindParameters::Dynamic, 10.0f, sql::toText("abc"));
    param = 2;
    update(sql::BindParameters::Dynamic, 20.0f, sql::toText("def"));

Order By and Limit
------------------

.. note::

    By default, Sqlite does not support limiting the number of updated rows. See
    `this ticket <https://github.com/TimZoet/cppql/issues/37>`_.
