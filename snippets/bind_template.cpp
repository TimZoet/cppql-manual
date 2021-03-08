const char* txt = new char[6]{"abcde"};
auto dest = [](void* p){delete[] static_cast<const char*>(p);}
stmt.bind(
    0,
    10,
    4.55,
    sql::Text{.data = txt, .size = 6, .destructor = dest}
);