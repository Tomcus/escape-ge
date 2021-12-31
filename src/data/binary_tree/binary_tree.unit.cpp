#include "binary_tree/binary_tree.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Binary tree tests with simple value type (int)", "[unit][binaryTree][binary_tree]") {
    esc::data::BinaryTreeHeap<int> heap;

    SECTION("Simple adding") {
        heap.push(120);
        heap.push(42);
        heap.push(12);
        heap.push(13);
        heap.push(43);
        heap.push(121);
        REQUIRE(heap.size() == 6);
    }
}