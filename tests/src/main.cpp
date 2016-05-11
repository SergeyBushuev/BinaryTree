
#include <node.h>

#include <catch.hpp>
#include <fstream>
#include <iostream>

SCENARIO("insert_int", "[insert_node]") {
	Tree<int> intTree;
	REQUIRE(intTree.insert_node(1));
	REQUIRE(intTree.insert_node(2));
	REQUIRE(intTree.insert_node(3));
	REQUIRE(intTree.find_node(2));
	REQUIRE(intTree.find_node(3));
	REQUIRE(intTree.find_node(1));
}
 
