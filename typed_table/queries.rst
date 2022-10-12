Queries
=======

The :code:`INSERT`, :code:`DELETE`, :code:`SELECT` and :code:`UPDATE` statements can all be constructed directly from a
:code:`sql::TypedTable`. Calling the various :code:`select`, :code:`insert`, etc. methods will return a reusable query
object. All classes offer a C++ only interface to the underlying table. Query objects are valid as long as the table
they operate on is valid. Each type of query is documented in a separate section.

Filtering results, ordering rows, etc., can all be done by writing normal C++ expressions. The :code:`col<size_t>`
method of a typed table returns an object that represents a particular column. This object can be e.g. compared to some
value to select all rows that have that value. Details are explained in the remaining subsections.
