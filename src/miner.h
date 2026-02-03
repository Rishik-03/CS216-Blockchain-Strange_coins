#ifndef MINER_H
#define MINER_H

#include <bits/stdc++.h>
#include "mempool.h"
#include "utxo_manager.h"
using namespace std;

void mineBlock(string miner, Mempool &mempool,
               UTXOManager &utxo, int numTx = 5);

#endif
