all:
	gcc src/*.c -o bin/ggapf

do:
	./ggapf 
debug:
	valgrind --show-leak-kinds=all --leak-check=full ./aprox -s spl -p test/dane.1 -g myplot -f 5.1 -t 5.7 -n 300



.PHONY: clean

clean:
	-rm *.o 
