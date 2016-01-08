TOUT:=execl execv execve minisystem closeexec dup sigact bombarde-emet bombarde-ecoute sourdeoreille sourdeoreille2 sourdeoreille3 famille enfants

tout: ${TOUT}

%: %.c
	gcc -Wall -Werror -ansi -pedantic -D_XOPEN_SOURCE=500 -g -o $@ $<

clean:
	rm ${TOUT}

.PHONY: tout clean
