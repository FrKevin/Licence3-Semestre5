TOUT:=tube fork entrelacs fork2 nonbloc recepteur ign-segv ign-segv2 ign-segv3

tout: ${TOUT}

%: %.c
	gcc -Wall -Werror -ansi -pedantic -D_XOPEN_SOURCE=500 -g -o $@ $<

clean:
	rm ${TOUT}

.PHONY: tout clean
