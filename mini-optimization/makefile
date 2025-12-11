all: mini asm machine

mini: src/main.c src/mini.l src/mini.y src/tac.c src/obj.c include/inst.h include/obj.h include/opcode.h include/tac.h
	lex -o src/mini.l.c src/mini.l
	yacc -d -o src/mini.y.c src/mini.y
	gcc -g3 -Iinclude src/main.c src/mini.l.c src/mini.y.c src/tac.c src/obj.c -o mini

asm: src/asm.l src/asm.y include/inst.h
	lex -o src/asm.l.c src/asm.l
	yacc -d -o src/asm.y.c src/asm.y
	gcc -g3 -Iinclude src/asm.l.c src/asm.y.c -o asm

machine: src/machine.c include/inst.h
	gcc -g3 -Iinclude src/machine.c -o machine

clean:
	rm -fr src/*.l.* src/*.y.* *.s *.x *.o core mini asm machine

test:
	./mini test.m; \
	./asm test.s; \
	./machine test.o

