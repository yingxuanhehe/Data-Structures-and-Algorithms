//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////

typedef struct _btnode{
int item;
struct _btnode *left;
struct _btnode *right;
} BTNode;

///////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value);
void printBSTInOrder(BTNode *node);
int isBST(BTNode *node, int min, int max);
BTNode *removeBSTNode(BTNode *node, int value);
BTNode *findMin(BTNode *p);
BTNode *findMin2(BTNode *p);

///////////////////////////////////////////////////////////////////////

int main(){
	int i=0;

	BTNode *root=NULL;

	//question 1
	do{
		printf("input a value you want to insert(-1 to quit):");

		scanf("%d",&i);
		if (i!=-1)
			insertBSTNode(&root,i);
	}while(i!=-1);

	//question 2
	printf("\n");
	printBSTInOrder(root);

	//question 3
	if ( isBST(root,-1000000, 1000000)==1)
		printf("It is a BST!\n");
	else
		printf("It is not a BST!\n");

	//question 4
	do{
		printf("\ninput a value you want to remove(-1 to quit):");
		scanf("%d",&i);
		if (i!=-1)
		{
			root=removeBSTNode(root,i);
			printBSTInOrder(root);
		}
	}while(i!=-1);


	return 0;
}

//////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value)
{
	if (*node==NULL) //if the tree is empty
	{
		*node=malloc(sizeof(BTNode));
		(*node)->item =value;
		(*node)->left =NULL;
		(*node)->right = NULL;
		return;
	}

	if ((*node)->item > value) //value is smaller than the node
		insertBSTNode(&((*node)->left), value);

	else if ((*node)->item <value) //value is larger than the node
		insertBSTNode(&((*node)->right), value);

	else // (*node)->item == value, value will not be inserted
	{
		printf("Already exists in the BST\n");
		return;
	}
	return;
}

//////////////////////////////////////////////////////////////////////

void printBSTInOrder(BTNode *node)
{
	if(node==NULL)
        return;

    printBSTInOrder(node->left);
    printf("%d", node->item);
    printBSTInOrder(node->right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int isBST(BTNode *node, int min, int max) // the item stored in node has to be smaller than max and larger than min
{
	if (node==NULL)
		return 1;

    //the node's value should belong to (min, max)
	if (node->item >= max || node->item <= min)
		return 0;

	// its left node should be smaller than node->item
	// its right node should be larger than node->item
	return isBST(node->left,min, node->item)&& isBST(node->right,node->item, max) ;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *removeBSTNode(BTNode *node, int value)
{
	BTNode *p;

	if (node==NULL)
	{
		printf("can't find the value!\n");
		return NULL;
	}

    // If the node to be removed is < than root's
    // then it is in left subtree
    if(value < node->item)
        node->left = removeBSTNode(node->left, value);

    // If the node to be removed is > than root's
    // then it is in right subtree
    else if(value > node->item)
        node->right = removeBSTNode(node->right, value);

    // If root's item == value
    else
    {
        //has two children
        if(node->left!=NULL && node->right!=NULL)
        {
            p = findMin(node->right);  //find the smallest value in the right subtree
            node->item = p->item;
            node->right = removeBSTNode(node->right, p->item);  // Delete the inorder successor
        }

        //has no children or one child
        else
        {
            p = node;

            if(node->left)
                node=node->left;

            else
                node=node->right;

            free(p);
        }
    }
    return node;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *findMin(BTNode *p)
{
	BTNode *cur = p;

	while(cur->left != NULL)
        cur = cur->left;

    return cur;
}

BTNode *findMin2(BTNode *p)
{
	return p->left!=NULL? findMin(p->left):p;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
