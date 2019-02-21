CXX = g++
CXXFLAGS = -Wall

driver1: driver1.o Sally.o
	$(CXX) $(CXXFLAGS) Sally.o driver.cpp -o driver

Sally.o: Sally.cpp Sally.h
	$(CXX) $(CXXFLAGS) -c Sally.cpp

clean:
	rm *.o
	rm *~

run:
	./driver1

