# CS216 – Blockchain Simulation Assignment (UTXO Model)

## Overview
This project is a simplified blockchain simulation implemented in **C++** using the **UTXO (Unspent Transaction Output)** model.  
It demonstrates how transactions are created, validated, stored in a mempool, mined into blocks, and how balances are updated securely.

The implementation follows a **modular design**, where each blockchain component is separated into its own header (`.h`) and source (`.cpp`) file.

---

## Repository Structure
CS216/
│
├── src/
│ ├── main.cpp # Entry point of the program
│ ├── utxo_manager.h/.cpp # UTXO set management
│ ├── transaction.h # Transaction structure
│ ├── mempool.h/.cpp # Pending transaction pool
│ ├── validator.h/.cpp # Transaction validation logic
│ ├── miner.h/.cpp # Mining and block reward logic
│
├── tests/
│ ├── tests.h/.cpp # All 10 mandatory test scenarios
│
├── .gitignore
├── README.md
├── requirements.txt
├── sample_output.txt

---

## Design Explanation (Core Components)

### 1. UTXO Manager (`utxo_manager`)
- Maintains a map of all **unspent outputs**
- Key: `(transaction_id, output_index)`
- Value: `{amount, owner}`
- Responsibilities:
  - Add UTXOs after mining
  - Remove UTXOs when spent
  - Calculate balance of any user
  - Track ownership securely

 **Why UTXO?**  
UTXO ensures no double spending and allows simple balance calculation by summing unspent outputs.

---

### 2. Transaction (`transaction`)
- Represents a transaction with:
  - Inputs (references to previous UTXOs)
  - Outputs (new owners + amounts)
  - Transaction ID
- Transactions are immutable once created.

---

### 3. Validator (`validator`)
- Verifies transactions before entering the mempool:
  - Checks if referenced UTXOs exist
  - Ensures sender owns the UTXOs
  - Prevents double spending
  - Ensures total input ≥ total output

 Invalid transactions are **rejected immediately**.

---

### 4. Mempool (`mempool`)
- Temporary holding area for **valid but unmined transactions**
- Only validated transactions are added
- Cleared once a block is mined

---

### 5. Miner (`miner`)
- Selects transactions from the mempool
- Applies them to the UTXO set
- Creates a **coinbase transaction**
- Rewards miner with block reward

 Miner earns by receiving newly created UTXOs (block reward).

---

### 6. Test Scenarios (`tests`)
- Contains **10 mandatory test cases**
- Each test is labeled clearly (e.g., *Test 1 – Valid Transaction*)
- User can:
  - Run a single test
  - Run all tests together
- Tests verify:
  - Balance updates
  - Validation failures
  - Mempool behavior
  - Miner rewards

---

## Program Flow
1. Initialize UTXO set with genesis balances
2. User selects test scenario
3. Transactions are created
4. Validator checks transactions
5. Valid transactions enter mempool
6. Miner mines a block
7. UTXO set updates
8. Balances are printed

---

## Compilation Instructions
Run from the **project root directory**:

--- To run the code ----
g++ -std=gnu++17 src/main.cpp src/utxo_manager.cpp src/mempool.cpp src/validator.cpp src/miner.cpp tests/tests.cpp -o blockchain && blockchain
