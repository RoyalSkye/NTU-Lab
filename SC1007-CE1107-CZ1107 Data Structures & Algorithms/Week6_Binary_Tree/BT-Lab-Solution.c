
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////


typedef struct _btnode{
int item;
struct _btnode *left;
struct _btnode *right;

} BTNode;

////////////////////////////////////////////////////////////////////

void mirrorTree(BTNode *node);
void printSmallerValues(BTNode *node, int m);
int smallestValue(BTNode *node);
int hasGreatGrandchild(BTNode *node);
void printTree_InOrder(BTNode *node);

////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]){

	int i;
	//char reply;

	BTNode *root, *root2;
	BTNode btn[15];

	// Create the tree in Q1
	// Using manual dynamic allocation of memory for BTNodes

	root = malloc(sizeof(BTNode));
	root->item = 4;

	root->left = malloc(sizeof(BTNode));
	root->left->item = 5;

	root->right = malloc(sizeof(BTNode));
	root->right->item = 2;

	root->left->left = NULL;

	root->left->right = malloc(sizeof(BTNode));
	root->left->right->item = 6;

	root->left->right->left = NULL;
	root->left->right->right = NULL;

	root->right->left = malloc(sizeof(BTNode));
	root->right->left->item = 3;

	root->right->right = malloc(sizeof(BTNode));
	root->right->right->item = 1;

	root->right->left->left = NULL;

	root->right->left->right = NULL;

	root->right->right->left = NULL;

	root->right->right->right = NULL;

	printTree_InOrder(root);
	printf("\n");
	mirrorTree(root);
	printTree_InOrder(root);
	printf("\n\n");

	//question 2
	printf("\n input m for question 2:");
	scanf("%d", &i);
	printf("the values smaller than %d are:", i);
	printSmallerValues(root, i);
	printf("\n\n");

	//question 3
	printf("The smallest value in the tree is %d:\n", smallestValue(root));

	//question 4
	// Create a tree for Q4: Tall enough so some nodes have great-grandchildren
	// Use array of BTNodes, create tree by linking nodes together
	for (i = 0; i <= 6; i++){
		btn[i].item = i;
		btn[i].left = &(btn[i * 2 + 1]);
		btn[i].right = &(btn[i * 2 + 2]);
	}

	for (i = 7; i <= 14; i++){
		btn[i].item = i;
		btn[i].left = NULL;
		btn[i].right = NULL;
	}
	root2 = &btn[0];

	printf("The tree for question 4 visited by in-order is \n");
	printTree_InOrder(root2);
	printf("\nthe values stored in all nodes of the tree that have at least one great-grandchild are: ");

	hasGreatGrandchild(root2);

	return 0;
	//printf("\nenter any key to exit:");
	//fflush(stdin);
	//scanf("%c", &reply);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void mirrorTree(BTNode *node){

	BTNode *temp;

	if (node == NULL) return;

	// Swap left and right BTNode pointers
	// Using pre-order traversal
/*
	temp = node->left;
	node->left = node->right;
	node->right = temp;
	mirrorTree(node->left);
	mirrorTree(node->right);
*/
	// Using post-order traversal
	/*
	 mirrorTree(node->left);
	 mirrorTree(node->right);
	 temp = node->left;
	 node->left = node->right;
	 node->right = temp;
	  */

	// What about using in-order traversal?

	mirrorTree(node->left);
	temp = node->left;
	node->left = node->right;
	node->right = temp;
	mirrorTree(node->left);  // node->left is the original (before swapping) right subtree

}

///////////////////////////////////////////////////////////////////////////////////////////////

int hasGreatGrandchild(BTNode *node){

	int l, r;

	// Calculate the height of each node in the tree
	// Print out (data stored in) node that has height > n

	if (node == NULL)
		return -1;

	l = hasGreatGrandchild(node->left);
	r = hasGreatGrandchild(node->right);

	if (r > l)  // the height of a tree is decided by the higher subtree
		l = r;
	// it would be better to understand by drawing a tree and conducting the calculation
	if (l > 1)  // this is because we return -1 when node == NULL, the node has at least one great-grandchild iff the (maximum) height of subtree l > 1 (e.g., 2, 3, ...)
		printf("%d ", node->item);

	return (l + 1);

}

//////////////////////////////////////////////////////////////////////////////////////////////////

void printSmallerValues(BTNode *node, int m){
	if (node==NULL) return;
	if (node->item<m)
		printf("%d,", node->item);
	printSmallerValues(node->left, m);
	printSmallerValues(node->right, m);

	return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int smallestValue(BTNode *node)
{
	int l,r;
	if (node==NULL)
		return 100000;  // return an arbitrary large value

	l=smallestValue(node->left);
	r=smallestValue(node->right);
	if (l<node->item && l<r)
		return l;
	else if (r<node->item && r<l)
		return r;
	else 
		return node->item;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void printTree_InOrder(BTNode *node){

	if (node==NULL) return;
	printTree_InOrder(node->left);
	printf("%d, ",node->item);
	printTree_InOrder(node->right);
	return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
