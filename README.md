Advanced Inventory BST (C++ Splay-like Tree)
This project is a C++ implementation of a specialized Binary Search Tree (BST) built to simulate an efficient inventory management system. It was developed as a Data Structures and Algorithms course assignment.

Unlike a standard BST, this implementation includes unique self-adjusting operations inspired by splay trees to optimize for frequently accessed items:

Move-to-Root on Insert: Newly inserted nodes are automatically rotated to become the new root.

Move-to-Level on Search: Searched nodes are moved to a specified level k, keeping "hot" items near the top for faster subsequent access.

Linear-Time Organize: Features an O(n) Organize function that finds and moves the tree's median item to the root to restore balance.

🚀 Key Features
The InventoryBST class manages ProductRecord objects and implements a full suite of self-adjusting tree operations.

Insert(ProductRecord record)
Inserts a new product into the tree. After insertion, the new node is rotated all the way to the root, based on the assumption that a newly added item is likely to be accessed again soon.

Search(int pid, int k)
Searches for a product by its pid. If found, the node is moved to level k using a series of rotations on the search path.

k = 0: Moves the node to the root (identical to a splay operation).

k = 1: Moves the node to be a direct child of the root.

If k is deeper than the node's current level, the node is found but not moved.

Organize()
A special linear-time O(n) operation to re-balance the tree.

Performs an O(n) in-order traversal to collect all PIDs in a sorted vector.

Finds the median PID from the vector (an O(1) operation).

Calls Search(medianPID, 0) to move the median node to the root, effectively re-balancing the tree around its true center.

Remove(int pid)
Implements a standard BST node removal, correctly handling all three deletion cases (0, 1, or 2 children). When a node with two children is removed, it is replaced by its in-order successor (the minimum value in the right subtree).

Print(int pid)
Searches for and prints the details of a single product record.

PrintAll()
Performs a full in-order traversal to print all products in the inventory, guaranteed to be in sorted order by their pid.

🛠️ Class Structure
ProductRecord

A simple data class to store product information: productid, name, and category.

TNode

The node class for the BST. It stores the pid directly (for fast comparisons) and a ProductRecord* pointer to the full data object on the heap.

InventoryBST

The main tree class that encapsulates all logic. It manages the root pointer, size, and all private helper functions for recursion, rotations, and memory management (including a full destructor for cleanup).

💻 Getting Started
Prerequisites
You need a C++ compiler, such as g++.

Compilation & Running
Save all the code (all classes and the main function) into a single file named main.cpp.

Open your terminal and compile the program:

Bash

g++ main.cpp -o inventory
Run the executable:

Bash

./inventory
Example main.cpp
Here is the test main function included in the file, which demonstrates all the features.

C++

#include <iostream>
#include <vector>
#include <string>

// ... (Paste all 3 classes: ProductRecord, TNode, InventoryBST) ...

int main() {
    InventoryBST tree;
    cout << "--- 1. Testing Insert (and move-to-root) ---" << endl;
    
    // Insertions will cause rotations. The last item inserted (8) will be the root.
    tree.Insert(ProductRecord(10, "Laptop", "Electronics"));
    tree.Insert(ProductRecord(5, "Mouse", "Peripherals"));
    tree.Insert(ProductRecord(20, "Keyboard", "Peripherals"));
    tree.Insert(ProductRecord(15, "Monitor", "Electronics"));
    tree.Insert(ProductRecord(8, "Webcam", "Peripherals"));

    cout << "\n--- 2. Testing PrintAll ---" << endl;
    cout << "Items should be sorted: 5, 8, 10, 15, 20" << endl;
    tree.printall();

    cout << "\n--- 3. Testing Print (Single Item) ---" << endl;
    cout << "Finding PID 15:" << endl;
    tree.print(15);
    
    cout << "\nFinding PID 99 (Not Found):" << endl;
    tree.print(99);

    cout << "\n--- 4. Testing Search (Move 5 to level 1) ---" << endl;
    // Let's find 5 and move it to level 1 (a direct child of the root).
    tree.Search(5, 1);
    cout << "Tree after moving 5:" << endl;
    tree.printall();

    cout << "\n--- 5. Testing Remove ---" << endl;
    cout << "Removing PID 10..." << endl;
    tree.Remove(10);
    tree.print(10); // Should say "not found"
    
    cout << "\nRemoving PID 5..." << endl;
    tree.Remove(5);
    tree.print(5); // Should say "not found"

    cout << "\nTree after removals:" << endl;
    tree.printall(); // Should show 8, 15, 20

    cout << "\n--- 6. Testing Organize ---" << endl;
    // Current PIDs: 8, 15, 20. Median is 15.
    tree.organize();
    
    cout << "\nTree after organizing (15 should be root):" << endl;
    tree.printall();

    cout << "\n--- 7. Testing Destructor ---" << endl;
    // Destructor is called automatically when 'main' ends.
    
    return 0; 
}
🧑‍💻 Author
Muhammad Obaidullah (24L-0509)
