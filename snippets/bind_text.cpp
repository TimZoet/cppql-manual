auto stmt = db->createStatement(
    "INSERT INTO myTable VALUES (?, ?, ?);", 
    true);

// Pass text into function together with delete function.
const char* txt0 = "abcde";
stmt.bindText(0, txt0, 6, 
    [](void* p){ delete[] static_cast<const char*>(p); });

// Tell sqlite to copy text because it is 
// deallocated before the statement's lifetime ends.
{
    std::string txt1 = "abcde";
    stmt.bindTransientText(1, txt1);
}

// Assuming myString will not go out of scope 
// before stmt, we can bind it like this.
stmt.bindStaticText(2, myString);