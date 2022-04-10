all:
	gcc src/*.c -lm

make testnsp1:
	./a.out -s data/not_connected_graph1.txt -b 1 -e 2


clean:
	-rm *.o 

