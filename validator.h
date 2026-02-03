#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <bits/stdc++.h>
#include "transaction.h"
#include "utxo_manager.h"
#include "mempool.h"
using namespace std;

class Validator {
public:
    static bool validateTransaction(
        Transaction &tx,
        UTXOManager &utxo,
        Mempool &mempool,
        string &error
    );
};

#endif
