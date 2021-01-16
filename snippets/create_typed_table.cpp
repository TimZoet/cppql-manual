// Create a typed table wrapping around the new table.
sql::ext::TypedTable<int64_t, float, std::string, double*> 
    typedTable(table);