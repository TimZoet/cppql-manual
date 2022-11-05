Count
=====

To count the number rows in a table, you can construct a :code:`sql::Count` object from a :code:`sql::TypedTable`. This
object holds a statement of the form :code:`SELECT COUNT(*) FROM <table> WHERE <expr>`.

.. code-block:: cpp

    // Create typed table.
    sql::TypedTable<...> table(...);

    // Create count statement that will return the  number of rows that match the filter expression.
    auto count = table.count(table.col<0>() >= 10, sql::BindParameters::All);

Calling the count object will directly return the number of rows that match the filter expression. Optionally, you can
pass a parameter to indicate whether fixed or dynamic filter parameters should be (re)bound.

.. code-block:: cpp

    count = count(sql::BindParameters::Dynamic);

To count all rows in a table, pass :code:`std::nullopt` in place of a filter expression.

.. code-block:: cpp

    // Count all rows
    auto countAll = table.count(std::nullopt, sql::BindParameters::None);
    const auto rowCount = countAll();
