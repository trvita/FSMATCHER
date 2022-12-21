.PHONY: clean fsmatcher 
CFLAGS = -Wall -Wextra
CPPFLAGS = -MMD

fsmatcher : obj/fsmatcher.o obj/func.o
	gcc $(CFLAGS) -g -o $@ $^

obj/fsmatcher.o: src/fsmatcher.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -o $@ src/fsmatcher.c

obj/func.o: src/func.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src/ -o $@ src/func.c

run/fsmatcher:
	./fsmatcher

clean:
	rm obj/*/*.[od]
