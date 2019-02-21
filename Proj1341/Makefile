CXX = g++
CXXFLAGS = -Wall

driver: driver.o joke.o
	$(CXX) $(CXXFLAGS) joke.o driver.cpp -o driver

joke.o: joke.cpp joke.h
	$(CXX) $(CXXFLAGS) -c joke.cpp

clean:
	rm *.o
	rm *~

run:
	./driver

