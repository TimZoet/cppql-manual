// Specify just one column.
auto insert = table.insert<2>();

// Insert string and use default values for rest.
insert("mnop");

// Specify 0 columns.
auto insert2 = table.insert<>();

// Insert default values for all columns.
insert2();