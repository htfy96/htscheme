CPPFLAGS = -I . -I .. -g -O2 -pipe -std=gnu++0x 
CXX = g++

preprocessortest: test/preprocessortest.cpp preprocessor.o
	$(CXX) $(CPPFLAGS) $^  -o $@ 

tokenizertest: test/tokenizertest.cpp tokenizer.o preprocessor.o
	$(CXX) $(CPPFLAGS) $^  -o $@

biginttest: test/biginttest.cpp utility/bigint.o 
	$(CXX) $(CPPFLAGS) $^  -o $@

.PHONY: clean

OBJ = $(wildcard *.o test/*.o utility/*.o types/*.o)

clean:
	rm $(OBJ); rm -r preprocessortest tokenizertest biginttest
