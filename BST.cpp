#include <iostream>
#include <climits>
#include <algorithm> // for min
#include <cstdlib>   // for abs
using namespace std;

// ===============================
// Binary Search Tree (BST) Node
// ===============================
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// =============================================
// Create a new node with the given integer data
// =============================================
struct node* newNode(int data) {
    struct node* node = new struct node;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// ==============================================
// Insert a new value into the BST (recursive)
// ==============================================
void insert(struct node** rootRef, int data) {
    if (*rootRef == NULL) {
        *rootRef = newNode(data);
    } else if (data <= (*rootRef)->data) {
        insert(&((*rootRef)->left), data);
    } else {
        insert(&((*rootRef)->right), data);
    }
}

// ===============================================
// Compute total number of nodes in the BST
// ===============================================
int size(struct node* root) {
    if (root == NULL) return 0;
    return size(root->left) + size(root->right) + 1;
}

// ===============================================
// Compute maximum depth (height) of the BST
// ===============================================
int maxDepth(struct node* root) {
    if (root == NULL) return 0;
    int lheight = maxDepth(root->left);
    int rheight = maxDepth(root->right);
    return (lheight > rheight ? lheight : rheight) + 1;
}

// ===============================================
// In-order traversal
// ===============================================
void printTreeInOrder(struct node* root) {
    if (root == NULL) return;
    printTreeInOrder(root->left);
    cout << root->data << " ";
    printTreeInOrder(root->right);
}

// ===============================================
// Pre-order traversal
// ===============================================
void printTreePreOrder(struct node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    printTreePreOrder(root->left);
    printTreePreOrder(root->right);
}

// ===============================================
// Post-order traversal
// ===============================================
void printTreePostOrder(struct node* root) {
    if (root == NULL) return;
    printTreePostOrder(root->left);
    printTreePostOrder(root->right);
    cout << root->data << " ";
}

// ===============================================
// Lookup a value in the BST
// ===============================================
bool lookup(struct node* root, int target) {
    if (root == NULL) return false;
    if (root->data == target)
        return true;
    else if (target < root->data)
        return lookup(root->left, target);
    else
        return lookup(root->right, target);
}

// ===============================================
// Find maximum and minimum values
// ===============================================
int findMaxValue(struct node* root) {
    if (root == NULL) return -1;
    if (root->right == NULL) return root->data;
    return findMaxValue(root->right);
}

int findMinValue(struct node* root) {
    if (root == NULL) return -1;
    if (root->left == NULL) return root->data;
    return findMinValue(root->left);
}

int findMinValueNoRecursive(struct node* root) {
    if (root == NULL) return -1;
    struct node* temp = root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp->data;
}

// ===============================================
// 1. Find the kth largest element in the BST
// ===============================================
struct node* findKthLargest(struct node* root, int k) {
    static int count = 0;
    static struct node* result = NULL;

    if (root == NULL || result != NULL) return result;

    result = findKthLargest(root->right, k);
    if (result != NULL) return result;

    count++;
    if (count == k) return root;

    return findKthLargest(root->left, k);
}

// ===============================================
// 2. Find minimum absolute difference between any
//     two node values in the BST
// ===============================================
int getMinimumDifference(struct node* root) {
    static int minDiff = INT_MAX;
    static int prev = -1;

    if (root == NULL) return minDiff;

    getMinimumDifference(root->left);

    if (prev != -1)
        minDiff = min(minDiff, abs(root->data - prev));
    prev = root->data;

    getMinimumDifference(root->right);

    return minDiff;
}

// ===============================================
// 3. Delete a node by value
// ===============================================
struct node* findMinValueNode(struct node* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

struct node* deleteNode(struct node** rootRef, int data) {
    struct node* root = *rootRef;
    if (root == NULL) return NULL;

    if (data < root->data) {
        return deleteNode(&(root->left), data);
    }
    else if (data > root->data) {
        return deleteNode(&(root->right), data);
    }
    else {
        struct node* deleted = root;

        if (root->left == NULL && root->right == NULL) {
            *rootRef = NULL;
        }
        else if (root->left == NULL) {
            *rootRef = root->right;
        }
        else if (root->right == NULL) {
            *rootRef = root->left;
        }
        else {
            struct node* successor = findMinValueNode(root->right);
            root->data = successor->data;
            deleteNode(&(root->right), successor->data);
            deleted = root;
        }

        return deleted;
    }
}

// ===============================================
// 4. Delete all nodes
// ===============================================
void deleteTree(struct node** rootRef) {
    if (*rootRef == NULL) return;

    deleteTree(&((*rootRef)->left));
    deleteTree(&((*rootRef)->right));

    delete *rootRef;
    *rootRef = NULL;
}

int main() {
    struct node* root = NULL;

    int values[] = { -5, -4, -1, 1, 41, 20, 11, 90, 29, 32, 65, 70, 30, 75};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; ++i)
        insert(&root, values[i]);

    cout << "In-Order: ";  printTreeInOrder(root);  cout << endl;
    cout << "Tree size: " << size(root) << ", Height: " << maxDepth(root) << endl;

    // Find kth largest
    int k = 3;
    struct node* kth = findKthLargest(root, k);
    if (kth) cout << "\n3rd largest value: " << kth->data << endl;

    // Minimum absolute difference
    cout << "Minimum absolute difference: " << getMinimumDifference(root) << endl;

    // Delete node
    cout << "\nDeleting node with value 20..." << endl;
    struct node* deleted = deleteNode(&root, 20);
    if (deleted != NULL){
      cout << "Deleted node had value: " << deleted->data << endl;
      cout << "After deletion (In-Order): ";  printTreeInOrder(root);  cout << endl;
    }

    // Cleanup all nodes
    cout << "\nDeleting all nodes..." << endl;
    deleteTree(&root);
    if(root == NULL)
      cout << "Tree successfully cleared." << endl;
    else
      cout << "Error: Tree not cleared." << endl;

    return 0;
}

