#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <bits/stdc++.h>
using namespace std;

struct TxInput {
    string prev_tx;
    int index;
    string owner;
};

struct TxOutput {
    double amount;
    string address;
};

struct Transaction {
    string tx_id;
    vector<TxInput> inputs;
    vector<TxOutput> outputs;
    double fee;
};

#endif
