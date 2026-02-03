#include <bits/stdc++.h>
#include "utxo_manager.h"
#include "mempool.h"
#include "miner.h"
#include "tests.h"
using namespace std;

string generateTxID() {
    static int c = 0;
    return "tx_" + to_string(++c);
}

int main() {
    UTXOManager utxo;
    Mempool mempool;

    // -------- Genesis UTXOs --------
    utxo.addUTXO("genesis",0,50,"Alice");
    utxo.addUTXO("genesis",1,30,"Bob");
    utxo.addUTXO("genesis",2,20,"Charlie");
    utxo.addUTXO("genesis",3,10,"David");
    utxo.addUTXO("genesis",4,5,"Eve");

    while (true) {
        cout << "\n=== Bitcoin Transaction Simulator ===\n";
        cout << "1. Create new transaction\n";
        cout << "2. View UTXO set\n";
        cout << "3. View mempool\n";
        cout << "4. Mine block\n";
        cout << "5. Run test cases\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        /* -------- CREATE TRANSACTION -------- */
        if (choice == 1) {
            auto users = utxo.getAllOwners();

            cout << "\nAvailable users:\n";
            for (auto &u : users)
                cout << "- " << u << " (Balance: "
                     << utxo.getBalance(u) << " BTC)\n";

            string sender, receiver;
            double amount;

            cout << "\nEnter sender: ";
            cin >> sender;
            if (!users.count(sender)) {
                cout << "Invalid sender.\n";
                continue;
            }

            cout << "Enter receiver: ";
            cin >> receiver;

            cout << "Enter amount (BTC): ";
            cin >> amount;

            Transaction tx;
            tx.tx_id = generateTxID();

            double collected = 0;
            auto utxos = utxo.getUTXOsForOwner(sender);

            for (auto &u : utxos) {
                tx.inputs.push_back({u.first, u.second, sender});
                collected += utxo.utxo_set[u].amount;
                if (collected >= amount + 0.001)
                    break;
            }

            if (collected < amount) {
                cout << "Insufficient funds.\n";
                continue;
            }

            tx.outputs.push_back({amount, receiver});

            double change = collected - amount - 0.001;
            if (change > 0)
                tx.outputs.push_back({change, sender});

            string msg;
            if (mempool.addTransaction(tx, utxo, msg)) {
                cout << "Transaction added to mempool\n";
                cout << "TxID: " << tx.tx_id << "\n";
                cout << "Fee: " << fixed << setprecision(3)
                     << tx.fee << " BTC\n";
            } else {
                cout << "Transaction rejected: " << msg << "\n";
            }
        }

        /* -------- VIEW UTXO -------- */
        else if (choice == 2) {
            utxo.printUTXOs();
        }

        /* -------- VIEW MEMPOOL -------- */
        else if (choice == 3) {
            mempool.printMempool();
        }

        /* -------- MINE BLOCK -------- */
        else if (choice == 4) {
            string miner;
            cout << "Enter miner name: ";
            cin >> miner;
            mineBlock(miner, mempool, utxo);
        }

        /* -------- TEST CASES -------- */
        else if (choice == 5) {
            testMenu();
        }

        /* -------- EXIT -------- */
        else if (choice == 6) {
            break;
        }

        else {
            cout << "Invalid choice\n";
        }
    }

    return 0;
}
