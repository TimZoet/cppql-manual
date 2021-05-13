// A filter expression with dynamic parameters.
int32_t param0 = 10;
float   param1 = 4.5f;
... = table.select(col0 > &param0 && col1 <= &param1, true);

// Do stuff with query...

// Update parameters.
param0 = 20;
param1 = 13.33f;

// Do more stuff with updated query...