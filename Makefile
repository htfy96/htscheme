CPPFLAGS = -I . -I ..  -isystem ./sys -isystem ../sys -std=c++11 -static -Wno-non-template-friend
CXX = g++

INTEST = -D INTEST
OBJ = $(wildcard *.o test/*.o utility/*.o types/*.o parsers/*.o funs/*.o)
BIN = $(wildcard cli preprocessortest tokenizertest biginttest typestest asttest parserstest rationaltypetest complextypetest)

TYPESCPP = $(wildcard types/*.cpp)
TYPESHPP = $(wildcard types/*.hpp)
TYPES = $(patsubst %.cpp,%.o,$(TYPESCPP)) $(TYPESHPP)

PARSERSCPP = $(wildcard parsers/*.cpp)
PARSERSHPP = $(wildcard parsers/*.hpp)
PARSERS = $(patsubst %.cpp,%.o,$(PARSERSCPP)) $(TYPESHPP)

UTILITYCPP = $(wildcard utility/*.cpp)
UTILITYHPP = $(wildcard utility/*.hpp)
UTILITY = $(patsubst %.cpp,%.o,$(UTILITYCPP)) $(UTILITYHPP)

FUNSCPP = $(wildcard funs/*.cpp)
FUNSHPP = $(wildcard funs/*.hpp)
FUNS = $(patsubst %.cpp,%.o,$(FUNSCPP)) $(FUNSHPP)

BASICTYPES = $(filter-out types/all.o, $(TYPES))

DEP = dep.d

all:
	$(MAKE) cli 

include $(DEP)

cli: cli.o preprocessor.o tokenizer.o ast.o $(TYPES) $(PARSERS) $(UTILITY) $(FUNS)
	$(CXX) $(CPPFLAGS) $(filter %.o,$^) -o $@

preprocessortest: test/preprocessortest.o preprocessor.o
	$(CXX) $(CPPFLAGS) $(INTEST) $(filter %.o,$^)  -o $@ 

tokenizertest: test/tokenizertest.o tokenizer.o preprocessor.o $(TYPES) $(UTILITY)
	$(CXX) $(CPPFLAGS) $(INTEST) $(filter %.o,$^)  -o $@

biginttest: test/biginttest.o utility/bigint.o 
	$(CXX) $(CPPFLAGS) $(INTEST) $(filter %.o,$^)  -o $@

asttest: test/asttest.o preprocessor.o tokenizer.o ast.o $(TYPES) $(UTILITY)
	$(CXX) $(CPPFLAGS) $(INTEST) $(filter %.o,$^) -o $@

parserstest: test/parserstest.o preprocessor.o tokenizer.o ast.o $(TYPES) $(PARSERS) $(UTILITY) $(FUNS)
	$(CXX) $(CPPFLAGS) $(INTEST) $(filter %.o,$^) -o $@

rationaltypetest: test/rationaltypetest.o utility/rationaltype.o utility/bigint.o
	$(CXX) $(CPPFLAGS) $(INTEST) $(filter %.o,$^) -o $@

complextypetest: test/complextypetest.o $(UTILITY) types/float.o types/rational.o
	$(CXX) $(CPPFLAGS) $(INTEST) $(filter %.o,$^) -o $@

.PHONY: clean all

dep: */*.cpp */*.hpp
	 - $(CXX) $(CPPFLAGS) -MM */*.cpp > dep.d



#typestest: test/typestest.o $(TYPES) $(UTILITY)
#	$(CXX) $(CPPFLAGS) $(INTEST) $(filter %.o,$^) -o $@


clean:
	-rm $(OBJ) $(BIN)
