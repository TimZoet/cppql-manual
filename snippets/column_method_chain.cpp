table.createColumn("col1", sql::Column::Type::Int)
     .setPrimaryKey(true)
     .setNotNull(true)
     .setAutoIncrement(true);