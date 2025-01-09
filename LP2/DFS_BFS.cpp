#include<bits/stdc++.h>
using namespace std;

// TreeNode class represents a single node of the binary tree.
class TreeNode{
    private:
       int data;  // Holds the value of the node
       TreeNode* left;  // Pointer to the left child
       TreeNode* right;  // Pointer to the right child

    public:
    // Constructor to initialize a new node with data
    TreeNode(int data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }

    // Declaring BinaryTree class as a friend to access private members
    friend class BinaryTree;
};

// BinaryTree class represents the complete binary tree and has methods to perform various operations.
class BinaryTree{
    public:
        TreeNode* root = NULL;  // Root pointer of the tree
        TreeNode* temp = root;  // Temporary pointer to help while building the tree

        // Method to build the binary tree interactively by user input
        void buildTree(){
            cout << "Enter the data to be inserted: " << endl;
            int d;
            cin >> d;
            TreeNode* newNode = new TreeNode(d);  // Create a new node with user input data
            TreeNode* temp = root;  // Temporary pointer to traverse the tree

            if (root == NULL) {  // If the tree is empty, make the new node the root
                root = newNode;
                return;
            }

            // Loop to insert the node in the correct position
            while (temp->left != NULL || temp->right != NULL) {
                cout << "Enter 1 for left of : " << temp->data << endl;
                cout << "Enter 2 for right of : " << temp->data << endl;
                int ch;
                cin >> ch;
                if (ch == 1) {
                    if (temp->left == NULL) {  // If left child is NULL, insert the new node
                        temp->left = newNode;
                        return;
                    }
                    temp = temp->left;  // Move to the left child if it's already filled
                }
                else {
                    if (temp->right == NULL) {  // If right child is NULL, insert the new node
                        temp->right = newNode;
                        return;
                    }
                    temp = temp->right;  // Move to the right child if it's already filled
                }
            }

            // After the while loop, either left or right position is available, so insert the new node
            cout << "Enter 1 to left of " << temp->data << endl;
            cout << "Enter 2 to right of " << temp->data << endl;
            int ch;
            cin >> ch;
            if (ch == 1) {
                temp->left = newNode;  // Insert to the left
            } else {
                temp->right = newNode;  // Insert to the right
            }
        }

        // BFS (Breadth-First Search) - Non Recursive method using queue
        void BFS_NonRecursive(){
            queue<TreeNode*> q;  // Queue to hold nodes to process level by level
            q.push(root);
            q.push(NULL);  // Marker to denote the end of one level

            while (!q.empty()) {
                TreeNode* curr = q.front();
                q.pop();

                if (curr == NULL) {
                    cout << endl;  // End of one level, print a newline
                    if (!q.empty()) {
                        q.push(NULL);  // If there are more nodes to process, add the level marker
                    }
                } else {
                    cout << curr->data << " ";  // Print the current node's data
                    if (curr->left) {  // If left child exists, add it to the queue
                        q.push(curr->left);
                    }
                    if (curr->right) {  // If right child exists, add it to the queue
                        q.push(curr->right);
                    }
                }
            }
        }

        // DFS (Depth-First Search) - Non Recursive method using stack
        void DFS_NonRecursive(){
            if (root == NULL) {
                return;
            }

            stack<TreeNode*> st;  // Stack to hold nodes for DFS
            st.push(root);

            while (!st.empty()) {
                TreeNode* temp = st.top();  // Get the top node from the stack
                cout << temp->data << " ";  // Print the node's data
                st.pop();  // Pop the node from the stack

                if (temp->right) {  // If right child exists, push it to the stack
                    st.push(temp->right);
                }
                if (temp->left) {  // If left child exists, push it to the stack
                    st.push(temp->left);
                }
            }
        }

        // Helper function to start BFS recursively by levels
        void BFS_Helper(TreeNode* root){
            int h = height(root);  // Get the height of the tree
            for (int i = 1; i <= h; i++) {  // Perform BFS at each level
                BFS_Recursive(root, i);
            }
        }

        // Recursive BFS at a particular level
        void BFS_Recursive(TreeNode* root, int level){
            if (root == NULL) {
                return;  // Base case: If node is NULL, return
            }
            if (level == 1) {
                cout << root->data << " ";  // Print the node data at the current level
            } else if (level > 1) {
                BFS_Recursive(root->left, level - 1);  // Recursively visit left subtree
                BFS_Recursive(root->right, level - 1);  // Recursively visit right subtree
            }
        }

        // Recursive DFS method
        void DFS_Recursive(TreeNode* root){
            if (root == NULL) {
                return;  // Base case: If node is NULL, return
            }
            cout << root->data << " ";  // Print the node's data
            DFS_Recursive(root->left);  // Recursively visit left subtree
            DFS_Recursive(root->right);  // Recursively visit right subtree
        }

        // Function to calculate the height of the binary tree
        int height(TreeNode* root){
            if (root == NULL) {
                return 0;  // If the node is NULL, height is 0
            }
            int lHeight = height(root->left);  // Get height of left subtree
            int rHeight = height(root->right);  // Get height of right subtree
            return (lHeight > rHeight) ? (lHeight + 1) : (rHeight + 1);  // Return the maximum height
        }
};

// Main function that drives the program
int main(){
    BinaryTree b;  // Create a BinaryTree object
    cout << "Enter 1 to Build Tree: " << endl;
    cout << "Enter 2 for BFS Recursive: " << endl;
    cout << "Enter 3 for BFS Non Recursive: " << endl;
    cout << "Enter 4 for DFS Recursive: " << endl;
    cout << "Enter 5 for DFS Non Recursive: " << endl;

    while(true) {
        int choice;
        cout << "Enter choice: " << endl;
        cin >> choice;

        // Based on the user's choice, call the appropriate method
        if (choice == 1) {
            b.buildTree();  // Build the tree
        } else if (choice == 2) {
            cout << "BFS_Recursive: " << endl;
            b.BFS_Helper(b.root);  // Perform BFS recursively
            cout << endl;
        } else if (choice == 3) {
            cout << "BFS NonRecursive: " << endl;
            b.BFS_NonRecursive();  // Perform BFS non-recursively
            cout << endl;
        } else if (choice == 4) {
            cout << "DFS Recursive: " << endl;
            b.DFS_Recursive(b.root);  // Perform DFS recursively
            cout << endl;
        } else if (choice == 5) {
            cout << "DFS Non Recursive: " << endl;
            b.DFS_NonRecursive();  // Perform DFS non-recursively
            cout << endl;
        } else {
            cout << "Enter the valid choice" << endl;  // Handle invalid input
        }
    }
    return 0;
}