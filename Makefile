all: wcat wgrep wunzip wzip

wcat: wcat.c
	gcc -o wcat wcat.c -Wall -Werror

wgrep: wgrep.c
	gcc -o wgrep wgrep.c -Wall -Werror

wunzip: wunzip.c
	gcc -o wunzip wunzip.c -Wall -Werror

wzip: wzip.c
	gcc -o wzip wzip.c -Wall -Werror

clean:
	rm -f wcat wgrep wunzip wzip
