CC=/usr/bin/clang
TOLINK= -lm
CFLAGS= -O3 -Weverything -Werror -Wno-missing-field-initializers -Wno-gnu-statement-expression

default: main

main: main.c imgedit.o imgeditppm.o imgeditfarb.o filters.o
	$(CC) $(CFLAGS) $(TOLINK) main.c imgedit.o imgeditppm.o imgeditfarb.o filters.o -o main

imgedit.o: imgedit.c
	$(CC) $(CFLAGS) imgedit.c -c

imgeditfarb.o: imgeditfarb.c
	$(CC) $(CFLAGS) imgeditfarb.c -c

imgeditppm.o: imgeditppm.c
	$(CC) $(CFLAGS) imgeditppm.c -c

filters.o: filters.c
	$(CC) $(CFLAGS) filters.c -c

clean:
	rm *.o main
