compiler = g++
compiler_args = -Wall -ggdb

test: wire.o truth.o gates.o test-gates.cpp
	$(compiler) $(compiler_args) -o test test-gates.cpp wire.o truth.o gates.o
gates.o: gates.h gates.cpp wire.o
	$(compiler) $(compiler_args) -c gates.cpp
truth.o: truth.h truth.cpp wire.o
	$(compiler) $(compiler_args) -c truth.cpp
wire.o: wire.h wire.cpp
	$(compiler) $(compiler_args) -c wire.cpp
clean:
	rm *.o test
