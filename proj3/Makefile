CXX = g++
CXXFLAGS = -Wall

test1: test1.o MinMaxHeap.o
	$(CXX) $(CXXFLAGS) MinMaxHeap.o test1.cpp -o test1

MinMaxHeap.o: MinMaxHeap.cpp MinMaxHeap.h
	$(CXX) $(CXXFLAGS) -c MinMaxHeap.cpp	

clean:
	rm *.o
	rm *~

run:
	./test1

