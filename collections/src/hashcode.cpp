#include "hashcode.h"
#include <stdint.h>

const int HASH_SEED = 5381;               // Starting point for first cycle
const int HASH_MULTIPLIER = 33;           // Multiplier for each cycle
const int HASH_MASK = unsigned(-1) >> 1;  // All 1 bits except the sign

/*
 * Implementation notes: hashCode
 * ------------------------------
 * This function takes a string key and uses it to derive a hash code,
 * which is a nonnegative integer related to the key by a deterministic
 * function that distributes keys well across the space of integers.
 * The general method is called linear congruence, which is also used
 * in random-number generators.  The specific algorithm used here is
 * called djb2 after the initials of its inventor, Daniel J. Bernstein,
 * Professor of Mathematics at the University of Illinois at Chicago.
 */

int hashCode(bool key) {
    return (int)key;
}

int hashCode(char key) {
    return key;
}

int hashCode(double key) {
    char* byte = (char*)&key;
    unsigned hash = HASH_SEED;
    for (int i = 0; i < (int)sizeof(double); i++) {
        hash = HASH_MULTIPLIER * hash + (int)*byte++;
    }
    return hash & HASH_MASK;
}

int hashCode(float key) {
    char* byte = (char*)&key;
    unsigned hash = HASH_SEED;
    for (int i = 0; i < (int)sizeof(float); i++) {
        hash = HASH_MULTIPLIER * hash + (int)*byte++;
    }
    return hash & HASH_MASK;
}

int hashCode(int key) {
    return key & HASH_MASK;
}

int hashCode(long key) {
    return int(key) & HASH_MASK;
}

int hashCode(const char* str) {
    unsigned hash = HASH_SEED;
    for (int i = 0; str && str[i] != 0; i++) {
        hash = HASH_MULTIPLIER * hash + str[i];
    }
    return int(hash & HASH_MASK);
}

int hashCode(const std::string& str) {
    unsigned hash = HASH_SEED;
    int n = str.length();
    for (int i = 0; i < n; i++) {
        hash = HASH_MULTIPLIER * hash + str[i];
    }
    return int(hash & HASH_MASK);
}

int hashCode(uintptr_t key) {
    return hashCode(static_cast<long>(key));
}

int hashCode(void* key) {
    return hashCode(reinterpret_cast<uintptr_t>(key));
}
