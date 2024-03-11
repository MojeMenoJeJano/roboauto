#include <iostream>
#include "assignment3.h"
#include <vector>

// helper function to print values one certain level
[[maybe_unused]] void printValuesOnGivenLevel(const std::unique_ptr<INode> &root, int depth) {
    if (depth < 0) {
        return;
    }
    if (depth == 0) {
        std::cout << " " << root->value();
    }

    for (auto &i: root->children()) {
        printValuesOnGivenLevel(i, depth - 1);
    }
}

int main() {

    test_getClosestToZero();
    test_countChunks();
    test_getLevelSum();
    test_getReversalsToSort();

    return 0;
}

