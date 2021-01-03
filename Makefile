LUA=lua5.2

default:
	gcc -c -fPIC -Wno-implicit-function-declaration -Wall -m64 -lm -lao -l$(LUA) -I/usr/include/$(LUA) src/soundness.c -o src/soundness.o
	gcc -fPIC -Wall -lm -lao -l$(LUA) -I/usr/include/$(LUA) src/soundness.o -o src/soundness.so -shared

clean:
	rm -f src/*.0
	rm -f src/*.so
	rm -f src/*.o

