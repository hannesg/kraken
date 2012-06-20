build/kraken/node.o: src/kraken/node.cpp src/kraken/node.h src/kraken/visitor.h
	g++ -c --std=c++0x -Isrc -Itests src/kraken/node.cpp -o build/kraken/node.o
build/kraken/base.o: src/kraken/base.cpp src/kraken/base.h
	g++ -c --std=c++0x -Isrc -Itests src/kraken/base.cpp -o build/kraken/base.o
build/kraken/visitor.o: src/kraken/visitor.cpp src/kraken/node.h src/kraken/visitor.h
	g++ -c --std=c++0x -Isrc -Itests src/kraken/visitor.cpp -o build/kraken/visitor.o
build/kraken/token.o: src/kraken/token.cpp src/kraken/base.h src/kraken/range_map.h src/kraken/token.h
	g++ -c --std=c++0x -Isrc -Itests src/kraken/token.cpp -o build/kraken/token.o
build/kraken/node/map.o: src/kraken/node/map.cpp src/kraken/base.h src/kraken/node.h src/kraken/range_map.h src/kraken/range_set.h src/kraken/node/map.h
	g++ -c --std=c++0x -Isrc -Itests src/kraken/node/map.cpp -o build/kraken/node/map.o
build/kraken/symbol_map.o: src/kraken/symbol_map.cpp
	g++ -c --std=c++0x -Isrc -Itests src/kraken/symbol_map.cpp -o build/kraken/symbol_map.o
build/kraken.o: src/kraken.cpp src/kraken/node.h
	g++ -c --std=c++0x -Isrc -Itests src/kraken.cpp -o build/kraken.o
build/test_token.o: tests/test_token.cpp src/kraken/token.h
	g++ -c --std=c++0x -Isrc -Itests tests/test_token.cpp -o build/test_token.o
./test_token: build/test_token.o build/kraken/token.o build/kraken/base.o src/kraken/range_map.h src/kraken/range_set.h
	g++ --std=c++0x -Isrc -Itests build/test_token.o build/kraken/token.o build/kraken/base.o  -o test_token
build/test_range_map.o: tests/test_range_map.cpp src/kraken/range_map.h
	g++ -c --std=c++0x -Isrc -Itests tests/test_range_map.cpp -o build/test_range_map.o
./test_range_map: build/test_range_map.o src/kraken/range_map.h src/kraken/range_set.h
	g++ --std=c++0x -Isrc -Itests build/test_range_map.o  -o test_range_map
build/test_node_pool.o: tests/test_node_pool.cpp src/kraken/node.h src/kraken/node/map.h src/kraken/base.h
	g++ -c --std=c++0x -Isrc -Itests tests/test_node_pool.cpp -o build/test_node_pool.o
./test_node_pool: build/test_node_pool.o build/kraken/node.o build/kraken/node/map.o build/kraken/base.o build/kraken/visitor.o src/kraken/range_map.h src/kraken/range_set.h
	g++ --std=c++0x -Isrc -Itests build/test_node_pool.o build/kraken/node.o build/kraken/node/map.o build/kraken/base.o build/kraken/visitor.o  -o test_node_pool
all: ./test_token ./test_range_map ./test_node_pool
clean: 
	rm -rf ./test_token ./test_range_map ./test_node_pool build/kraken/node.o build/kraken/base.o build/kraken/visitor.o build/kraken/token.o build/kraken/node/map.o build/kraken/symbol_map.o build/kraken.o
.PHONY: all clean
