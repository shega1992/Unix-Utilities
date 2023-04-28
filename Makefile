all: wcat wgrep wunzip wzip pzip wtee wcp

wcat: wcat.c
	gcc -o wcat wcat.c -Wall -Werror

wgrep: wgrep.c
	gcc -o wgrep wgrep.c -Wall -Werror

wunzip: wunzip.c
	gcc -o wunzip wunzip.c -Wall -Werror

wzip: wzip.c
	gcc -o wzip wzip.c -Wall -Werror

pzip: pzip.c
	gcc -o pzip pzip.c -Wall -Werror -pthread

wtee: wtee.c
	gcc -o wtee wtee.c -Wall -Werror

wcp: wcp.c
	gcc -o wcp wcp.c -Wall -Werror

clean:
	rm -f wcat wgrep wunzip wzip pzip wtee wcp
