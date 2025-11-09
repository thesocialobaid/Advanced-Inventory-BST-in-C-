🌳 Advanced Inventory BST (C++ Splay-like Tree)

A C++ implementation of a specialized Binary Search Tree (BST) designed to simulate an efficient inventory management system.
Developed as a Data Structures and Algorithms course assignment.

Unlike a standard BST, this version includes self-adjusting operations inspired by splay trees, optimizing for frequently accessed items.

⚡ Overview
Unique Features:

Move-to-Root on Insert
Newly inserted nodes are automatically rotated to the root.

Move-to-Level on Search
Searched nodes are moved to a specified level k, keeping "hot" items near the top for faster future access.

Linear-Time Organize
Implements an O(n) rebalancing method that moves the median node to the root.

🚀 Key Features

The InventoryBST class manages ProductRecord objects and implements a full suite of self-adjusting tree operations:

Insert(ProductRecord record)

Inserts a new product and rotates it all the way to the root.

Search(int pid, int k)

Searches for a product by its pid and moves it up to level k:

k = 0: Moves the node to the root (like a splay).
k = 1: Moves the node to be a direct child of the root.

If k is deeper than the node's level, it remains unmoved.

Organize()

Rebalances the tree in O(n) time:

Collects all PIDs via in-order traversal.

Finds the median PID.

Moves that node to the root, balancing around the true median.

Remove(int pid)

Implements standard BST removal, handling all three cases (0, 1, or 2 children).
If a node has two children, it is replaced by its in-order successor.

Print(int pid)

Prints details of a single product record.

PrintAll()

Performs a full in-order traversal and prints all products (sorted by PID).

🧱 Class Structure
ProductRecord

A simple class storing:

int productid;
string name;
string category;

TNode

Represents a tree node:

int pid;
ProductRecord* record;
TNode* left;
TNode* right;

InventoryBST

Encapsulates the full logic:

Root pointer and tree size

Recursive helpers

Rotations and memory management

Full destructor for cleanup

💻 Getting Started
✅ Prerequisites

You’ll need a C++ compiler, such as g++.

🧩 Compilation & Execution
# Compile
g++ main.cpp -o inventory

# Run
./inventory

🧪 Example main.cpp
#include <iostream>
#include <vector>
#include <string>

// ... (Paste all 3 classes: ProductRecord, TNode, InventoryBST) ...

int main() {
    InventoryBST tree;
    cout << "--- 1. Testing Insert (and move-to-root) ---" << endl;

    tree.Insert(ProductRecord(10, "Laptop", "Electronics"));
    tree.Insert(ProductRecord(5, "Mouse", "Peripherals"));
    tree.Insert(ProductRecord(20, "Keyboard", "Peripherals"));
    tree.Insert(ProductRecord(15, "Monitor", "Electronics"));
    tree.Insert(ProductRecord(8, "Webcam", "Peripherals"));

    cout << "\n--- 2. Testing PrintAll ---" << endl;
    cout << "Items should be sorted: 5, 8, 10, 15, 20" << endl;
    tree.PrintAll();

    cout << "\n--- 3. Testing Print (Single Item) ---" << endl;
    cout << "Finding PID 15:" << endl;
    tree.Print(15);
    
    cout << "\nFinding PID 99 (Not Found):" << endl;
    tree.Print(99);

    cout << "\n--- 4. Testing Search (Move 5 to level 1) ---" << endl;
    tree.Search(5, 1);
    cout << "Tree after moving 5:" << endl;
    tree.PrintAll();

    cout << "\n--- 5. Testing Remove ---" << endl;
    cout << "Removing PID 10..." << endl;
    tree.Remove(10);
    tree.Print(10);
    
    cout << "\nRemoving PID 5..." << endl;
    tree.Remove(5);
    tree.Print(5);

    cout << "\nTree after removals:" << endl;
    tree.PrintAll();

    cout << "\n--- 6. Testing Organize ---" << endl;
    tree.Organize();
    cout << "\nTree after organizing (median at root):" << endl;
    tree.PrintAll();

    cout << "\n--- 7. Testing Destructor ---" << endl;
    return 0;
}

🧑‍💻 Author

Muhammad Obaidullah (24L-0509)
🎓 FAST-NUCES Lahore | 💡 DSA Project | ⚙️ Implemented in C++
