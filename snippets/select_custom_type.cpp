struct CustomType
{
    CustomType(int32_t id, float f, std::string s);
};

...

for (CustomType row : table.select<CustomType, 0, 1, 2>(expr))
{ ... }