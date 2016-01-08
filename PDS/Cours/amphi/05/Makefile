TOUT:=piletas fork2 fork3 fork4 fork5 fork-wait execseul

tout: ${TOUT}

%: %.c
	gcc -Wall -Werror -ansi -pedantic -D_XOPEN_SOURCE=500 -g -o $@ $<

clean:
	rm ${TOUT}

.PHONY: tout clean
