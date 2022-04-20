all:
	gcc src/main.c src/graph.c src/reader.c src/writer.c src/queue.c src/bfs.c src/priority_queue.c src/dijkstra.c src/splitter.c -o ggapf -lm -ggdb

generate_test: all
	./ggapf -x 10 -y 10 -f 0 -t 10 -n 1 -b 0 -e 99 -r data/sample10x10_nosplit
generate_test_50: all
	./ggapf -x 50 -y 50 -f 0 -t 10 -n 1 -b 0 -e 2499 -r data/sample50x50_nosplit
generate_test_100: all
	./ggapf -x 100 -y 100 -f 0 -t 10 -n 1 -b 0 -e 9999 -r data/sample100x100_nosplit
generate_test_1000: all
	./ggapf -x 1000 -y 1000 -f 0 -t 10 -n 1 -b 0 -e 999999 -r data/sample1000x1000_nosplit

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

valgrind_test: generate_test
	valgrind ./ggapf -s data/sample10x10_nosplit -n 2 -b 0 -e 99 -r data/sample10x10_split2

clean:
	-rm *.o ggapf tester
clean_data:
	-rm data/sample*


#TESTY

#Reakcja na niepoprawne parametry wywołania.
test1:
	./ggapf -x 10 -y 10 -f 0 -t 10 -n 1 -b 0 -r data/sample10x10_nosplit

#Wczytywanie danych i reakcji na zły format danych w pliku.	
test2:
	./ggapf -s data/dane_ktorych_nie_ma -n 2 -b 0 -e 99 -r data/sample10x10_split2

#Definiowanie przez program grafu spójnego oraz niespójnego.
test3:
	./ggapf -s data/sample10x10_nosplit -n 2 -b 0 -e 99 -r data/sample10x10_split2

#Sprawdzanie przez program spójności grafu.
test4:
	./ggapf -x 10 -y 10 -f 0 -t 10 -n 1 -b 0 -e 99 -r data/sample10x10_nosplit

