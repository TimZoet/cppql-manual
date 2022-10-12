Order By
========

For all queries that contain an :code:`ORDER BY` clause, it is possible to write a simple expression using the column
objects. To sort a column in ascending order, prepend it with the :code:`+` operator. For descending order, use the
:code:`-` operator. 

.. code-block:: cpp

    // Assuming some table with at least 3 columns.
    sql::TypedTable<...> table(...);
    auto col0 = table.col<0>();
    auto col1 = table.col<1>();
    auto col2 = table.col<2>();

    // Order by col1 ASC, col0 DESC, col2 ASC.
    ... = table.selectAll(+col1 - col0 + col2);

Note that you must explicitly add a :code:`+` to the first column even when you want to order it in ascending order.
Additionally, to concatenate two expressions within parentheses you must use the :code:`+` operator. :code:`-` does not
merge them. It also doesn't reverse the order, so expressions such as :code:`(+a) - (+b)` and :code:`--a` are all
invalid.
