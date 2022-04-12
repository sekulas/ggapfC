all:
	gcc src/main.c src/graph.c src/reader.c src/writer.c src/queue.c src/bfs.c src/priority_queue.c src/dijkstra.c src/splitter.c -o ggapf -lm -ggdb

generate_test: all
	./ggapf -x 10 -y 10 -f 0 -t 10 -n 1 -b 0 -e 99 -r data/sample10x10_nosplit

split_test_2: generate_test
	./ggapf -s data/sample10x10_nosplit -n 2 -b 0 -e 99 -r data/sample10x10_split2
split_test_3: generate_test
	./ggapf -s data/sample10x10_nosplit -n 3 -b 0 -e 99 -r data/sample10x10_split3
split_test_4: generate_test
	./ggapf -s data/sample10x10_nosplit -n 4 -b 0 -e 99 -r data/sample10x10_split4
split_test_5: generate_test
	./ggapf -s data/sample10x10_nosplit -n 5 -b 0 -e 99 -r data/sample10x10_split5
split_test_10: generate_test
	./ggapf -s data/sample10x10_nosplit -n 10 -b 0 -e 99 -r data/sample10x10_split10

clean:
	-rm *.o ggapf tester

