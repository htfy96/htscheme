opminus.o: parsers/opminus.cpp parsers/opminus.hpp ast.hpp types.hpp \
  types/all.hpp types/arch.hpp types/rational.hpp \
  utility/rationaltype.hpp utility/bigint.hpp types/float.hpp \
  types/string.hpp types/boolean.hpp types/parenthesis.hpp types/ops.hpp \
  parsers/arch.hpp parsers/all.hpp parsers/opplus.hpp
opplus.o: parsers/opplus.cpp parsers/opplus.hpp ast.hpp types.hpp \
  types/all.hpp types/arch.hpp types/rational.hpp \
  utility/rationaltype.hpp utility/bigint.hpp types/float.hpp \
  types/string.hpp types/boolean.hpp types/parenthesis.hpp types/ops.hpp \
  parsers/arch.hpp parsers/all.hpp parsers/opminus.hpp
asttest.o: test/asttest.cpp ast.hpp types.hpp types/all.hpp \
  types/arch.hpp types/rational.hpp utility/rationaltype.hpp \
  utility/bigint.hpp types/float.hpp types/string.hpp types/boolean.hpp \
  types/parenthesis.hpp types/ops.hpp preprocessor.hpp tokenizer.hpp
biginttest.o: test/biginttest.cpp utility/bigint.hpp
parserstest.o: test/parserstest.cpp preprocessor.hpp tokenizer.hpp \
  types.hpp types/all.hpp types/arch.hpp types/rational.hpp \
  utility/rationaltype.hpp utility/bigint.hpp types/float.hpp \
  types/string.hpp types/boolean.hpp types/parenthesis.hpp types/ops.hpp \
  ast.hpp parsers.hpp parsers/all.hpp parsers/opplus.hpp \
  parsers/arch.hpp parsers/opminus.hpp
preprocessortest.o: test/preprocessortest.cpp preprocessor.hpp
rationaltypetest.o: test/rationaltypetest.cpp utility/rationaltype.hpp \
  utility/bigint.hpp
tokenizertest.o: test/tokenizertest.cpp preprocessor.hpp tokenizer.hpp \
  types.hpp types/all.hpp types/arch.hpp types/rational.hpp \
  utility/rationaltype.hpp utility/bigint.hpp types/float.hpp \
  types/string.hpp types/boolean.hpp types/parenthesis.hpp types/ops.hpp
typestest.o: test/typestest.cpp types.hpp types/all.hpp types/arch.hpp \
  types/rational.hpp utility/rationaltype.hpp utility/bigint.hpp \
  types/float.hpp types/string.hpp types/boolean.hpp \
  types/parenthesis.hpp types/ops.hpp
all.o: types/all.cpp types/all.hpp types/arch.hpp types/rational.hpp \
  utility/rationaltype.hpp utility/bigint.hpp types/float.hpp \
  types/string.hpp types/boolean.hpp types/parenthesis.hpp types/ops.hpp
boolean.o: types/boolean.cpp types/boolean.hpp types/arch.hpp
float.o: types/float.cpp types/arch.hpp types/float.hpp
ops.o: types/ops.cpp types/arch.hpp types/ops.hpp
parenthesis.o: types/parenthesis.cpp types/all.hpp types/arch.hpp \
  types/rational.hpp utility/rationaltype.hpp utility/bigint.hpp \
  types/float.hpp types/string.hpp types/boolean.hpp \
  types/parenthesis.hpp types/ops.hpp
bigint.o: utility/bigint.cpp utility/bigint.hpp utility/strutility.hpp
rationaltype.o: utility/rationaltype.cpp utility/rationaltype.hpp \
  utility/bigint.hpp
