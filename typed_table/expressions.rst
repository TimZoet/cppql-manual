Expressions
===========

.. toctree::
    :maxdepth: 3
    :titlesonly:
    :hidden:

    expressions/filter
    expressions/order_by
    expressions/limit_offset

To create filters, order result rows, etc. you can write various expressions. Most of these expressions are made up of
:code:`sql::ColumnExpression` objects, combined with various operators to e.g. filter the results of a selection based
on the value of one or more columns. Column objects can be constructed using the :code:`col` method of a
:code:`sql::TypedTable`, which takes the column index.

.. code-block:: cpp

    sql::TypedTable<int32_t, std::string, Foo> table(...);
    auto col0 = table.col<0>();
    auto filter = col0 > 20;
