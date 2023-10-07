LUA=lua5.3

default:
	gcc -c -fPIC -Wno-implicit-function-declaration -Wall -lm -lao -l$(LUA) -I/usr/include/$(LUA) src/soundness.c -o src/soundness.o
	gcc -fPIC -Wall -lm -lao -l$(LUA) -I/usr/include/$(LUA) src/soundness.o -o src/soundness.so -shared

deb:
	$(eval LUA=lua5.1)
	gcc -c -fPIC -Wno-implicit-function-declaration -Wall -lm -lao -l$(LUA) -I/usr/include/$(LUA) src/soundness.c -o src/soundness.o
	gcc -fPIC -Wall -lm -lao -l$(LUA) -I/usr/include/$(LUA) src/soundness.o -o src/lib$(LUA)-soundness.so.0.0.0 -shared
	$(eval LUA=lua5.2)
	gcc -c -fPIC -Wno-implicit-function-declaration -Wall -lm -lao -l$(LUA) -I/usr/include/$(LUA) src/soundness.c -o src/soundness.o
	gcc -fPIC -Wall -lm -lao -l$(LUA) -I/usr/include/$(LUA) src/soundness.o -o src/lib$(LUA)-soundness.so.0.0.0 -shared
	$(eval LUA=lua5.3)
	gcc -c -fPIC -Wno-implicit-function-declaration -Wall -lm -lao -l$(LUA) -I/usr/include/$(LUA) src/soundness.c -o src/soundness.o
	gcc -fPIC -Wall -lm -lao -l$(LUA) -I/usr/include/$(LUA) src/soundness.o -o src/lib$(LUA)-soundness.so.0.0.0 -shared

clean:
	rm -f src/*.0
	rm -f src/*.so
	rm -f src/*.o

