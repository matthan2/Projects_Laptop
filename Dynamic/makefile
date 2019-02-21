CXX = g++
CXXFLAGS = -Wall

dynamic3: Student.o
	$(CXX) $(CXXFLAGS) Student.o dynamic3.cpp -o dynamic3

Student.o: Student.cpp Student.h
	$(CXX) $(CXXFLAGS) -c Student.cpp

clean:
	rm *.o
	rm *~ 

run:
	./dynamic3
