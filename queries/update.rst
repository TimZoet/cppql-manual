Update
======

To update the rows in a table, you can construct a :code:`sql::Update` object from a :code:`sql::TypedTable`. This
object holds a statement of the form :code:`UPDATE <table> SET <cols> = <vals>`. Its interface is very similar to the
:code:`sql::Insert` class.

.. code-block:: cpp

    // Create typed table.
    sql::TypedTable<int64_t, float, std::string> table(...);

    // Create update statement that will update the 2nd and 3rd 
    // columns for all rows that match the filter expression.
    int64_t param = 0;
    auto update = table.update<1, 2>(table.col<0>() == &param, false);

The update object is callable with either separate values for each column, or a tuple. Optionally, you can pass a
boolean parameter to indicate whether filter parameters should be rebound.

.. code-block:: cpp

    // Update 2 rows.
    param = 1;
    update(true, 10.0f, "abc"s);
    param = 2;
    update(true, 20.0f, "def"s);

Order By and Limit
------------------
