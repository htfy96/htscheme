CPPFLAGS = -I . -I $(CURDIR) -isystem $(CURDIR)/sys -g -O2 -pipe -std=gnu++0x 
CXX = ccache clang++

INTEST = -D INTEST
OBJ = $(wildcard *.o test/*.o utility/*.o types/*.o)
BIN = $(wildcard preprocessortest tokenizertest biginttest typestest)
TYPESCPP = $(wildcard types/*.cpp)
TYPES = $(patsubst %.cpp,%.o,$(TYPESCPP))
BASICTYPES = $(filter-out types/all.o, $(TYPES))

preprocessortest: test/preprocessortest.cpp preprocessor.o
	$(CXX) $(CPPFLAGS) $(INTEST) $^  -o $@ 

tokenizertest: test/tokenizertest.cpp tokenizer.o preprocessor.o $(TYPES)
	$(CXX) $(CPPFLAGS) $(INTEST) $^  -o $@

biginttest: test/biginttest.cpp utility/bigint.o 
	$(CXX) $(CPPFLAGS) $(INTEST) $^  -o $@

.PHONY: clean


typestest: test/typestest.cpp $(TYPES) 
	$(CXX) $(CPPFLAGS) $(INTEST) $^ -o $@

clean:
	rm $(OBJ); rm $(BIN);
