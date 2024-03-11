#include "assignment3.h"
#include <cassert>

void test_getClosestToZero() {
    assert(0 == getClosestToZero(std::vector<int>{0, 2, 3, -4, 0, 5, 100}));
    assert(2 == getClosestToZero(std::vector<int>{65, 2, 3, -4, 71, 5, 100}));
    assert((-5) == getClosestToZero(std::vector<int>{3443, 25, 322, -24, 777, -5, 100}));
    assert(2 == getClosestToZero(std::vector<int>{22, 9, 2, -4, 77, 5 - 2, 100}));
}

void test_countChunks() {
    assert(2 == countChunks(std::vector<int>{0, 2, 3, -4, 0, 5, 100}));
    assert(3 == countChunks(std::vector<int>{0, 0, 0, 0, 5, 666, 7, 8, 2, 0, 0, 0, 0, 3, -4, 0, 5, 1000, 0, 0, 0, 0}));
    assert(3 == countChunks(std::vector<int>{5, 666, 7, 8, 2, 0, 0, 0, 0, 3, -4, 0, 5, 1000}));
    assert(1 == countChunks(std::vector<int>{1}));
    assert(6 == countChunks(std::vector<int>{1, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0}));
}

void test_getLevelSum() {

    int level = 0;
    int depth = 5;

    auto root = std::make_unique<Node>();
    makeTree(static_cast<Node *>(root.get()), depth);

    assert(getLevelSum(*root, level) == static_cast<int>(pow(2, level)));
    level++;
    assert(getLevelSum(*root, level) == static_cast<int>(pow(2, level)));
    level++;
    assert(getLevelSum(*root, level) == static_cast<int>(pow(2, level)));
    level++;
    assert(getLevelSum(*root, level) == static_cast<int>(pow(2, level)));
}

// helper function to test if two vector equals
bool doVectorsEqual(const std::vector<std::size_t> &result, const std::vector<int> &functionShouldEqual) {
    std::size_t sizeOfResult = result.size();
    std::size_t sizeOfArr = functionShouldEqual.size();

    for (int i = 0; (i < sizeOfArr) && (i < sizeOfResult); i++) {
        if (result[i] != functionShouldEqual[i]) {
            return false;
        }
    }
    return true;
}

void test_getReversalsToSort() {
    std::vector<int> arr{2, 3, 1, 4, 0};
    std::vector<int> functionShouldEqual{4, 5, 3, 4, 2};

    std::vector<int> arr1{2, 3, 1, 44, 0};
    std::vector<int> functionShouldEqual1{4, 5, 3, 4, 2};

    std::vector<int> arr2{2, 3, 1, 4, 0, 5};
    std::vector<int> functionShouldEqual2{4, 5, 3, 4, 2};

    std::vector<int> arr3{12, 13, 11, 14};
    std::vector<int> functionShouldEqual3{2, 3};

    auto result = getReversalsToSort(arr);
    assert(doVectorsEqual(result, functionShouldEqual));

    result = getReversalsToSort(arr1);
    assert(doVectorsEqual(result, functionShouldEqual1));

    result = getReversalsToSort(arr2);
    assert(doVectorsEqual(result, functionShouldEqual2));

    result = getReversalsToSort(arr3);
    assert(doVectorsEqual(result, functionShouldEqual3));
}
/*
 * General rules:
 * - You can use modern C++ features (anything that is supported by modern compilers)
 * - Try to validate input parameters if it makes sense, throw exceptions if needed
 * - You are allowed to use STL (so adding includes is allowed)
 */

/**
 * Implement a method that returns number that is closest to zero in a given vector.
 * If there are two equally close to zero elements like 2 and -2,
 * then consider the positive element to be "closer" to zero.
 */

int getClosestToZero(const std::vector<int> &arr) {
    if (arr.empty()) {
        throw std::invalid_argument("vector is empty");
    }
    int temp = arr[0]; // I can do this because it is not empty
    for (int i: arr) {

        if (abs(i) < abs(temp)) { // if the number is closer to zero
            temp = i;
        }
        if ((i + temp) == 0) { // if the number are -2 and 2 prefer positive
            temp = abs(i);
        }
    }
    return temp;
}

/**
 * Please implement this method to return count of chunks in given array.
 *
 * Chunk is defined as continuous sequence of one or more non-zero numbers separated by one or more zeroes.
 * Input can contain leading and trailing zeroes.
 *
 * Example: [5, 4, 0, 0, -1, 0, 2, 0, 7] contains 3 chunks
 */
std::size_t countChunks(const std::vector<int> &arr) {
    if (arr.empty()) {
        return 0;
    }
    std::size_t chunks{0};
    for (int i = 0; i < (arr.size() - 1); i++) {
        if ((arr[i] != 0) && (arr[i + 1] == 0)) {
            chunks++;
        }
    }
    if (arr.back() != 0) {
        chunks++;
    }
    return chunks;
}

/**
 * Open INode.h to see the INode interface.
 *
 * Implement following function that shall traverse the tree,
 * and return the sum of the values (INode.value()) of all nodes
 * at the level 'n' in the tree.
 * 
 * Node root is assumed to be at the level 0. All its children are level 1, etc.
 */

int countValuesOnLevel(const INode &node, int depth, std::size_t wantedDepth) {
    int sum = 0;

    if (depth == wantedDepth) {
        sum += node.value();
    }
    auto &v = node.children();
    if (depth < wantedDepth) {
        for (auto &i: v) {
            sum += countValuesOnLevel(*i, depth + 1, wantedDepth);
        }
    }
    return sum;
}


int getLevelSum(const INode &root, std::size_t n) {
    int result = countValuesOnLevel(root, 0, n);
    return result;
}

/**
 * Imagine a sort algorithm, that sorts array of integers by repeatedly reversing
 * the order of the first several elements of it.
 *
 * For example, to sort [12,13,11,14], you need to reverse the order of the first two (2)
 * elements. You will get [13,12,11,14].
 * Then you shall reverse the order of the first three (3) elements,
 * and you will get [11,12,13,14]
 *
 * For this assignment you shall implement function
 * that returns list of integers corresponding to the required reversals.
 * E.g. for given vector [12,13,11,14]
 * the function should return [2, 3].
 */
int findPosition(int position, const std::vector<int> &v) {
    if (v.empty()) {
        throw std::invalid_argument("vector is empty");
    }
    for (int i = 0; i <= v.size() - 1; i++) {
        if (position == v[i]) {
            return i;
        }
    }
    return 0;
}

//make projection from variables in given vector to number form 0 to "number of variables"
void projection(std::vector<int> &projection, const std::vector<int> &arr) {
    if (arr.empty()) {
        throw std::invalid_argument("vector is empty");
    }

    std::size_t size = arr.size();
    std::vector<int> v = arr;
    projection = arr;

    std::sort(v.begin(), v.end());

    for (int k{0}; k < (size); k++) {
        for (int l{0}; l < (size); l++) {
            if (projection[k] == v[l]) {
                projection[k] = l;
            }
        }
    }
}

std::vector<std::size_t> getReversalsToSort(const std::vector<int> &arr) {
    if (arr.empty()) {
        throw std::invalid_argument("vector is empty");
    }
    std::vector<std::size_t> result{};
    std::vector<int> v = arr; // coping a vector is expensive :(
    projection(v, arr);
    int size = arr.size();
    size--;

    // go from biggest value to smallest, find if it is in its place, if not put it where it belongs
    for (int i = size; i > 0; i--) {

        if (v[i] != i) {
            int positionOfCurrentlySortingElement = findPosition(i, v);
            std::reverse(v.begin(), (v.begin() + positionOfCurrentlySortingElement + 1));

            std::reverse(v.begin(), (v.begin() + i + 1));
            if (0 != positionOfCurrentlySortingElement) {
                result.push_back(positionOfCurrentlySortingElement + 1);
            }
            result.push_back(i + 1);
        }
    }
    return result;
}