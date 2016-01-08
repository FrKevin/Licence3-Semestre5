TOUT:=mmap1 mmap2 mmap3 mmap4 prodcons philo sig flock-lect flock-ecri

tout: ${TOUT}

%: %.c
	gcc -Wall -Werror -pthread -g -o $@ $<

clean:
	rm ${TOUT}

.PHONY: tout clean
