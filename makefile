all: myls mystat mysearch mytail

myls: myls-hunt.c
	gcc -o myls myls-hunt.c

mystat: mystat-hunt.c
	gcc -o mystat mystat-hunt.c

mysearch: mysearch-hunt.c
	gcc -o mysearch mysearch-hunt.c

mytail: mytail-hunt.c
	gcc -o mytail mytail-hunt.c

clean:
	rm mystat myls mysearch