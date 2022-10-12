Typed Tables
============

.. toctree::
    :maxdepth: 3
    :titlesonly:
    :hidden:

    typed_table/queries
    typed_table/filter
    typed_table/order_by
    typed_table/limit_offset

The :code:`sql::Table` class does not offer much in terms of type safety or extensive interfaces. For that, there is
the :code:`sql::TypedTable` class, which can be used to construct queries without actually writing any SQL code.

A :code:`sql::TypedTable` can be constructed by passing it a normal table and allows you to specify a static type for
each column.

.. code-block:: cpp

    // Create a normal table.
    auto& table = db->createTable("myTable");
    table.createColumn("c1", sql::Column::Type::Int);
    table.createColumn("c2", sql::Column::Type::Real);
    table.createColumn("c3", sql::Column::Type::Text);
    table.createColumn("c3", sql::Column::Type::Blob);
    table.commit();

    // Create a typed table wrapping around the new table.
    sql::TypedTable<
        int64_t,
        float,
        std::string,
        std::vector<int32_t>
    > typedTable(table);

The column types follow the same rules as column retrieval. See Section~\ref{section:statement:get}. If you pass an
invalid type, an exception will be thrown directly upon construction.
