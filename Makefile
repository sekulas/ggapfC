all:
	gcc src/main.c src/graph.c src/reader.c src/writer.c src/queue.c src/bfs.c src/priority_queue.c src/dijkstra.c -o ggapf -lm -ggdb

testnsp1:
	./a.out -s data/not_connected_graph1.txt -b 1 -e 2
testsp1:
	./a.out -s data/graph1 -b 1 -e 2


clean:
	-rm *.o 

