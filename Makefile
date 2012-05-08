

test_range_map:
	g++ --std=c++0x tests/test_range_map.cpp -Isrc -O0 -o test_range_map

test_node_pool: src/kraken/node.cpp tests/test_node_pool.cpp src/kraken/node.h src/kraken/visitor.h src/kraken/visitor.cpp
		g++ --std=c++0x src/kraken/node.cpp src/kraken/visitor.cpp tests/test_node_pool.cpp -Isrc -O0 -o test_node_pool
