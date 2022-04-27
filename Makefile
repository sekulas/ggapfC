all:
	gcc src/main.c src/graph.c src/reader.c src/writer.c src/queue.c src/bfs.c src/priority_queue.c src/dijkstra.c src/splitter.c -o ggapf -lm -ggdb

# generator tests
# the suffix specifies size of the graph (nxn)
generate_test: all
	./ggapf -x 10 -y 10 -f 0 -t 10 -n 1 -b 0 -e 99 -r data/sample10x10_nosplit
generate_test_50: all
	./ggapf -x 50 -y 50 -f 0 -t 10 -n 1 -b 0 -e 2499 -r data/sample50x50_nosplit
generate_test_100: all
	./ggapf -x 100 -y 100 -f 0 -t 10 -n 1 -b 0 -e 9999 -r data/sample100x100_nosplit
generate_test_1000: all
	./ggapf -x 1000 -y 1000 -f 0 -t 10 -n 1 -b 0 -e 999999 -r data/sample1000x1000_nosplit
generate_test_2000: all
	./ggapf -x 2000 -y 2000 -f 0 -t 10 -n 1 -b 0 -e 3999999 -r data/sample2000x2000_nosplit

# splitter tests
# the suffix specifies number of subgraphs
split_test_2: generate_test
	./ggapf -s data/sample10x10_nosplit -n 2 -b 0 -e 99 -r data/sample10x10_split2
split_test_3: generate_test
	./ggapf -s data/sample10x10_nosplit -n 3 -b 0 -e 99 -r data/sample10x10_split3
split_test_4: generate_test
	./ggapf -s data/sample10x10_nosplit -n 4 -b 0 -e 99 -r data/sample10x10_split4
split_test_5: generate_test
	./ggapf -s data/sample10x10_nosplit -n 5 -b 0 -e 99 -r data/sample10x10_split5
split_test_10: generate_test
	./ggapf -s data/sample10x10_nosplit -n 10 -b 0 -e 99 -r data/sample10x50_split10

split_test_50x50_10: generate_test_50
	./ggapf -s data/sample50x50_nosplit -n 10 -b 0 -e 99 -r data/sample50x50_split10

# valgrind test
valgrind_test: generate_test
	valgrind ./ggapf -s data/sample10x10_nosplit -n 2 -b 0 -e 99 -r data/sample10x10_split2

# clean rules
clean:
	-rm *.o ggapf tester
clean_data:
	-rm data/sample*


### TESTS from functional specs ###
# reaction to wrong args
test1: all
	./ggapf -x 10 -y 10 -f 0 -t 10 -n 1 -b 0 -r data/sample10x10_nosplit

# data loading and reaction to incorrect data format
test2: all
	./ggapf -s data/dane_ktorych_nie_ma -n 2 -b 0 -e 99 -r data/sample10x10_split21

# creating connected or not connected graph
test3: generate_test
	./ggapf -s data/sample10x10_nosplit -n 2 -b 0 -e 99 -r data/sample10x10_split2

# tests 4-8 shows the effects of program modules
# all can be seen in one call
#test4: Checking if graph is connected
#test5: Checking if there is path between given vertices
#test6: Counting the shortest path between given vertices
#test7: Showing the way of the shortest path
#test8: Showing graph
test4 test5 test6 test7 test8: generate_test
	./ggapf -s data/sample10x10_nosplit -b 0 -e 99 -r data/sample10x10_split2
