#include <bits/stdc++.h>
#include "../src/utxo_manager.h"
#include "../src/mempool.h"
#include "../src/miner.h"
#include "../src/validator.h"
using namespace std;

static UTXOManager utxo;
static Mempool mempool;
static bool init = false;

string testName(int t) {
    string names[] = {
        "",
        "Basic valid transaction",
        "Multiple-input transaction",
        "Double spend in same transaction",
        "Mempool double spend",
        "Insufficient funds",
        "Negative output amount",
        "Zero-fee transaction",
        "Fee-priority mining",
        "Miner reward validation",
        "Unconfirmed output spending"
    };
    return names[t];
}

void initGenesis() {
    if (init) return;
    init = true;
    utxo.addUTXO("genesis",0,50,"Alice");
    utxo.addUTXO("genesis",1,30,"Bob");
    utxo.addUTXO("genesis",2,20,"Charlie");
    utxo.addUTXO("genesis",3,10,"David");
    utxo.addUTXO("genesis",4,5,"Eve");
}

void runTest(int t) {
    initGenesis();
    string msg;

    cout << "\n==============================\n";
    cout << "TEST " << t << ": " << testName(t) << "\n";
    cout << "==============================\n";

    if (t == 1) {
        Transaction tx{"T1",{{"genesis",0,"Alice"}},{{10,"Bob"},{39.999,"Alice"}}};
        mempool.addTransaction(tx, utxo, msg);
        mempool.printMempool();
        mineBlock("Miner1", mempool, utxo);
    }
    else if (t == 4) {
        Transaction a{"T4a",{{"genesis",4,"Eve"}},{{2,"Bob"}}};
        Transaction b{"T4b",{{"genesis",4,"Eve"}},{{2,"Alice"}}};
        mempool.addTransaction(a, utxo, msg);
        mempool.printMempool();
        if (!mempool.addTransaction(b, utxo, msg))
            cout << "Rejected: " << msg << "\n";
        mineBlock("Miner2", mempool, utxo);
    }

    utxo.printUTXOs();
}

void testMenu() {
    cout << "\nChoose test case:\n";
    for (int i = 1; i <= 10; i++)
        cout << i << ". " << testName(i) << "\n";
    cout << "11. Run ALL\nChoice: ";

    int c; cin >> c;
    if (c >= 1 && c <= 10) runTest(c);
    else if (c == 11)
        for (int i = 1; i <= 10; i++) runTest(i);
}
