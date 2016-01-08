TOUT:=th-1 th-maps th-2 th-3-detach th-maps-errno compteurs compteur-incr compteur-incr-rec

tout: ${TOUT}

%: %.c
	gcc -Wall -Werror -pthread -g -o $@ $<

clean:
	rm ${TOUT}

.PHONY: tout clean
