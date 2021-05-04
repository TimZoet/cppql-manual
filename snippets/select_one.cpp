// Prepare object to select exactly one row by ID.
int32_t id = 0;
auto selectOne = table.selectOne(col0 == &id, false);

// Update parameter and select first row.
id = 1;
auto row0 = selectOne(true);

// Update parameter and select second row.
id = 2;
auto row1 = selectOne(true);