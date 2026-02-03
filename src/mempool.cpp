#include <bits/stdc++.h>
#include "mempool.h"
#include "validator.h"
using namespace std;

bool Mempool::addTransaction(Transaction &tx, UTXOManager &utxo, string &msg) {
    if (!Validator::validateTransaction(tx, utxo, *this, msg))
        return false;

    for (auto &in : tx.inputs)
        spentUTXOs.insert({in.prev_tx, in.index});

    transactions.push_back(tx);
    msg = "Transaction accepted";
    return true;
}

vector<Transaction> Mempool::getTopTransactions(int n) {
    vector<Transaction> temp = transactions;
    sort(temp.begin(), temp.end(),
         [](const Transaction &a, const Transaction &b) {
             return a.fee > b.fee;
         });
    if ((int)temp.size() > n)
        temp.resize(n);
    return temp;
}

void Mempool::removeTransaction(string tx_id) {
    for (auto &tx : transactions)
        if (tx.tx_id == tx_id)
            for (auto &in : tx.inputs)
                spentUTXOs.erase({in.prev_tx, in.index});

    transactions.erase(
        remove_if(transactions.begin(), transactions.end(),
                  [&](Transaction &t){ return t.tx_id == tx_id; }),
        transactions.end());
}

void Mempool::printMempool() {
    cout << "\n--- MEMPOOL ---\n";
    for (auto &tx : transactions)
        cout << tx.tx_id << " | Fee: "
             << fixed << setprecision(3)
             << tx.fee << " BTC\n";
}
