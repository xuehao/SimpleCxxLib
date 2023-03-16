#include <catch2/catch_test_macros.hpp>
#include <string>
#include "set.h"
using namespace std;

TEST_CASE("Test Set Class: range-based for") {
    Set<string> set1{"A", "B", "C"};
    Set<string> set2;
    for (const string& elem : set1) {
        set1.add(elem);
    }
    REQUIRE(set1 != set2);
}

static Set<char> charSet(string str) {
    Set<char> set;
    int nChars = str.length();
    for (int i = 0; i < nChars; i++) {
        set.add(str[i]);
    }
    return set;
}

static string charString(const Set<char>& set) {
    string str = "";
    for (char ch : set) {
        str += ch;
    }
    return str;
}

TEST_CASE("Test Set Class: char set") {
    Set<char> lcletters = charSet("abcdefghijklmnopqrstuvwxyz");
    Set<char> vowels = charSet("aeiou");
    Set<char> consonants = charSet("bcdfghjklmnpqrstvwxyz");
    Set<char> onePointTiles = charSet("aeilnorstu");
    Set<char> highPointTiles = charSet("kjxqz");
    Set<char> descenders = charSet("gjpqy");
    Set<char> empty;
    REQUIRE(lcletters.size() == 26);
    REQUIRE(vowels.size() == 5);
    REQUIRE(charString(highPointTiles) == "jkqxz");
    REQUIRE(vowels.contains('a'));
    REQUIRE_FALSE(vowels.contains('x'));
    REQUIRE_FALSE(empty.contains('x'));
    REQUIRE(vowels.isSubsetOf(onePointTiles));
    REQUIRE_FALSE(vowels.isSubsetOf(highPointTiles));
    REQUIRE(empty.isSubsetOf(highPointTiles));
    REQUIRE(empty.isEmpty());
    REQUIRE_FALSE(consonants.isEmpty());
    REQUIRE(vowels.first() == 'a');
    REQUIRE(highPointTiles.first() == 'j');
    REQUIRE_THROWS(empty.first(), "first: set is empty");
    REQUIRE(charString(highPointTiles + vowels) == "aeijkoquxz");
    Set<char> mySet = highPointTiles;
    mySet += vowels;
    REQUIRE(charString(mySet) == "aeijkoquxz");
    REQUIRE(lcletters - vowels == consonants);
    mySet = lcletters;
    mySet -= vowels;
    REQUIRE(mySet == consonants);
    REQUIRE(charString(highPointTiles * descenders) == "jq");
    string str = "";
    for (char ch : vowels)
        str += ch;
    REQUIRE(str == "aeiou");
}

TEST_CASE("Test Set Class: comma operator") {
    Set<int> digits;
    digits += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
    string str;
    for (int x : digits)
        str += integerToString(x);
    REQUIRE(str == "0123456789");
    digits -= 0, 2, 4, 6, 8;
    str = "";
    for (int x : digits)
        str += integerToString(x);
    REQUIRE(str == "13579");
}

static string setSignature(Set<char>& set) {
    string signature;
    for (char ch : set) {
        signature += ch;
    }
    return signature;
}

static void testSetCopy(Set<char>& set, Set<char> setByValue) {
    Set<char> setCopy = set;
    REQUIRE(setByValue.size() == set.size());
    REQUIRE(setCopy.size() == set.size());
    REQUIRE(setSignature(set) == setSignature(setByValue));
    REQUIRE(setSignature(set) == setSignature(setCopy));
}

TEST_CASE("Test Set Class: copy semantics") {
    Set<char> consonants = charSet("bcdfghjklmnpqrstvwxyz");
    Set<char> empty;
    testSetCopy(consonants, consonants);
    testSetCopy(empty, empty);
}
