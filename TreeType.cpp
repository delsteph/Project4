#include<iostream>
using namespace std;
#include "TreeType.h"
struct TreeNode
{
  ItemType info;
  TreeNode* left;
  TreeNode* right;
};

template<class ItemType>
TreeType<ItemType>::TreeType()
{
	root = NULL;
}

template<class ItemType>
TreeType<ItemType>::TreeType(const TreeType& originalTree)
{

  this.root = originalTree.root;
}

void Destroy(TreeNode*& tree);

template<class ItemType>
TreeType<ItemType>::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
	Destroy(root);
}

template<class ItemType>
bool TreeType<ItemType>::IsFull() const
// Returns true if there is no room for another item 
//  on the free store; false otherwise.
{
  TreeNode* location;
  try
  {
    location = new TreeNode;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception)
  {
    return true;
  }
}

template<class ItemType>
bool TreeType<ItemType>::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}


int CountNodes(TreeNode* tree);

template<class ItemType>
int TreeType<ItemType>::GetLength() const
// Calls recursive function CountNodes to count the 
// nodes in the tree.
{
  return CountNodes(root);
}


int CountNodes(TreeNode* tree)
// Post: returns the number of nodes in the tree.
{
  if (tree == NULL)
    return 0;
  else 
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

void Retrieve(TreeNode* tree, 
     ItemType& item, bool& found);

template<class ItemType>
ItemType TreeType<ItemType>::GetItem(ItemType item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
  return item;
}

// helper function for GetItem
void Retrieve(TreeNode* tree, 
     ItemType& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem; 
//       otherwise found is false and item is unchanged.
{
  if (tree == NULL)
    found = false;                     // item is not found.
  else if (item < tree->info)      
    Retrieve(tree->left, item, found); // Search left subtree.
  else if (item > tree->info)
    Retrieve(tree->right, item, found);// Search right subtree.
  else
  {
    item = tree->info;                 // item is found.
    found = true;
   }
} 


void Insert(TreeNode*& tree, ItemType item);

template<class ItemType>
void TreeType<ItemType>::PutItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}

// helper Function for PutItem
void Insert(TreeNode*& tree, ItemType item) // Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL){// Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    Insert(tree->left, item);    // Insert in left subtree.
  else
    Insert(tree->right, item);   // Insert in right subtree.
}


void DeleteNode(TreeNode*& tree);

void Delete(TreeNode*& tree, ItemType item);

template<class ItemType>
void TreeType<ItemType>::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
	bool found = false;
	GetItem(item, found);
	if (found)
		Delete(root, item);
	else
		cout << item << "is not in tree\n";
}


void Delete(TreeNode*& tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
  if (item < tree->info)
    Delete(tree->left, item);   // Look in left subtree.
  else if (item > tree->info)
    Delete(tree->right, item);  // Look in right subtree.
  else
    DeleteNode(tree);           // Node found; call DeleteNode.
}   

void GetPredecessor(TreeNode* tree, ItemType& data);

void DeleteNode(TreeNode*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no 
//       longer in the tree.  If tree is a leaf node or has only 
//       non-NULL child pointer the node pointed to by tree is 
//       deleted; otherwise, the user's data is replaced by its 
//       logical predecessor and the predecessor's node is deleted.
{
  ItemType data;
  TreeNode* tempPtr;

  tempPtr = tree;
  if (tree->left == NULL)
  {
    tree = tree->right;
    delete tempPtr;
  }
  else if (tree->right == NULL)
  {
    tree = tree->left;
    delete tempPtr;
  }
  else
  {
    GetPredecessor(tree->left, data);
    tree->info = data;
    Delete(tree->left, data);  // Delete predecessor node.
  }
}
//Helper function for DeleteNode
void GetPredecessor(TreeNode* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}
// Helper function for Print


void inOrderTraverse(TreeNode* tree) 
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
  {
	inOrderTraverse(tree->left);   // Print left subtree.
    cout << tree->info<<"  ";
	inOrderTraverse(tree->right);  // Print right subtree.
  }
}

void preOrderTraverse(TreeNode* tree) 
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL){
    cout << tree->info<<"  "; //print node first
      preOrderTraverse(tree->right);  // Print right subtree.
    preOrderTraverse(tree->left);   // Print left subtree.

  }
}

void postOrderTraverse(TreeNode* tree) 
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL){
     postOrderTraverse(tree->right);  // Print right subtree.
       postOrderTraverse(tree->left);   // Print left subtree.
  
	 cout << tree->info<<"  "; //print node first
  }
}



template <class ItemType>
void TreeType<ItemType>::Print() const
// Calls recursive function inOrderTraverse to print items in the tree.
{
  inOrderTraverse(root);
}


template <class ItemType>
void TreeType<ItemType>::PreOrderPrint()const
{// Implement this function, You may call a helper function
 // Then Remove the following stub statement
  preOrderTraverse(root);

	
}


template <class ItemType>
void TreeType<ItemType>::PostOrderPrint() const
{
 // Implement this function, You may call a helper function
// Then Remove the following stub statement
  postOrderTraverse(root);

}


void findNode(TreeNode* tree, ItemType item, TreeNode*& nodePtr,
	      TreeNode*& parentPtr, bool& found){

  nodePtr = tree;
  parentPtr = NULL;
  found = false;
  while(nodePtr != NULL && !found){
    if(item < nodePtr->info){
      parentPtr = nodePtr;
      nodePtr = nodePtr->left;
    }else if(item >nodePtr->info){
      parentPtr = nodePtr;
      nodePtr = nodePtr->right;
    }else{
      found = true;
    }    
  }
}

template <class ItemType>
void TreeType<ItemType>::PrintAncestors(int value) {
// Implement this function, You may call a helper function
// Then Remove the following stub statement

	bool found=false;
	TreeNode* tree = root;
	TreeNode* currentPtr;
	TreeNode* parentPtr;

	if (tree == NULL){
	  found = false;// item is not found.
	  cout << "tree is empty";
	}else{
	  
	  findNode(tree, value, currentPtr, parentPtr, found);
	  currentPtr=NULL;
	  parentPtr=NULL;
	  
	  if(found){
	    
	    while(parentPtr != NULL && currentPtr != NULL){
	      
	      findNode(tree, value, currentPtr, parentPtr, found);
	      cout << parentPtr->info << " ";
	      currentPtr = parentPtr;
	    parentPtr = NULL;//parent is now current and then to find its parent
	    value = currentPtr->info; //updated value
	    
	    }
	  }
	}
	
}


template <class ItemType>
int TreeType<ItemType>::GetSuccessor(int value) {
// Implement this function, You may call a helper function
// Then Remove the following stub statement
	cout << "GetSuccessor() has been called\n";
	
	return 0;//you should change this return statement
}
// helper function for Mirror Image


	
void mirror(TreeNode*& copy, const TreeNode* originalTree)
// Post: copy is the root of a tree that is a mirror Image of originalTree.
{


  // implement this function
}


template <class ItemType>
void TreeType<ItemType>::mirrorImage(TreeType& t)
{
	// calls the helper function mirror
}
   


void Destroy(TreeNode*& tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
}



template <class ItemType>
void TreeType<ItemType>::MakeEmpty()
{
  Destroy(root);
  root = NULL;
}



void CopyTree(TreeNode*& copy,	const TreeNode* originalTree)
	// Post: copy is the root of a tree that is a duplicate
	// of originalTree.
{
	if (originalTree == NULL)
		copy = NULL;
	else
	{
		copy = new TreeNode;
		copy->info = originalTree->info;
		CopyTree(copy->left, originalTree->left);
		CopyTree(copy->right, originalTree->right);
	}
}


template <class ItemType>
void TreeType<ItemType>::operator=(const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree 
// into root.
{
  {
  if (&originalTree == this)
    return;             // Ignore assigning self to self
  Destroy(root);      // Deallocate existing tree nodes
  CopyTree(root, originalTree.root);
  }

}



template <class ItemType>
void TreeType<ItemType>::LevelOrderPrint()const
{//Implement this function, you May use a data structure

  QueType A;
  QueType B;

  TreeNode* tree = root;
  ItemType item = tree->info;
  
  A.Enqueue(item);

  while(!A.isEmpty() || !B.isEmpty()){
    while(!A.isEmpty()){ //first case

      
      tree->info = A.Dequeue();
      cout << tree->info << endl;
      if(tree-> left != NULL){


      }
      

      




    }







  }
  

  
  
  


  
}
	
TreeNode* ptrToSuccessor(TreeNode* tree){//Implement this function, you May use a data structure
	
}
