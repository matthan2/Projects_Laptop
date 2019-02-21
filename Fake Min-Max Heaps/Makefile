CXX = g++
CXXFLAGS = -Wall

test5: test5.o MinMaxHeap.o NoCopyString.o
	$(CXX) $(CXXFLAGS) MinMaxHeap.o NoCopyString.o test5.cpp -o test5

MinMaxHeap.o: MinMaxHeap.cpp MinMaxHeap.h
	$(CXX) $(CXXFLAGS) -c MinMaxHeap.cpp	

NoCopyString.o: NoCopyString.cpp NoCopyString.h
	$(CXX) $(CXXFLAGS) -c NoCopyString.cpp

clean:
	rm *.o
	rm *~

run:
	./test5

