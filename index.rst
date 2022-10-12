cppql
=====

.. toctree::
    :maxdepth: 3
    :titlesonly:
    :hidden:

    core
    typed_table
    queries
    error_handling

:code:`cppql` is a C++ library that wraps around the sqlite C API. It offers multiple levels of abstraction.

At the lowest level, it merely provides two classes to handle the lifetimes of database connections and statements. You
call all the C functions yourself with the handles you :code:`get` from the objects. Obviously, this is not very
interesting.

At a higher level the various classes expose a number of methods corresponding to the most common functions from the C
API. Additionally, creating tables is made a little bit easier through a more object-oriented approach. You'll still be
writing most, if not all of your own SQL statements, though.

At the highest level a fully type safe, C++ only interface is available. To select rows from a table, you write typical
C++ expressions with objects representing columns, e.g. :code:`table.select(col1 > 10)`, and iterate over the results.
Similar functionality is available for deletions, inserts, etc. Note that advanced queries, such as joins, are not
supported through this high level interface. For that, you must use the lower level functionality.

:code:`cppql` does not wrap every single C function. You might therefore find yourself having to use the internal
handles to call more obscure C functions that are not supported by the C++ layers. It also does not do e.g. exhaustive
type checking when constructing string based queries, instead returning sqlite error codes.
