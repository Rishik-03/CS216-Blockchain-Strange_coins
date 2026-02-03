#include <bits/stdc++.h>
#include "validator.h"
using namespace std;

bool Validator::validateTransaction(
    Transaction &tx,
    UTXOManager &utxo,
    Mempool &mempool,
    string &error
) {
    set<pair<string,int>> seen;
    double inputSum = 0, outputSum = 0;

    for (auto &in : tx.inputs) {
        pair<string,int> key = {in.prev_tx, in.index};

        if (!utxo.exists(in.prev_tx, in.index)) {
            error = "UTXO does not exist";
            return false;
        }
        if (seen.count(key)) {
            error = "Double-spend in same transaction";
            return false;
        }
        if (mempool.spentUTXOs.count(key)) {
            error = "UTXO already spent in mempool";
            return false;
        }

        seen.insert(key);
        inputSum += utxo.utxo_set[key].amount;
    }

    for (auto &out : tx.outputs) {
        if (out.amount < 0) {
            error = "Negative output amount";
            return false;
        }
        outputSum += out.amount;
    }

    if (inputSum < outputSum) {
        error = "Insufficient funds";
        return false;
    }

    tx.fee = inputSum - outputSum;
    return true;
}
