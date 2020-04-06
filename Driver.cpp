#include <string>
#include <cctype>
#include <cstring>
#include "TreeType.cpp"
#include<iostream>
using namespace std;


int main(){
TreeType<int> tree;
TreeType<int> treeHeight;
TreeType<int> treeMirror;
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


}
