// Prepare object to delete rows by primary key.
int32_t id = -1;
auto del = table.del(col1 == &id, false);