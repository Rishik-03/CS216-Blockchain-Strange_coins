#include <bits/stdc++.h>
#include "utxo_manager.h"
using namespace std;

void UTXOManager::addUTXO(string tx_id, int index, double amount, string owner) {
    utxo_set[{tx_id, index}] = {amount, owner};
}

void UTXOManager::removeUTXO(string tx_id, int index) {
    utxo_set.erase({tx_id, index});
}

bool UTXOManager::exists(string tx_id, int index) {
    return utxo_set.count({tx_id, index});
}

double UTXOManager::getBalance(string owner) {
    double sum = 0;
    for (auto &u : utxo_set)
        if (u.second.owner == owner)
            sum += u.second.amount;
    return sum;
}

vector<pair<string,int>> UTXOManager::getUTXOsForOwner(string owner) {
    vector<pair<string,int>> res;
    for (auto &u : utxo_set)
        if (u.second.owner == owner)
            res.push_back(u.first);
    return res;
}

void UTXOManager::printUTXOs() {
    cout << "\n--- UTXO SET ---\n";
    for (auto &u : utxo_set)
        cout << "(" << u.first.first << "," << u.first.second << ") "
             << u.second.owner << " : "
             << fixed << setprecision(3)
             << u.second.amount << " BTC\n";
}
set<string> UTXOManager::getAllOwners() {
    set<string> owners;
    for (auto &u : utxo_set)
        owners.insert(u.second.owner);
    return owners;
}

