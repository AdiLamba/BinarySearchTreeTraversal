#include <stdio.h>
#include <stdlib.h>

/*Typedef structure of a node, referred to as node,
with a pointer to the struct for future reference*/
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node, *NodePtr;

/*Function to create a node by referencing/pointing to the struct.
Point new variable np to struct, allocate memory of that size (Node),
assign passed in value, leave left/right pointers null*/
NodePtr createNode(int data){
    NodePtr np = (NodePtr)malloc(sizeof(Node));
    np -> data = data;
    np -> left = NULL;
    np -> right = NULL;
    return np;
}

/*Initialize a node named tree, (referencing struct) with the passed in value.
If tree is null then create it as the first/only node. Otherwise, if the passed
in value is less than the tree's current value, go to the tree's left value. If
the passed in value is greater than the tree's current value go to the tree's right.
Which ever way you go, repeat the insertNode function again, compare values and
travel along the tree as required. Once you reach a height/side neither apply,
insert the node and return the tree with the new value.*/
NodePtr insertNode(NodePtr tree, int data) {
    if (tree == NULL) {
        return createNode(data);
    }
    if (data < tree -> data) {
        tree -> left = insertNode(tree -> left, data);
    }
    else if (data > tree -> data) {
        tree -> right = insertNode(tree -> right, data);
    }
    return tree;
}

/*Function to find Minimum value. While the node on the left is not null,
continue to the left value (smaller int), repeat. Once the value further
left is null, return the current node as it will be the minimum value*/
NodePtr findMin(NodePtr node) {
    while (node -> left != NULL) {
        node = node -> left;
    }
    return node;
    
}

/*Function to delete a node. If there is no tree (null), return the tree as is.
*/
NodePtr deleteNode(NodePtr tree, int data) {
    if (tree == NULL){
        return tree;
    }

    /*Compare data that was passed in to the data in the tree. Keep traversing
    left or right as required until the data finds its match/indended delete.*/
    if (data < tree -> data) {
        tree -> left = deleteNode(tree -> left, data);
    }
    else if (data > tree -> data) {
        tree -> right = deleteNode(tree -> right, data);
    }

    /*Once data finds its match run these 2 if statements to verify whether it
    is a parent with one child, if it is (depending on which child is null),
    the funtion will assign the non null value in temp, delete the target node,
    return the temp value, which due to the recursive nature of the function,
    will assign the temp value in the place of the deleted node. */
    else {
        if (tree -> left == NULL) {
            NodePtr temp = tree -> right;
            free (tree);
            return temp;
        }
        else if (tree -> right == NULL) {
            NodePtr temp = tree -> left;
            free (tree);
            return temp;
        }
        /*If the matched node for deletion was NOT a one child node, it would mean
        that it is a 2 child node. In this case there would be 2 ways to handle it.
        This code handles it by finding the minimum value on the right subtree.
        Any value in the right sub tree is larger than the target node, but it finds
        the smallest of those, and replaces the target node value with that of the
        min value in the right subtree, thereby preserving the integrity of the tree,
        without having to balance it. All the subsequent values remaining in the right
        subtree would still be larger than the replaced value since it was the smallest
        among them (in the right subtree). Another way would have been to find the largest
        value in the left subtree using the same logic of preserving the integrity of the tree,
        but apparently using the min value is more generally accepted.
        (and I already had a findMin function). */
        NodePtr temp = findMin(tree -> right);
        tree -> data = temp -> data;
        tree -> right = deleteNode(tree -> right, temp -> data);
    }

    return tree;
}

/*Function returns ordered list of nodes in the tree, by going to the furthest
left subtree value, printing it, and then repeating for each right subtree*/
void inOrderTraversal (NodePtr tree) {
    if (tree == NULL) {
        return;
    }
    inOrderTraversal(tree -> left);
    printf("%d \n", tree -> data);
    inOrderTraversal(tree -> right);
}

/*Function to print the root node first, then the left subtree then the right.*/
void preOrderTraversal(NodePtr tree) {
    if (tree == NULL) {
        return;
    }
    printf("%d \n", tree -> data);
    preOrderTraversal(tree -> left);
    preOrderTraversal(tree -> right);
}

/*Function that prints the values in the left subtree, then the right subtree,
working its way back to the root node.*/
void postOrderTraversal(NodePtr tree) {
    if (tree == NULL) {
        return;
    }
    postOrderTraversal(tree -> left);
    postOrderTraversal(tree -> right);
    printf("%d \n", tree -> data);
}

/*Function to calulate height of the tree. If the tree is empty, return -1, value
of an empty tree. Otherwise count the numbe of nodes first in the left subtree, counting
all the left most values until the end is reached. Do the same for the right subtree
use the value for whichever branch (left or right) was the largest. Assign that number
(level) of the tree to height and add 1 to incorporate the current level it is stopped at
(since height will not add this level if the next left or right is a null value).*/
int calculateHeight(NodePtr tree) {
    if (tree == NULL) {
        return -1;
    }
    int leftHeight = calculateHeight (tree -> left);
    int rightHeight = calculateHeight (tree -> right);
    int height = 0;
    if (leftHeight > rightHeight) {
        height = leftHeight;
    }
    else {
        height = rightHeight;
    }
    return 1 + height;
}

/*Function to count nodes from a given point. Any value passed to this function
will yeild a count of that node plus all of its child elements. It will continue
counting recursively until a null values is encountered.*/
int nodeCount (NodePtr tree) {
    if (tree == NULL) {
        return 0;
    }
    return 1 + nodeCount(tree -> left) + nodeCount(tree -> right);
}

/*Function to find a value within a tree. Returns null if no tree or value is found.
Otherwise it will continue recursively checking the tree left and right and return true (1)
once the passed in value has been found.*/
int search(NodePtr tree, int value) {
    if (tree == NULL) {
        return 0;
    }
    if (tree -> data == value) {
        return 1;
    }
    if (value < tree -> data) {
        return search(tree -> left, value);
    }
    else {
        return search(tree -> right, value);
    }
}

/*Function to find minimum. Passed in tree you are looking through recursively.
while the value is in the current nodes subtree is not null
(meaning there is one which is smaller), keep moving to the left subtree node,
once the next value in the left subtree is null, you know you have reached the lowest
node.*/
int minimum(NodePtr tree) {
    if (tree == NULL) {
        return -1;
    }
    NodePtr current = tree;
    while (current -> left != NULL) {
        current = current -> left;
    }
    return current -> data;
}

/*Function similar to minimum, checks the tree that was passed in recursively.
keeps moving to the value in the nodes right subtree until that value is null,
meaning you have found the largest value in the tree.*/
int maximum(NodePtr tree) {
    if (tree == NULL) {
        return -1;
    }
    NodePtr current = tree;
    while (current -> right != NULL) {
        current = current -> right;
    }
    return current -> data;
}

int main() {

    NodePtr tree = NULL;

    tree = insertNode(tree, 25);
    tree = insertNode(tree, 12);
    tree = insertNode(tree, 66);
    tree = insertNode(tree, 84);
    tree = insertNode(tree, 75);
    tree = insertNode(tree, 92);
    tree = insertNode(tree, 103);
    tree = insertNode(tree, 27);
    tree = insertNode(tree, 19);
    tree = insertNode(tree, 4);
    tree = insertNode(tree, 202);

    printf("In Order Traversal: \n");
    inOrderTraversal(tree);

    printf("Pre Order Traversal: \n");
    preOrderTraversal(tree);

    printf("Post Order Traversal: \n");
    postOrderTraversal(tree);

    printf("Height of tree: %d\n", calculateHeight(tree));
    printf("Total number of nodes: %d\n", nodeCount(tree));

    
    inOrderTraversal(tree);
    tree = deleteNode (tree, minimum(tree));
    printf("In order traversal after deleting minimum node: \n");
    inOrderTraversal(tree);

    
    deleteNode(tree, maximum(tree));
    printf("Tree after deleting maximum node: \n");
    inOrderTraversal(tree);

    
    tree = deleteNode(tree, 27);
    printf("In order traversal after deleting middle node (root): \n");
    inOrderTraversal(tree);

    /*Searching for value not in the tree*/
    int searchValue = 144;
    if (search(tree, searchValue)) {
        printf("Value %d was found in the tree\n", searchValue);
    }
    else {
        printf("Value %d was not found in the tree\n", searchValue);
    }

    return 0;
}

