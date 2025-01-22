#include <bits/stdc++.h>
using namespace std;
#define N 3  // Define the size of the puzzle (3x3 grid)

// Node class to represent each state of the puzzle
class Node{
public:
    Node *parent;  // Pointer to the parent node
    int mat[N][N]; // Matrix representing the current state of the puzzle
    int x, y;      // Coordinates of the blank space (0)
    int cost;      // The cost (heuristic) for the node
    int level;     // Level of the node (depth in the search tree)
};

// Function to print the puzzle matrix along with the cost and heuristic values
int printMatrix(int mat[N][N], int& steps, int g, int h){ 
    steps++;  // Increment the step count
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cout<<mat[i][j]<<" ";  // Print the matrix element
        }
        cout<<endl;
    }
    cout<<"f(n) = "<<g+h<<" g(n) = "<<g<<" h(n) = "<<h<<endl; // Print f(n), g(n), h(n)
}

// Function to create a new node by moving the blank space
Node *newNode(int mat[N][N], int x, int y, int newX,
              int newY, int level, Node *parent){
    Node *node = new Node;  // Allocate memory for the new node
    node->parent = parent;  // Set the parent node
    memcpy(node->mat, mat, sizeof node->mat);  // Copy the matrix from the parent
    swap(node->mat[x][y], node->mat[newX][newY]);  // Swap the blank space with the new position
    node->cost = INT_MAX;  // Initialize the cost to a very large value
    node->level = level;   // Set the level (depth)
    node->x = newX;        // Update the x-coordinate of the blank space
    node->y = newY;        // Update the y-coordinate of the blank space
    return node;  // Return the new node
}

// Directional movement for the blank space (up, left, down, right)
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

// Function to calculate the cost (heuristic) based on the number of misplaced tiles
int calculateCost(int initial[N][N], int final[N][N]){
    int count = 0;  // Initialize the count of misplaced tiles
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (initial[i][j] && initial[i][j] != final[i][j]){
                count++;  // Increment count if the tile is misplaced
            }
        }
    }
    return count;  // Return the count of misplaced tiles
}

// Function to check if a move is safe (within bounds of the matrix)
int isSafe(int x, int y){
    return (x >= 0 && x < N && y >= 0 && y < N);  // Ensure the coordinates are within the grid bounds
}

// Function to print the path from the root node to the solution
void printPath(Node *root, int &steps){
    if (root == NULL)  // Base case: if the root is NULL, return
        return;
    printPath(root->parent,steps);  // Recursively print the path of the parent node
    printMatrix(root->mat,steps,root->level,root->cost);  // Print the current state
    cout<<endl;
}

// Comparator for the priority queue to prioritize nodes based on f(n) = g(n) + h(n)
struct comp{
    bool operator()(const Node *lhs, const Node *rhs) const{
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);  // Prioritize by f(n)
    }
};

// Function to solve the puzzle using A* search
void solve(int initial[N][N], int x, int y,
           int final[N][N]){
    int steps = 0;  // Initialize step count
    priority_queue<Node *, std::vector<Node *>, comp> pq;  // Priority queue to store nodes (sorted by f(n))
    
    // Create the root node and set the initial cost (heuristic)
    Node *root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);  // Calculate the initial heuristic cost
    pq.push(root);  // Push the root node into the priority queue
    
    // A* search loop
    while (!pq.empty()){
        Node *min = pq.top();  // Get the node with the lowest f(n)
        pq.pop();  // Remove it from the priority queue
        
        // If the cost is zero, the puzzle is solved
        if (min->cost == 0){
            printPath(min,steps);  // Print the path to the solution
            cout<<"Total Steps: "<<steps<<endl;  // Print the total number of steps
            return;
        }
        
        // Generate children by moving the blank space in all four directions
        for (int i = 0; i < 4; i++){
            if (isSafe(min->x + row[i], min->y + col[i])){  // Check if the move is safe
                // Create a new node with the moved blank space
                Node *child = newNode(min->mat, min->x,
                                      min->y, min->x + row[i],
                                      min->y + col[i],
                                      min->level + 1, min);
                child->cost = calculateCost(child->mat, final);  // Calculate the heuristic cost of the new state
                pq.push(child);  // Push the new node into the priority queue
            }
        }
    }
}

// Main function to get input and start the solving process
int main()
{
    int x = 0, y = 0;  // Initialize coordinates of the blank space
    int initial[N][N];  // Matrix to store the initial state
    cout << "Enter initial state: " << endl;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> initial[i][j];  // Read initial state
            if (initial[i][j] == 0){
                x = i;  // Find the coordinates of the blank space
                y = j;
            }
        }
    }
    cout<<endl;
    int final[N][N];  // Matrix to store the final state
    cout << "Enter final state: " << endl;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> final[i][j];  // Read final state
        }
    }
    cout<<endl;
    solve(initial, x, y, final);  // Solve the puzzle

    return 0;
}
