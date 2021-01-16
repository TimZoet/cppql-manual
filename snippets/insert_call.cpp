// Insert separate values.
insert(1, 10.0f, "abc"s);

// Insert tuple.
auto row = std::make_tuple<int64_t, float, std::string>(
    2, 20.0f, "def"s);
insert(row);