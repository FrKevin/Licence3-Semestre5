TOUT:=exit1 exit2 th-prodcons th-sig th-fork Synch.class remplissage-tube pseudocp socket

tout: ${TOUT}

%: %.c
	gcc -Wall -Werror -pthread -g -o $@ $<

%.class: %.java
	javac $^

clean:
	rm ${TOUT}

.PHONY: tout clean
