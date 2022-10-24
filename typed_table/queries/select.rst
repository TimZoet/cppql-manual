Select
======

To select rows in a table, you can construct a :code:`sql::Select` object from a :code:`sql::TypedTable`. This object
holds a statement of the form :code:`SELECT <cols> FROM <table> WHERE <expr>`.


.. code-block:: cpp

    // Create typed table.
    sql::TypedTable<int32_t, float, ...> table(...);
    const auto col1 = table.col<1>();

    // Prepare object to select first 2 columns of all rows
    // where 2nd column is in the range 10-20.
    auto select = table.select<0, 1>(col1 >= 10 && col1 <= 20, sql::BindParameters::All);

After construction, the object can be iterated over one or more times to retrieve the results.

.. code-block:: cpp

    for (std::tuple<int32_t, float> row : select)
    {
        // Do something with results.
        // std::get<0>(row)...
    }

Iterating over the select object will first reset the statement. If you want to (re)bind parameters, call
:code:`operator(sql::BindParameter)` before iteration. Since this operator returns a reference to the select object
itself, you can e.g. use it in a range based for loop: :code:`for (auto row : select(true)){...}`.

.. code-block:: cpp

    // Run.
    for (auto row : select(sql::BindParameters::Dynamic)){...}
    
    // Update parameters...

    // Run again.
    for (auto row : select(sql::BindParameters::Dynamic)){...}

Some notes on the internal implementation details. Calling the :code:`begin` method will run :code:`sqlite3_step` and
return an iterator. Each time the iterator is incremented, :code:`sqlite3_step` is called. The :code:`end` method
returns a dummy iterator value. The end of the sequence is determined using the return code of :code:`sqlite3_step`.

Custom Return Types
-------------------

It is also possible to use custom return types, instead of just tuples. To do so, pass your type as the first template
parameter to the :code:`select` method. The only requirement on the type is that it has a constructor that takes all
selected column values.

.. code-block:: cpp

    struct CustomType
    {
        CustomType(int32_t id, float f, std::string s);
    };

    ...

    for (CustomType row : table.select<CustomType, 0, 1, 2>(expr))
    { ... }

Containers
----------

Since the :code:`sql::Select` class has a :code:`begin` and :code:`end` method, you can also directly construct e.g. a
:code:`std::vector` from it.

.. code-block:: cpp

    std::vector<...> myVec(select.begin(), select.end());

Select One
----------

If you wish to construct a query that is expected to return exactly one row, there is the :code:`selectOne` method. This
method returns a callable object that directly produces a value instead of an iterator. If no or more than one rows
match the query, an exception is thrown.

.. code-block:: cpp

    // Prepare object to select exactly one row by ID.
    int32_t id = 0;
    auto selectOne = table.selectOne(col0 == &id, sql::BindParameters::All);

    // Update parameter and select first row.
    id = 1;
    auto row0 = selectOne(sql::BindParameters::All);

    // Update parameter and select second row.
    id = 2;
    auto row1 = selectOne(sql::BindParameters::All);

Select All
----------

It is also possible to select all rows in a table with the :code:`selectAll` method. This returns the same type of
object as a normal select, just without a filter expression.

.. code-block:: cpp

    // Prepare object to select all rows.
    auto selectAll = table.selectAll();

    // Iterate over results.
    for (auto row : selectAll)
        ...

Order By, Limit and Offset
--------------------------

All select statements (with the exception of :code:`selectOne`) support the :doc:`/typed_table/expressions/order_by`
and :doc:`/typed_table/expressions/limit_offset` expressions.

.. code-block:: cpp

    sql::TypedTable<int32_t, float> table(...);

    // This query will select all rows...
    auto select = table.select(
        table.col<1>() >= 10.0f,              // with col1 >= 10.0f
        -table.col<1>(),                      // ordered by col1 DESC
        sql::LimitExpression{.offset = 10},   // skipping the first 10
        sql::BindParameters::All
    );
