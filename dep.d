all.o: parsers/all.cpp parsers/all.hpp ast.hpp types.hpp types/all.hpp \
 types/arch.hpp utility/wrapper.hpp types/complex.hpp \
 utility/complextype.hpp utility/rationaltype.hpp utility/bigint.hpp \
 utility/bigint.hpp types/string.hpp types/boolean.hpp \
 types/parenthesis.hpp types/char.hpp types/ops.hpp types/rational.hpp \
 utility/rationaltype.hpp types/float.hpp parsers/opplus.hpp \
 parsers/arch.hpp parsers/opminus.hpp parsers/opmultiply.hpp \
 parsers/opdivide.hpp utility/debug.hpp
opdivide.o: parsers/opdivide.cpp parsers/opdivide.hpp ast.hpp types.hpp \
 types/all.hpp types/arch.hpp utility/wrapper.hpp types/complex.hpp \
 utility/complextype.hpp utility/rationaltype.hpp utility/bigint.hpp \
 utility/bigint.hpp types/string.hpp types/boolean.hpp \
 types/parenthesis.hpp types/char.hpp types/ops.hpp types/rational.hpp \
 utility/rationaltype.hpp types/float.hpp parsers/arch.hpp \
 parsers/all.hpp parsers/opplus.hpp parsers/opminus.hpp \
 parsers/opmultiply.hpp types.hpp utility/debug.hpp
opminus.o: parsers/opminus.cpp parsers/opminus.hpp ast.hpp types.hpp \
 types/all.hpp types/arch.hpp utility/wrapper.hpp types/complex.hpp \
 utility/complextype.hpp utility/rationaltype.hpp utility/bigint.hpp \
 utility/bigint.hpp types/string.hpp types/boolean.hpp \
 types/parenthesis.hpp types/char.hpp types/ops.hpp types/rational.hpp \
 utility/rationaltype.hpp types/float.hpp parsers/arch.hpp types/all.hpp \
 parsers/all.hpp parsers/opplus.hpp parsers/opmultiply.hpp \
 parsers/opdivide.hpp types.hpp
opmultiply.o: parsers/opmultiply.cpp parsers/opmultiply.hpp ast.hpp \
 types.hpp types/all.hpp types/arch.hpp utility/wrapper.hpp \
 types/complex.hpp utility/complextype.hpp utility/rationaltype.hpp \
 utility/bigint.hpp utility/bigint.hpp types/string.hpp types/boolean.hpp \
 types/parenthesis.hpp types/char.hpp types/ops.hpp types/rational.hpp \
 utility/rationaltype.hpp types/float.hpp parsers/arch.hpp \
 parsers/all.hpp parsers/opplus.hpp parsers/opminus.hpp \
 parsers/opdivide.hpp types.hpp
opplus.o: parsers/opplus.cpp parsers/opplus.hpp ast.hpp types.hpp \
 types/all.hpp types/arch.hpp utility/wrapper.hpp types/complex.hpp \
 utility/complextype.hpp utility/rationaltype.hpp utility/bigint.hpp \
 utility/bigint.hpp types/string.hpp types/boolean.hpp \
 types/parenthesis.hpp types/char.hpp types/ops.hpp types/rational.hpp \
 utility/rationaltype.hpp types/float.hpp parsers/arch.hpp \
 parsers/all.hpp parsers/opminus.hpp parsers/opmultiply.hpp \
 parsers/opdivide.hpp types.hpp
asttest.o: test/asttest.cpp
biginttest.o: test/biginttest.cpp
complextypetest.o: test/complextypetest.cpp
parserstest.o: test/parserstest.cpp
preprocessortest.o: test/preprocessortest.cpp
rationaltypetest.o: test/rationaltypetest.cpp
tokenizertest.o: test/tokenizertest.cpp
typestest.o: test/typestest.cpp
all.o: types/all.cpp types/all.hpp types/arch.hpp utility/wrapper.hpp \
 types/complex.hpp utility/complextype.hpp utility/rationaltype.hpp \
 utility/bigint.hpp utility/bigint.hpp types/string.hpp types/boolean.hpp \
 types/parenthesis.hpp types/char.hpp types/ops.hpp types/rational.hpp \
 utility/rationaltype.hpp types/float.hpp
arch.o: types/arch.cpp types/arch.hpp utility/wrapper.hpp
boolean.o: types/boolean.cpp types/boolean.hpp types/arch.hpp \
 utility/wrapper.hpp
char.o: types/char.cpp types/char.hpp types/arch.hpp utility/wrapper.hpp \
 types/all.hpp types/complex.hpp utility/complextype.hpp \
 utility/rationaltype.hpp utility/bigint.hpp utility/bigint.hpp \
 types/string.hpp types/boolean.hpp types/parenthesis.hpp types/ops.hpp \
 types/rational.hpp utility/rationaltype.hpp types/float.hpp
complex.o: types/complex.cpp types/complex.hpp types/arch.hpp \
 utility/wrapper.hpp utility/complextype.hpp utility/rationaltype.hpp \
 utility/bigint.hpp utility/bigint.hpp types/all.hpp types/string.hpp \
 types/boolean.hpp types/parenthesis.hpp types/char.hpp types/ops.hpp \
 types/rational.hpp utility/rationaltype.hpp types/float.hpp
float.o: types/float.cpp types/arch.hpp utility/wrapper.hpp \
 types/float.hpp utility/simplenum.hpp
ops.o: types/ops.cpp types/arch.hpp utility/wrapper.hpp types/ops.hpp
parenthesis.o: types/parenthesis.cpp types/all.hpp types/arch.hpp \
 utility/wrapper.hpp types/complex.hpp utility/complextype.hpp \
 utility/rationaltype.hpp utility/bigint.hpp utility/bigint.hpp \
 types/string.hpp types/boolean.hpp types/parenthesis.hpp types/char.hpp \
 types/ops.hpp types/rational.hpp utility/rationaltype.hpp \
 types/float.hpp
rational.o: types/rational.cpp types/rational.hpp types/arch.hpp \
 utility/wrapper.hpp utility/rationaltype.hpp utility/bigint.hpp \
 types/all.hpp types/complex.hpp utility/complextype.hpp \
 utility/rationaltype.hpp utility/bigint.hpp types/string.hpp \
 types/boolean.hpp types/parenthesis.hpp types/char.hpp types/ops.hpp \
 types/float.hpp utility/simplenum.hpp
string.o: types/string.cpp types/string.hpp types/arch.hpp \
 utility/wrapper.hpp types/all.hpp types/complex.hpp \
 utility/complextype.hpp utility/rationaltype.hpp utility/bigint.hpp \
 utility/bigint.hpp types/boolean.hpp types/parenthesis.hpp \
 types/char.hpp types/ops.hpp types/rational.hpp utility/rationaltype.hpp \
 types/float.hpp utility/strutility.hpp
bigint.o: utility/bigint.cpp utility/bigint.hpp utility/strutility.hpp
complextype.o: utility/complextype.cpp utility/complextype.hpp \
 utility/rationaltype.hpp utility/bigint.hpp utility/bigint.hpp \
 types/rational.hpp types/arch.hpp utility/wrapper.hpp \
 utility/rationaltype.hpp types/float.hpp
debug.o: utility/debug.cpp utility/debug.hpp
rationaltype.o: utility/rationaltype.cpp utility/rationaltype.hpp \
 utility/bigint.hpp utility/debug.hpp
simplenum.o: utility/simplenum.cpp utility/simplenum.hpp
