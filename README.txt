Recursive Tree
Files:
	TreeType.h	Contains the specification for class TreeType
	TreeType.cpp	Contains the implementation for class TreeType
	QueType.h		Contains the specification for class QueType
	QueType.cpp	Contains the implementation for class QueType. A singly linear linked list implementation of the ADT Queue.
        TreeDr.cpp      Test driver for TreeType
	inFile.txt:     Sample input file, contains sample commands that you have to consider in your driver program.

The implementation defines three queues to store tree items according to traversal order.

 	preQue:  contains the tree items in preorder.
 	inQue:   contains the tree items in inorder.
	postQue: contains the tree items in postorder.
	
	
To compile and execute the program, we have a Makefile which you just use the commands:
$ make compile

to compile all the files and then 

$ make run

to run the executable.
