TOUT:=creat creat2 environnement

tout: ${TOUT}

%: %.c
	gcc -Wall -Werror -ansi -pedantic -g -o $@ $<

test: creat
	./creat
	chmod -rwx /tmp/test
	./creat

clean:
	rm ${TOUT}

.PHONY: tout test clean
