// Muhammad Obaidullah ( 24L-0509)
// Assignment 02- Implementation of the Data Structure Algorithms. 

#include<iostream>
#include<vector> 
using namespace std; 


class ProductRecord{ 
  private: 
       int productid; 
       string name; 
       string category;  
  public: 
      // Parametrized constructor to initialize the objects made by the class  
      ProductRecord(int pid, string name, string category){
        this->productid = pid; 
        this->name = name; 
        this->category = category; 
      }

      void printproduct(){ 
        cout << "The Product Id of the Product is : " << productid << endl; 
        cout << "The Name  of the Product is : " << name << endl; 
        cout << "The Category of the Product is : " << category << endl; 
      }

      //Implementing the "getter functions so that other classes can read the product's private data when necessary "
      int getPID(){ 
        return productid; 
      }

      string getName(){ 
        return name; 
      }

      string getCategory(){
        return category; 
      }

}; 

class TNode{ 

    friend class InventoryBST;
    private:
    int pid; 
    ProductRecord * productpointer; // here productpointer is a pointer of the type productrecord // meaning it can store the product address 
    TNode* left; 
    TNode* right; 

    public: 
    //Default constructor to parametrize the left and the right child to null values 
    TNode(){ 
        pid = 0; 
        productpointer = nullptr; 
        left = nullptr; 
        right = nullptr; 
    }

    // Parametrized Constructor to pass on the values in the Node Type of the Data 
    TNode(int pid, ProductRecord* p, TNode* l , TNode * r){ 
        this->pid = pid; 
        productpointer = p; 
        left = l; 
        right = r; 
    }

    ~TNode(){
        delete  productpointer; 
    }

}; 

class InventoryBST{
    private: 
    TNode*root; // Pointer to the root of the tree 
    int size; 

    TNode* rotateright(TNode* y ){
        TNode* x = y->left; 
        TNode*t2 = x->right; 

        //Performing the rotation 
        x->right = y; 
        y->left = t2; 

        return x; 
    }

    TNode* rotateleft(TNode *x){
        TNode* y = x->right; 
        TNode *t2 = y->left; 

        //Performing rotation 
        y->left = x; 
        x->right = t2; 

        return y; 
    }

    //Implementing recursive Insertion. The function finds the correct spot to insert, creates the new node, and then 
    // performs rotations on way back up the recursion. 
    // returning the new node of the subtree it just modified. 
    
    TNode* recursiveInsert(TNode* node, ProductRecord* recordonHeap){

        // Base Case ===> If the tree is empty 
        if(node == nullptr){ 
            size++; 
            return new TNode(recordonHeap->getPID(), recordonHeap, nullptr, nullptr); 
        }

        // 2. Recursive Step: Finding the correct path (left or right ). 
        int newPID = recordonHeap->getPID(); 

        if(newPID < node->pid){
            // Going to the left 
            node->left = recursiveInsert(node->left, recordonHeap); 
            return rotateright(node); 
        }
        else if(newPID > node->pid){ 
            node->right = recursiveInsert(node->right, recordonHeap); 
            return rotateleft(node); 
        }
        else { 
            delete recordonHeap;
            return node; 
        }
    }

    TNode* findMin(TNode* node){
        while(node!= nullptr && node->left !=nullptr){ 
            node = node->left; 
        }
        return node; 
    }
    //Implementing the Recursive Function for the Removal of the values 
    TNode* recursiveRemove(TNode* node, int pid){ 
         // 1. Base case: Item not found 
         if (node == nullptr){
            return nullptr; 
         }
         // Recursive Search to find the node 
         if(pid < node->pid){
            node->left = recursiveRemove(node->left, pid); 
         } else if(pid > node->pid){ 
            node->right = recursiveRemove(node->right, pid); 
         } else {
            // We have found the node that needs to be deleted 

            // Case 1 - No Children ( leaf node)
            if(node->left == nullptr && node->right == nullptr){
                delete node; 
                size--; 
                return nullptr; 
            }

            //Case 2 ( One child to the right )
            else if(node->left == nullptr){
                TNode* temp = node->right;
                delete node; 
                size--; 
                return temp; 
            }

            // Case 2: One child to the left 
            else if(node->right == nullptr){
                TNode* temp = node->left; 
                delete node; 
                size--; 
                return temp; 
            }
              // Case 3: Deletion through the successor 
        
                 TNode* successor = findMin(node->right); 
                 delete node->productpointer; 
                 node->pid = successor->pid; 
                 node->productpointer = nullptr; 

                 node->right = recursiveRemove(node->right, successor->pid); 
             
         }
         return node; 

     }

     void printall(TNode* node){
        if(node == nullptr){ 
            return; 
        }
        printall(node->left); 
        node->productpointer->printproduct();
        cout << "------------------------------" << endl; // Adding a seperator 
        printall(node->right); 
     }

     TNode* recursiveSearch(TNode*node, int pid, int k, int currentlevel, ProductRecord**outrecord){

        // Base Case - We have not found the node 
        if(node == nullptr){ 
            return nullptr; 
        }

        if(pid<node->pid){ 
            node->left = recursiveSearch(node->left, pid, k, currentlevel+1, outrecord); 
        }
        else if(pid > node->pid){ 
            node->right = recursiveSearch(node->right, pid, k, currentlevel+1, outrecord); 
        }
        else{ 
            *outrecord = node->productpointer; 
            return node; 
        }

        // Rotatitng the values as we tend to move upwards in the tree 
        if(*outrecord !=nullptr){
            //CHECKING THE LEVEL CONSTRAINT AND WE TEND TO ROTATE IF OUR CURRENT LEVEL IS >= the target level k 
            // and we stop rotating once the node's parent is at level k-1 
            if (currentlevel >=k ){
                if(pid < node->pid){
                    return rotateright(node); 
                }
                else{
                    return rotateleft(node); 
                }
            }
        }
        return node; 
     }

     //Detailed logic for the implementation of the organizing function here. The organize function tries to find the median value 
     // and moves it to the root here. 

     // Getting all the PIDS (Time: O(n)) 
     // - We use an in order traversal to visit the node exactly once and store these values in a vector (since we do not know the number of enteries here )
     // the vector is automatically sorted from the smallest to the largest values here. 
     // This step takes O(n) time as we tend to visit all 'n' nodes here. 

     // 2. Finding the Median 
     // - We get the middle element from the vector by using it's index pids[size/2]
     // - Accessing the vector by the index is a constant time O(1) operation. 

     // 3. Moving the median to the root 
     // We simply call the search(median PID function here to calculate the values of the new node and move it to the level 0 (the root)
     // This search and rotate tends to take O(h) time here. 

     
     void inOrder(TNode*node, vector<int>& pids){ 
        if(node == nullptr){
            return; 
        }
        inOrder(node->left, pids); 
        pids.push_back(node->pid);
        inOrder(node->right, pids); 
     }

     void clear(TNode*node){
        if(node == nullptr){
            return; 
        }
        clear(node->left);
        clear(node->right);
        delete node; 
     }

    public: 
    InventoryBST(){
        root = nullptr; 
        size = 0; 
    }


    ~InventoryBST(){
        cout << "Deleting the tree \n"; 
        clear(root); 
        cout << "Tree Deleted \n";   
    }

    ProductRecord* Search(int pid, int k){
        ProductRecord*foundrecord = nullptr; 
        root = recursiveSearch(root, pid, k,0, &foundrecord); 

        if(foundrecord !=nullptr){
            cout<< "Product " << pid << "found. Displaying the Details: " << endl; 
            foundrecord->printproduct(); 
        } else{
            cout << "Product " << pid << "not found " << endl; 

        }
        return foundrecord; 
    }
    
    void Insert(ProductRecord record ){
        ProductRecord* recordonheap = new ProductRecord(
            record.getPID(),
            record.getName(),
            record.getCategory()
        ); 

        root = recursiveInsert(root, recordonheap); 
    }

    void Remove(int pid){
        root = recursiveRemove(root, pid); 
    }


    //Printing function for printing one value 
    void print(int pid){
        TNode* current = root; 
        while(current!=nullptr){
            if(pid < current->pid){
                current = current->left; 
            }
            else if(pid > current->pid){
                current = current->right; 
            }
            else { 
                cout << "--- Product Found (PID:" << pid << ")" << endl; 
                current->productpointer->printproduct(); 
                cout << "----------------------------"<<endl; 
                return; 
            }
        }
        cout << "Product with PID" << pid << "not found " << endl; 
    }

    void printall(){
        cout << "======== Printing All Products (Sorted by PID) ====== " << endl; 
        printall(root); 
        cout << "=======================================================" << endl; 
    }
    
    void organize(){ 
        // Getting all the PIDS in a sorted list 
        vector<int> pids; 
        pids.reserve(size); // Pre allocating memory here 
        inOrder(root,pids); 
        if(size ==0 ){
            return; 
        }

        //Finding the median PID(O(1))
        int median = pids[size/2]; 

        Search(median,0); 
    }

}; 




int main(){ 
    
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
    // The tree structure is complex due to rotations.
    // Let's find 5 and move it to level 1 (a direct child of the root).
    tree.Search(5, 1);
    cout << "Tree after moving 5:" << endl;
    tree.printall();

    cout << "\n--- 5. Testing Remove ---" << endl;
    cout << "Removing PID 10 (node with one or two children)..." << endl;
    tree.Remove(10);
    tree.print(10); // Should say "not found"
    cout << "Removing PID 5 (a leaf or simple node)..." << endl;
    tree.Remove(5);
    tree.print(5); // Should say "not found"

    cout << "\nTree after removals:" << endl;
    tree.printall(); // Should show 8, 15, 20

    cout << "\n--- 6. Testing Organize ---" << endl;
    // Current PIDs: 8, 15, 20. Median (size/2) is pids[3/2] = pids[1] = 15
    tree.organize();
    
    cout << "\nTree after organizing (15 should be root):" << endl;
    tree.printall();

    cout << "\n--- 7. Testing Destructor ---" << endl;
    // The ~InventoryBST() destructor will be called automatically
    // when 'tree' goes out of scope at the end of main.
    // The "Deleting Tree" message will print if it's working.
    
    return 0; 
}
