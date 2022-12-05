Transaction
===========

The :code:`sql::Transaction` class can be used to manage the lifetime of a transaction. It is constructed using the
:code:`beginTransaction` of a :code:`sql::Database`. After running all statements that are to be part of the
transaction, it can be committed by calling the :code:`commit` method.

.. code-block:: cpp

    sql::Database& db = ...;
    
    // Begin transaction.
    auto transaction = db.beginTransaction(sql::Transaction::Type::Deferred);
    
    // Do stuff.
    ...
    
    // Finalize transaction.
    transaction.commit();

Should anything fail and the :code:`commit` call not be reached, the transaction will automatically rollback in its
destructor.

.. code-block:: cpp

    auto transaction = db.beginTransaction(sql::Transaction::Type::Deferred);
    
    // Assume doing stuff causes a throw.
    ...
    
    // Commit is not reached and ~Transaction() automatically does a rollback.
    transaction.commit();

A transaction can also be rolled back explicitly using the :code:`rollback` method.

.. code-block:: cpp

    sql::Database& db = ...;
    
    {
        auto transaction = db.beginTransaction(sql::Transaction::Type::Deferred);
        ...

        // Or explicitly rollback.
        if (!happyWithResults())
            transaction.rollback();
        else
            transaction.commit();
    }