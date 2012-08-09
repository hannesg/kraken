build/kraken.o: src/kraken.cpp src/kraken.h src/kraken/the.h build
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken.cpp -o build/kraken.o
build/kraken/link.o: src/kraken/link.cpp src/kraken/link.h src/kraken/decoder.h src/kraken/node/result.h build/kraken
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken/link.cpp -o build/kraken/link.o
build/kraken/visitor.o: src/kraken/visitor.cpp src/kraken/visitor.h src/kraken/node.h build/kraken
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken/visitor.cpp -o build/kraken/visitor.o
build/kraken/the.o: src/kraken/the.cpp src/kraken/node.h src/kraken/the.h build/kraken
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken/the.cpp -o build/kraken/the.o
build/kraken/attack.o: src/kraken/attack.cpp src/kraken.h src/kraken/node.h src/kraken/link.h src/kraken/the.h src/kraken/attack.h build/kraken
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken/attack.cpp -o build/kraken/attack.o
build/kraken/node.o: src/kraken/node.cpp src/kraken/node.h src/kraken/visitor.h src/kraken/base.h src/kraken/decoder.h src/kraken/node/result.h build/kraken
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken/node.cpp -o build/kraken/node.o
build/kraken/node/placeholder.o: src/kraken/node/placeholder.cpp src/kraken/node.h src/kraken/node/result.h src/kraken/node/placeholder.h build/kraken/node
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken/node/placeholder.cpp -o build/kraken/node/placeholder.o
build/kraken/node/result.o: src/kraken/node/result.cpp src/kraken/decoder.h src/kraken/node.h src/kraken/node/result.h build/kraken/node
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken/node/result.cpp -o build/kraken/node/result.o
build/kraken/node/fork.o: src/kraken/node/fork.cpp src/kraken/node.h src/kraken/node/fork.h src/kraken/node/result.h build/kraken/node
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken/node/fork.cpp -o build/kraken/node/fork.o
build/kraken/node/terminal.o: src/kraken/node/terminal.cpp src/kraken/node/terminal.h src/kraken/node.h src/kraken/base.h src/kraken/node/result.h build/kraken/node
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken/node/terminal.cpp -o build/kraken/node/terminal.o
build/kraken/node/replacer.o: src/kraken/node/replacer.cpp src/kraken/node/replacer.h src/kraken/visitor.h src/kraken/node.h build/kraken/node
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken/node/replacer.cpp -o build/kraken/node/replacer.o
build/kraken/node/map.o: src/kraken/node/map.cpp src/kraken/base.h src/kraken/node.h src/kraken/range_map.h src/kraken/range_set.h src/kraken/node/result.h src/kraken/node/map.h build/kraken/node
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken/node/map.cpp -o build/kraken/node/map.o
build/kraken/token.o: src/kraken/token.cpp src/kraken/token.h src/kraken/base.h src/kraken/node/map.h src/kraken/node/placeholder.h src/kraken/node/replacer.h src/kraken/range_map.h src/kraken/node.h build/kraken
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken/token.cpp -o build/kraken/token.o
build/kraken/base.o: src/kraken/base.cpp src/kraken/base.h build/kraken
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests src/kraken/base.cpp -o build/kraken/base.o
build/test_node_result.o: tests/test_node_result.cpp src/kraken/base.h src/kraken/node.h src/kraken/node/result.h src/kraken/node/terminal.h build
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests tests/test_node_result.cpp -o build/test_node_result.o
./test_node_result: build/test_node_result.o build/kraken/base.o build/kraken/node.o build/kraken/node/result.o build/kraken/node/terminal.o build/kraken/visitor.o src/kraken/decoder.h
	g++  -pthread -Wall -std=c++0x build/test_node_result.o build/kraken/base.o build/kraken/node.o build/kraken/node/result.o build/kraken/node/terminal.o build/kraken/visitor.o  -o test_node_result
build/test_node_pool.o: tests/test_node_pool.cpp src/kraken/node.h src/kraken/node/map.h src/kraken/node/terminal.h src/kraken/node/result.h src/kraken/base.h build
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests tests/test_node_pool.cpp -o build/test_node_pool.o
./test_node_pool: build/test_node_pool.o build/kraken/node.o build/kraken/node/map.o build/kraken/node/terminal.o build/kraken/node/result.o build/kraken/base.o build/kraken/visitor.o src/kraken/decoder.h src/kraken/range_map.h src/kraken/range_set.h
	g++  -pthread -Wall -std=c++0x build/test_node_pool.o build/kraken/node.o build/kraken/node/map.o build/kraken/node/terminal.o build/kraken/node/result.o build/kraken/base.o build/kraken/visitor.o  -o test_node_pool
build/mock_string.o: tests/mock_string.cpp tests/mock_string.h src/kraken/decoder.h build
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests tests/mock_string.cpp -o build/mock_string.o
build/test_range_map.o: tests/test_range_map.cpp src/kraken/range_map.h build
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests tests/test_range_map.cpp -o build/test_range_map.o
./test_range_map: build/test_range_map.o src/kraken/range_map.h src/kraken/range_set.h
	g++  -pthread -Wall -std=c++0x build/test_range_map.o  -o test_range_map
build/test_node_map.o: tests/test_node_map.cpp tests/mock_string.h src/kraken/node/map.h src/kraken/node/terminal.h build
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests tests/test_node_map.cpp -o build/test_node_map.o
./test_node_map: build/test_node_map.o build/mock_string.o build/kraken/node/map.o build/kraken/node/terminal.o src/kraken/decoder.h build/kraken/base.o build/kraken/node.o src/kraken/range_map.h src/kraken/range_set.h build/kraken/node/result.o build/kraken/visitor.o
	g++  -pthread -Wall -std=c++0x build/test_node_map.o build/mock_string.o build/kraken/node/map.o build/kraken/node/terminal.o build/kraken/base.o build/kraken/node.o build/kraken/node/result.o build/kraken/visitor.o  -o test_node_map
build/test_attack.o: tests/test_attack.cpp src/kraken/base.h tests/mock_string.h src/kraken/attack.h src/kraken/the.h src/kraken/node/map.h src/kraken/node/terminal.h build
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests tests/test_attack.cpp -o build/test_attack.o
./test_attack: build/test_attack.o build/kraken/base.o build/mock_string.o build/kraken/attack.o build/kraken/the.o build/kraken/node/map.o build/kraken/node/terminal.o src/kraken/decoder.h build/kraken.o build/kraken/node.o build/kraken/link.o src/kraken/range_map.h src/kraken/range_set.h build/kraken/node/result.o build/kraken/visitor.o
	g++  -pthread -Wall -std=c++0x build/test_attack.o build/kraken/base.o build/mock_string.o build/kraken/attack.o build/kraken/the.o build/kraken/node/map.o build/kraken/node/terminal.o build/kraken.o build/kraken/node.o build/kraken/link.o build/kraken/node/result.o build/kraken/visitor.o  -o test_attack
build/test_token.o: tests/test_token.cpp src/kraken/token.h src/kraken/node.h src/kraken/node/terminal.h build
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests tests/test_token.cpp -o build/test_token.o
./test_token: build/test_token.o build/kraken/token.o build/kraken/node.o build/kraken/node/terminal.o build/kraken/base.o build/kraken/node/map.o build/kraken/node/placeholder.o build/kraken/node/replacer.o src/kraken/range_map.h build/kraken/visitor.o src/kraken/decoder.h build/kraken/node/result.o src/kraken/range_set.h
	g++  -pthread -Wall -std=c++0x build/test_token.o build/kraken/token.o build/kraken/node.o build/kraken/node/terminal.o build/kraken/base.o build/kraken/node/map.o build/kraken/node/placeholder.o build/kraken/node/replacer.o build/kraken/visitor.o build/kraken/node/result.o  -o test_token
build/test_link.o: tests/test_link.cpp src/kraken/link.h build
	g++ -c  -pthread -Wall -std=c++0x -Isrc -Itests tests/test_link.cpp -o build/test_link.o
./test_link: build/test_link.o build/kraken/link.o src/kraken/decoder.h build/kraken/node/result.o build/kraken/base.o build/kraken/node.o build/kraken/visitor.o
	g++  -pthread -Wall -std=c++0x build/test_link.o build/kraken/link.o build/kraken/node/result.o build/kraken/base.o build/kraken/node.o build/kraken/visitor.o  -o test_link
build: 
	mkdir -p build
build/kraken: 
	mkdir -p build/kraken
build/kraken/node: 
	mkdir -p build/kraken/node
all: ./test_node_result ./test_node_pool ./test_range_map ./test_node_map ./test_attack ./test_token ./test_link
clean: 
	rm -rf ./test_node_result ./test_node_pool ./test_range_map ./test_node_map ./test_attack ./test_token ./test_link build/kraken.o build/kraken/link.o build/kraken/visitor.o build/kraken/the.o build/kraken/attack.o build/kraken/node.o build/kraken/node/placeholder.o build/kraken/node/result.o build/kraken/node/fork.o build/kraken/node/terminal.o build/kraken/node/replacer.o build/kraken/node/map.o build/kraken/token.o build/kraken/base.o build/mock_string.o build build/kraken build/kraken/node
Makefile: configure.rb src/* tests/*
	which ruby > /dev/null && ruby configure.rb > Makefile
run_tests: all
	ls | grep test_ | sed 's/test_/valgrind\ -q\ \.\/test_/' | sh
tests: clean run_tests
.PHONY: all clean tests run_tests
