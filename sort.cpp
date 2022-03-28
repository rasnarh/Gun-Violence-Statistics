#include<stdio.h>
#include<stdlib.h>

/* A Binary Tree node */
struct TNode
{
    int data;
    struct TNode* left;
    struct TNode* right;
};

struct TNode* newNode(int data);

/* A function that constructs Balanced Binary Search Tree from a sorted array */
struct TNode* sortedArrayToBST(int arr[], int start, int end)
{
    /* Base Case */
    if (start > end)
      return NULL;

    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    struct TNode *root = newNode(arr[mid]);

    /* Recursively construct the left subtree and make it
       left child of root */
    root->left =  sortedArrayToBST(arr, start, mid-1);

    /* Recursively construct the right subtree and make it
       right child of root */
    root->right = sortedArrayToBST(arr, mid+1, end);

    return root;
}

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct TNode* newNode(int data)
{
    struct TNode* node = (struct TNode*)
                         malloc(sizeof(struct TNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/* A utility function to print preorder traversal of BST */
void preOrder(struct TNode* node)
{
    if (node == NULL)
        return;
    printf("%d ", node->data);
    preOrder(node->left);
    preOrder(node->right);
}

/* Driver program to test above functions */
int main()
{
    int arr[] = {
                    1111, 1230, 1392, 1467, 1542, 1650, 1802, 1923, 2231, 2349,
                    2498, 2591, 2698, 2793, 2894, 2931, 3121, 3212, 3321, 3421,
                    3592, 3678, 3789, 3795, 3857, 3912, 4023, 4183, 4268, 4333,
                    4459, 4508, 4517, 4592/*, 4642, 4683, 4725, 4779, 4845, 4892,
                    4956, 5099, 5122, 5163, 5205, 5272, 5315, 5414, 5498, 5582,
                    5629, 5712, 5765, 5789, 5801, 5914, 6495, 6549, 6653, 6702,
                    6821, 6932, 7042, 7199, 7239, 7361, 7490, 7532, 7547, 7615,
                    7710, 7825, 7932, 8046, 8165, 8231, 8295, 8346, 8413, 8519,
                    8674, 8720, 8816, 8945, 9015, 9135, 9164, 9201, 9267, 9301,
                    9425, 9532, 9597, 9618, 9714, 9769, 9812, 9915, 9926, 9999*/
                };


    int n = sizeof(arr)/sizeof(arr[0]);
    //printf(n);
    /* Convert List to BST */
    struct TNode *root = sortedArrayToBST(arr, 0, n-1);
    printf("\n PreOrder Traversal of constructed BST ");
    preOrder(root);

    return 0;
}
