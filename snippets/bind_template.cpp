const char* txt = new char[6]{"abcde"};
stmt.bind(
    0,
    10,
    4.55,
    sql::Text{
        txt,
        6, 
        [](void* p){ delete[] static_cast<const char*>(p); }
    }
);