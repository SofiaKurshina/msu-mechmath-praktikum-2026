all: a.out

CFLAGS = -O3 -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors \
	 -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long \
	 -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast \
	 -Wnested-externs -Wmaybe-uninitialized

a.out: task.o solve.o array_io.o
	gcc $(CFLAGS) $^ -o $@ -lm

task.o: task.c io_status.h array_io.h solve.h
	gcc -c $(CFLAGS) $<

array_io.o: array_io.c array_io.h
	gcc -c $(CFLAGS) array_io.c

solve.o: solve.c solve.h
	gcc -c $(CFLAGS) solve.c

clean:
	rm *.o
