sql::Statement stmt(
    db, 
    "INSERT INTO myTable VALUES (?, ?, ?)", 
    true
);

// Bind a 32-bit integer.
stmt.bindInt(0, 10);

// Bind a double.
stmt.bindDouble(1, 4.55);

// Bind text. Tell sqlite to copy it because it is 
// deallocated before the statement's lifetime ends.
const char* txt = "abcde";
stmt.bindTransientText(2, txt, 6);
delete[] txt;