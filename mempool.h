#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <bits/stdc++.h>
#include "transaction.h"
#include "utxo_manager.h"
using namespace std;

class Mempool {
public:
    vector<Transaction> transactions;
    set<pair<string,int>> spentUTXOs;

    bool addTransaction(Transaction &tx, UTXOManager &utxo, string &msg);
    vector<Transaction> getTopTransactions(int n);
    void removeTransaction(string tx_id);
    void printMempool();
};

#endif
