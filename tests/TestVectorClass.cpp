#include <catch2/catch_test_macros.hpp>
#include <string>
#include "vector.h"
using namespace std;

TEST_CASE("Test Vector Class: add/remove/size/get/set") {
    Vector<string> v;
    v.add("A");
    v.add("C");
    v.add("D");
    v.insert(1, "B");
    REQUIRE(v.size() == 4);
    REQUIRE(v.get(0) == "A");
    REQUIRE(v.get(1) == "B");
    REQUIRE(v.get(2) == "C");
    REQUIRE(v.get(3) == "D");
    v.set(0, "a");
    REQUIRE(v.get(0) == "a");
    v.remove(0);
    REQUIRE(v.size() == 3);
}

TEST_CASE("Test Vector Class: equals") {
    Vector<int> vec1{1, 2, 3, 4, 5};
    Vector<int> vec2{1, 2, 3, 4, 5};
    REQUIRE(vec1.equals(vec2));
    vec2.remove(2);
    REQUIRE_FALSE(vec1.equals(vec2));
}

TEST_CASE("Test Vector Class: subList") {
    Vector<int> vec1{1, 2, 3, 4, 5};
    auto vec2 = vec1.subList(0, 2);
    REQUIRE(vec2.size() == 2);
    REQUIRE(vec2.get(0) == 1);
    REQUIRE(vec2.get(1) == 2);
    REQUIRE_THROWS(vec1.subList(-1, 2));
    auto vec3 = vec1.subList(0);
    REQUIRE(vec1.equals(vec3));
}

TEST_CASE("Test Vector Class: overloading") {
    Vector<int> vec1;
    vec1 += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
    REQUIRE(vec1.size() == 10);
    Vector<int> vec2{1, 2, 3, 4, 5};
    int value = 1;
    for (const int& val : vec2) {
        REQUIRE(val == value);
        value++;
    }
    auto vec3 = vec1 + vec2;
    REQUIRE(vec3.size() == 15);
    vec1 += vec2;
    REQUIRE(vec1.size() == 15);
}

TEST_CASE("Test Vector Class: range-based for") {
    Vector<string> vec1{"A", "B", "C"};
    for (string& elem : vec1) {
        elem += elem;
    }
    Vector<string> vec2{"AA", "BB", "CC"};
    REQUIRE(vec1.equals(vec2));
}

static string vectorSignature(Vector<string>& vec) {
    string signature;
    for (int i = 0; i < vec.size(); i++) {
        if (i > 0)
            signature += "/";
        signature += vec[i];
    }
    return signature;
}

static void testVectorCopy(Vector<string>& vec, Vector<string> vecByValue) {
    Vector<string> vecCopy = vec;
    REQUIRE(vecByValue.size() == vec.size());
    REQUIRE(vecCopy.size() == vec.size());
    REQUIRE(vectorSignature(vec) == vectorSignature(vecByValue));
    REQUIRE(vectorSignature(vec) == vectorSignature(vecCopy));
}

TEST_CASE("Test Vector Class: copy semantics") {
    Vector<string> vec1{"A", "B", "C"};
    testVectorCopy(vec1, vec1);
}
