Test: Test.cc
	g++ -g -o Test Test.cc String.cc -std=c++11
clean:
	rm -f Test	