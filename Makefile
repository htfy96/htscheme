CPPFLAGS = -I . -I $(CURDIR) -isystem $(CURDIR)/sys  -g -O2 -pipe -std=c++11 
CXX = ccache clang++

INTEST = -D INTEST
OBJ = $(wildcard *.o test/*.o utility/*.o types/*.o parsers/*.o)
BIN = $(wildcard preprocessortest tokenizertest biginttest typestest asttest parserstest)
TYPESCPP = $(wildcard types/*.cpp)
TYPES = $(patsubst %.cpp,%.o,$(TYPESCPP))
PARSERSCPP = $(wildcard parsers/*.cpp)
PARSERS = $(patsubst %.cpp,%.o,$(PARSERSCPP))
BASICTYPES = $(filter-out types/all.o, $(TYPES))

preprocessortest: test/preprocessortest.cpp preprocessor.o
	$(CXX) $(CPPFLAGS) $(INTEST) $^  -o $@ 

tokenizertest: test/tokenizertest.cpp tokenizer.o preprocessor.o $(TYPES)
	$(CXX) $(CPPFLAGS) $(INTEST) $^  -o $@

biginttest: test/biginttest.cpp utility/bigint.o 
	$(CXX) $(CPPFLAGS) $(INTEST) $^  -o $@

asttest: test/asttest.cpp preprocessor.o tokenizer.o ast.o $(TYPES)
	$(CXX) $(CPPFLAGS) $(INTEST) $^ -o $@

parserstest: test/parserstest.cpp preprocessor.o tokenizer.o ast.o $(TYPES) $(PARSERS)
	$(CXX) $(CPPFLAGS) $(INTEST) $^ -o $@

.PHONY: clean


typestest: test/typestest.cpp $(TYPES) 
	$(CXX) $(CPPFLAGS) $(INTEST) $^ -o $@

clean:
	rm $(OBJ); rm $(BIN);
