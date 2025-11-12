all: count test

count: count.cpp ll.hpp
	g++ -o count -ggdb3 -Wall -Werror -pedantic -std=gnu++98 count.cpp
test: test-lls.cpp ll.hpp
	g++ -o test test-lls.cpp
