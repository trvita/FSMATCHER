.PHONY: clean bin/fsmatcher test
CFLAGS = -Wall -Wextra
CPPFLAGS = -MMD

bin/fsmatcher: obj/fsmatcher.o obj/func.o
	gcc $(CFLAGS) -g -o $@ $^

test: bin/test

bin/test: obj/test/main.o obj/test/test.o obj/func.o
	gcc $(CFLAGS) -g -o $@ $^

obj/func.o: src/func.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -o $@ src/func.c

obj/fsmatcher.o: src/fsmatcher.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -o $@ src/fsmatcher.c

obj/test/test.o: test/test.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -I thirdparty/ -o $@ $<

obj/test/main.o: test/main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -I thirdparty/ -o $@ $<

run/fsmatcher:
	./bin/fsmatcher

run/test:
	./bin/test

clean:
	rm obj/*/*.[od]