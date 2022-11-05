Order By
========

For all queries that contain an :code:`ORDER BY` clause, it is possible to write a simple expression using the column
objects. To sort a column in a particular order, pass it to either the :code:`sql::ascending` or :code:`sql::descending`
function. Multiple order by expressions can be concatenated using the :code:`+` operator. 

.. code-block:: cpp

    // Assuming some table with at least 3 columns.
    sql::TypedTable<...> table(...);
    auto col0 = table.col<0>();
    auto col1 = table.col<1>();
    auto col2 = table.col<2>();

    // Order by col1 ASC, col0 DESC, col2 ASC.
    auto select = table.select(
        std::nullopt,
        sql::ascending(col1) + sql::descending(col0) + sql::ascending(col2),
        std::nullopt,
        sql::BindParameters::None
    );

NULL Ordering
-------------

By default, :code:`NULL` values are considered to be smaller than any other value. When sorting a column in ascending
order they end up at the front, while in descending order they will be at the back. The sorting functions take an
optional parameter of type :code:`sql::Nulls` to determine if :code:`NULL` values should be returned first or last.

.. code-block:: cpp

    // Order by col1 ASC NULLS LAST, col0 DESC NULLS FIRST, col2 ASC.
    auto select = table.select(
        std::nullopt,
        sql::ascending(col1, sql::Nulls::Last) + sql::descending(col0, sql::Nulls::First) + sql::ascending(col2),
        std::nullopt,
        sql::BindParameters::None
    );
