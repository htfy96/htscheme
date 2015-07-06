CPPFLAGS = -g -pipe -std=gnu++0x 
CXX = clang++

preprocessortest: test/preprocessortest.cpp preprocessor.o
	$(CXX) $(CPPFLAGS) $^ -I .. -I . -o $@ 

tokenizertest: test/tokenizertest.cpp tokenizer.o preprocessor.o
	$(CXX) $(CPPFLAGS) $^ -I .. -I . -o $@

.PHONY: clean

clean:
	rm -r *.o; rm -r preprocessortest tokenizertest
