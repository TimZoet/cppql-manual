Ordering
========

For all queries that contain an :code:`ORDER BY` clause, it is possible to write a simple expression using the column
objects. To sort a column in a particular order, pass it to either the :code:`sql::ascending` or :code:`sql::descending`
function. Multiple order by expressions can be concatenated using the :code:`+` operator. 

.. code-block:: cpp

    sql::TypedTable<int64_t, float, uint32_t> table(...);
    auto query = table.select()
                      .where(table.col<1>() >= 10.0f)
                      .orderBy(sql::ascending(table.col<2>()) +   // Order by col2 ASC
                               sql::descending(table.col<1>()));  //          col1 DESC

NULL Ordering
-------------

By default, :code:`NULL` values are considered to be smaller than any other value. When sorting a column in ascending
order they end up at the front, while in descending order they will be at the back. The sorting functions take an
optional parameter of type :code:`sql::Nulls` to determine if :code:`NULL` values should be returned first or last.

.. code-block:: cpp

    sql::TypedTable<int64_t, float, uint32_t> table(...);
    auto query = table.select()
                      .where(table.col<1>() >= 10.0f)
                      .orderBy(sql::ascending(table.col<2>(), sql::Nulls::Last) +   // Order by col2 ASC NULLS LAST
                               sql::descending(table.col<1>(), sql::Nulls::First)); //          col1 DESC NULLS FIRST
