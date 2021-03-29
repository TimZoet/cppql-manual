// Create insert.
sql::ext::TypedTable<int64_t, std::vector<float>> table(...);
auto insert = table.insert();

// Insert vector.
std::vector<float> floats = {1.0f, 2.0f, 3.0f};
insert(nullptr, sql::toStaticBlob(floats));