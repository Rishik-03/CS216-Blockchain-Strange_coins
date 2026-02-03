#ifndef UTXO_MANAGER_H
#define UTXO_MANAGER_H

#include <bits/stdc++.h>
#include "utxo.h"
using namespace std;

class UTXOManager {
public:
    map<pair<string,int>, UTXO> utxo_set;
    set<string> getAllOwners();

    void addUTXO(string tx_id, int index, double amount, string owner);
    void removeUTXO(string tx_id, int index);
    bool exists(string tx_id, int index);
    double getBalance(string owner);
    vector<pair<string,int>> getUTXOsForOwner(string owner);
    void printUTXOs();
};

#endif
