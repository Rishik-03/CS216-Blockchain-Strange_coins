#include <bits/stdc++.h>
#include "miner.h"
using namespace std;

void mineBlock(string miner, Mempool &mempool,
               UTXOManager &utxo, int numTx) {

    auto selected = mempool.getTopTransactions(numTx);
    double totalFees = 0;

    for (auto &tx : selected) {
        for (auto &in : tx.inputs)
            utxo.removeUTXO(in.prev_tx, in.index);

        int idx = 0;
        for (auto &out : tx.outputs)
            utxo.addUTXO(tx.tx_id, idx++, out.amount, out.address);

        totalFees += tx.fee;
        mempool.removeTransaction(tx.tx_id);
    }

    if (totalFees > 0)
        utxo.addUTXO("coinbase", rand(), totalFees, miner);

    cout << "Block mined. Miner earned "
         << fixed << setprecision(3)
         << totalFees << " BTC\n";
}
