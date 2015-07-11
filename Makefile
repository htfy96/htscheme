CPPFLAGS = -I . -I $(CURDIR) -isystem $(CURDIR)/sys  -g -O2 -pipe -std=c++11 
CXX = ccache clang++

INTEST = -D INTEST
CPPFLAGS += $(INTEST)
OBJ = $(wildcard *.o test/*.o utility/*.o types/*.o parsers/*.o)
BIN = $(wildcard preprocessortest tokenizertest biginttest typestest asttest parserstest rationaltypetest)

TYPESCPP = $(wildcard types/*.cpp)
TYPESHPP = $(wildcard types/*.hpp)
TYPES = $(patsubst %.cpp,%.o,$(TYPESCPP)) $(TYPESHPP)

PARSERSCPP = $(wildcard parsers/*.cpp)
PARSERSHPP = $(wildcard parsers/*.hpp)
PARSERS = $(patsubst %.cpp,%.o,$(PARSERSCPP)) $(TYPESHPP)

BASICTYPES = $(filter-out types/all.o, $(TYPES))

DEP = dep.d

include $(DEP)

preprocessortest: test/preprocessortest.o preprocessor.o
	$(CXX) $(CPPFLAGS) $(INTEST) $^  -o $@ 

tokenizertest: test/tokenizertest.o tokenizer.o preprocessor.o $(TYPES) 
	$(CXX) $(CPPFLAGS) $(INTEST) $(filter %.o,$^)  -o $@

biginttest: test/biginttest.o utility/bigint.o 
	$(CXX) $(CPPFLAGS) $(INTEST) $^  -o $@

asttest: test/asttest.o preprocessor.o tokenizer.o ast.o $(TYPES) 
	$(CXX) $(CPPFLAGS) $(INTEST) $(filter %.o,$^) -o $@

parserstest: test/parserstest.o preprocessor.o tokenizer.o ast.o $(TYPES) $(PARSERS) 
	$(CXX) $(CPPFLAGS) $(INTEST) $(filter %.o,$^) -o $@

rationaltypetest: test/rationaltypetest.o utility/rationaltype.o utility/bigint.o
	$(CXX) $(CPPFLAGS) $(INTEST) $^ -o $@

.PHONY: clean 

dep: */*.cpp */*.hpp
	 - $(CXX) $(CPPFLAGS) -MM */*.cpp > dep.d

typestest: test/typestest.cpp $(TYPES) 
	$(CXX) $(CPPFLAGS) $(INTEST) $^ -o $@

clean:
	-rm $(OBJ); rm $(BIN);
