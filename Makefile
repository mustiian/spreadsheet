CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb
OBJECTS=String.o Number.o Function.o Pointer.o Command.o Cell.o Spreadsheet.o main.o

all: compile doc

compile: table clean_o

clean_o:
	\rm ./*.o

run:
	./mustiian

doc:
	doxygen ./src/Doxyfile

table: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -lncurses -o mustiian

String.o: src/ExpressionTypes/String.cpp src/ExpressionTypes/String.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Number.o: src/ExpressionTypes/Number.cpp src/ExpressionTypes/Number.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Function.o: src/ExpressionTypes/Function.cpp src/ExpressionTypes/Function.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Pointer.o: src/ExpressionTypes/Pointer.cpp src/ExpressionTypes/Pointer.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Command.o: src/Command.cpp src/Command.h src/ExpressionTypes/Expression.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Cell.o: src/Cell.cpp src/Cell.h src/Command.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Spreadsheet.o: src/Spreadsheet.cpp src/Spreadsheet.h src/Cell.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o: src/main.cpp src/Spreadsheet.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f ./table *.o *.gch ./a.out ./mustiian rm -rf ./doc

.PHONY: clean
