#include<iostream>
using namespace std;
#include "TreeType.h"
struct TreeNode
{
  ItemType info;
  TreeNode* left;
  TreeNode* right;
};
void CopyTree(TreeNode*& copy,  const TreeNode* originalTree);
template<class ItemType>
TreeType<ItemType>::TreeType()
{
	root = NULL;
}

template<class ItemType>
TreeType<ItemType>::TreeType(const TreeType& originalTree)
{

    CopyTree(root, originalTree.root);
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
    TreeNode* pointer = ptrToSuccessor(tree);
    data = pointer->info;
    tree->info = data;
    Delete(tree, data); 
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
  if(tree != NULL){
    cout << tree->info<<"  "; //print node first
  
  }

  if(tree != NULL && tree->left != NULL){
    preOrderTraverse(tree->left);
  }
  if(tree != NULL && tree->right !=NULL){
    preOrderTraverse(tree->right);
  } 
}

void postOrderTraverse(TreeNode* tree) 
// Prints info member of items in tree in sorted order on screen.
{
   if(tree != NULL && tree->left != NULL){
    preOrderTraverse(tree->left);
  }
  if(tree != NULL && tree->right !=NULL){
    preOrderTraverse(tree->right);
  } 
    
   if(tree != NULL){
   
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
	TreeNode* currentPtr=root;
	TreeNode* parentPtr=NULL;

	if (currentPtr == NULL){
	  found = false;// item is not found.
	  cout << "tree is empty";
	}else if(value == currentPtr->info){
	  cout << value << " is the root value. No ancestors." << endl;
	}else{
	  	    
	  while(currentPtr != NULL && !found){
	    if(value < currentPtr->info){
	      cout << currentPtr->info << " ";
	      if(value > currentPtr->info && value < parentPtr->info){
		  cout << value << " is not in the list.\n";
		  break;
	      }
	      parentPtr = currentPtr;
	      currentPtr = currentPtr->left;	      
	    }else if(value >currentPtr->info){	      
	      cout << currentPtr->info << " ";
	      if(value > currentPtr->info && value < parentPtr->info){
		cout << value << " is not in the list.\n";
		break;
	      }
	      parentPtr = currentPtr;
	      currentPtr = currentPtr->right;
	    }
	    else{
	      found = true;
	    }     
	  }
	}
}


TreeNode* ptrToSuccessor(TreeNode* tree);

template <class ItemType>
int TreeType<ItemType>::GetSuccessor(int value) {
// Implement this function, You may call a helper function
// Then Remove the following stub statement
	cout << "GetSuccessor() has been called\n";
    bool found=false;
	TreeNode* tree = root;
	TreeNode* currentPtr;
	TreeNode* parentPtr;
    TreeNode* succNode;
    int succ = -1;
    findNode(tree, value, currentPtr, parentPtr, found);
    if(found==true){
        succNode = ptrToSuccessor(currentPtr);
        if(succNode != NULL){
            succ = succNode->info;
        }//else return no logical succesor
    }//else return item not in tree
    
	return succ;//you should change this return statement
}
// helper function for Mirror Image


	
void mirror(TreeNode*& copy, const TreeNode* originalTree)
// Post: copy is the root of a tree that is a mirror Image of originalTree.
{
    if(originalTree == NULL){
        copy = NULL;
    }
    else{
        copy = new TreeNode;
        copy->info = originalTree->info;
        mirror(copy->right, originalTree->left);
        mirror(copy->left, originalTree->right);
    }
  // implement this function
}


template <class ItemType>
void TreeType<ItemType>::mirrorImage(TreeType& t)
{
//    TreeNode * point = t.root;
    mirror(t.root,root);
    TreeNode * loc;
    loc = t.root;
    cout << loc->right->right->info <<" the info:: "<< endl;
    
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
      //if (&originalTree == this)
      //     return;             // Ignore assigning self to self
      //Destroy(root);      // Deallocate existing tree nodes
      CopyTree(originalTree.root, root);
  }

}




int findHeight(TreeNode* tree){ //helper method
  if(tree == NULL){
    return -1; //base case
  }
  return max(findHeight(tree-> left),findHeight(tree->right)) +1;
}

int widthFinder(int maxHeight){
  
  int width = pow(2.0, maxHeight-1);
  return width;

}


template <class ItemType>
void TreeType<ItemType>::LevelOrderPrint()const{
if(root !=NULL){
  QueType A;
  QueType B;
  TreeNode* tree = root;
  ItemType item = tree->info;
  int maxHeight= findHeight(tree);
  cout << "height of tree:" << maxHeight;
   int levelCounter=0;
  A.Enqueue(item);

  while(!A.IsEmpty() || !B.IsEmpty()){

    TreeNode* current;
    TreeNode* parent;
    bool found;  
    while(!A.IsEmpty()){ //first case      
      A.Dequeue(item);
      cout << item << " ";
      findNode(root, item, current, parent, found);
      if(found){
	tree=current; //location is set
	if(tree-> left != NULL){
	  item = tree->left->info;
	  B.Enqueue(item);	  
	}else{
	  if(levelCounter != maxHeight){ //if not at maxHeight
	    B.Enqueue(-1);
	  }
	}
	
	if(tree-> right != NULL){
	  item = tree->right->info;
	  B.Enqueue(item);	  
	}else{
	  if(levelCounter != maxHeight){
	    B.Enqueue(-1);
	  }
	}		
      }
    }//end of while loop   
    cout << endl; 
    levelCounter++; //new level now

    while(!B.IsEmpty()){      
      B.Dequeue(item);
      cout << item << " ";

      findNode(root, item, current, parent, found);
      if(found){
	tree=current;
	if(tree-> left != NULL){
	  item = tree->left->info;
	  A.Enqueue(item);	  
	}else{
	   if(levelCounter != maxHeight){
	    A.Enqueue(-1);
	  }
	}
	
	if(tree-> right != NULL){
	  item = tree->right->info;
	  A.Enqueue(item);	  
	}else{
	  if(levelCounter != maxHeight){
	    A.Enqueue(-1);
	  }	  
	}		
      }
    }//end of while loop
    levelCounter++;
    cout << endl;
   }	
  }
}

TreeNode* ptrToSuccessor(TreeNode* tree){//Implement this function, you May use a data structure
    TreeNode* location = NULL;
    if(tree==NULL){
        return NULL;
    }else{
        if(tree->right!=NULL){
            location = tree->right;
            while(location->left!=NULL){
                location = location->left;
            }
        }
        return location;
    }
}

