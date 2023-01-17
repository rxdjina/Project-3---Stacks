all: test_stack in2post

test_stack: stack.hpp test_stack1.cpp 
	g++ -std=c++11 test_stack1.cpp -o test_stack.x 

in2post: stack.hpp in2post.cpp
	g++ -std=c++11 in2post.cpp -o in2post.x

clean:
	rm -f test_stack.x in2post.x
