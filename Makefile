all:
	gcc src/*.c -lm

testnsp1:
	./a.out -s data/not_connected_graph1.txt -b 1 -e 2
testsp1:
	./a.out -s data/graph1 -b 1 -e 2


clean:
	-rm *.o 

