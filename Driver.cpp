#include <string>
#include <cctype>
#include <cstring>
#include "TreeType.cpp"
#include<iostream>
using namespace std;



void arrayToTree(int arr[], int start, int end, TreeType<int>& bt){
    if(start>end){
        
    }
    else{
        int mid = (start+end)/2;
        cout << mid << endl;
        int i = arr[mid];
        bt.PutItem(i);
        arrayToTree(arr, start, mid-1, bt);
        arrayToTree(arr, mid+1, end, bt);
    }
}
TreeType<int> makeTree(int arr[], int size)
{
    TreeType<int> balancedTree;
    arrayToTree(arr, 0, size, balancedTree);
    balancedTree.LevelOrderPrint();
	// Code to add array items in balancedTree
	//Write your code
	cout << "MakeTree has been called";
	//remove this statement from implementation
	return balancedTree;
}



int main(){
TreeType<int> tree;
TreeType<int> treeHeight;
int arrt[7];
arrt[0] = 1;
arrt[1] = 2;
arrt[2] = 3;
arrt[3] = 4;
arrt[4] = 5;
arrt[5] = 6;
arrt[6] = 7;

int s = 4;
TreeType<int> tree1 = makeTree(arrt, 6);
tree1.LevelOrderPrint();
//TreeType<int> bal = makeTree(arrt, 3);
//bal.LevelOrderPrint();
/*
treeHeight.PutItem(10);
treeHeight.LevelOrderPrint();
tree.PutItem(20);
tree.PutItem(10);
tree.PutItem(15);
tree.PutItem(3);
tree.PutItem(2);
tree.PutItem(4);
//tree.PutItem(15);
tree.PutItem(14);
tree.PutItem(17);
tree.PutItem(30);
tree.PutItem(25);
tree.PutItem(35);
tree.PutItem(24);
tree.PutItem(26);
tree.PutItem(34);
tree.PutItem(36);
*/
/*
tree.PutItem(20);
tree.PutItem(10);
tree.PutItem(5);
tree.PutItem(15);
tree.PutItem(30);
tree.PutItem(25);
tree.PutItem(35);
tree.LevelOrderPrint();
tree.mirrorImage(treeMirror);
int i = treeMirror.GetSuccessor(30);
cout << endl;
treeMirror.Print();
cout << endl;
cout << "suc" << i << endl;
treeMirror.LevelOrderPrint();
//int i = tree.GetSuccessor(7);
//cout << i << endl;

*/
}
