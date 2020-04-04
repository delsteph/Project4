compile:
	$ g++ -g -Wall -pedantic-errors -c QueType.cpp
	$ g++ -g -Wall -pedantic-errors -c TreeType.cpp
	$ g++ -g -Wall -pedantic-errors -c TreeDr.cpp
	$ g++ -g -Wall -pedantic-errors -o myProgram TreeDr.o
run:
	$ ./myProgram

clean:
	$ -rm *.o
