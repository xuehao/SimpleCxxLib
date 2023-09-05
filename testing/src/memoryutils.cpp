/**
 * @author Xue Hao
 * @version 2023/3/6
 *    Integrated into SimpleCxxLib
 *
 * @author Keith Schwarz
 * @version 2020/3/5
 *    Keith final revision from end of quarter 19-2
 */

#include "memoryutils.h"

#include <cxxabi.h>  // Nonstandard, but supported on g++ and clang.

#include <iostream>
#include <sstream>
#include <typeindex>
#include <unordered_map>

#include "error.h"
using namespace std;

namespace {
/* Type --> Frequency */
unordered_map<type_index, int>& allocationTable() {
    static unordered_map<type_index, int> instance;
    return instance;
}

/* Name --> Type */
unordered_map<string, type_index>& lookupTable() {
    static unordered_map<string, type_index> instance;
    return instance;
}
}  // namespace

namespace MemoryDiagnostics {
/* Injects the type into the appropriate table. */
int registerSentinel(const std::type_info& type) {
    /* std::type_info does not guarantee that .name() will be at all
     * human-readable. Use this g++/clang-specific logic to "demangle" the name
     * back into a human-readable format.
     */
    int statusCode;
    auto* realName = abi::__cxa_demangle(type.name(), nullptr, nullptr, &statusCode);
    if (statusCode != 0)
        error("Internal error: Couldn't demangle name?");

    /* C++ type_info objects don't work well as keys in maps, but std::type_index
     * allows us to fix that.
     */
    lookupTable().insert(make_pair(string(realName), type_index(type)));

    free(realName);
    return 137;  // You know, cause, why not?
}

void recordNew(const type_info& type) {
    allocationTable()[type_index(type)]++;
}

void recordDelete(const type_info& type) {
    allocationTable()[type_index(type)]--;
}

/* Clears the allocation table. */
void clear() {
    allocationTable().clear();
}

/* Returns a list of all imbalanced types. */
map<string, int> typesWithErrors() {
    map<string, int> result;

    /* Loop over types, looking for mismatches. */
    for (const auto& entry : lookupTable()) {
        int record = allocationTable()[entry.second];
        if (record != 0) {
            result[entry.first] = record;
        }
    }

    return result;
}
}  // namespace MemoryDiagnostics

static string pluralize(int val, const string& desc) {
    std::stringstream ss;
    ss << val << ' ' << desc << (val == 1 ? "" : "s");
    return ss.str();
}

/**
 * Function: MEM_CHECK(fn)
 * ------------------------------------------------------------------------------
 * Test if a test case function has memory leaks.
 */
void MEM_CHECK(void (*fn)()) {
    /* Reset memory counters so we don't have carryover across tests. */
    MemoryDiagnostics::clear();

    /* Testing Cases */
    fn();

    /* See if there were any memory leaks. */
    auto errors = MemoryDiagnostics::typesWithErrors();
    if (!errors.empty()) {
        /* We have memory leaks. */
        std::cout << std::endl
                  << "Test had allocation count mismatch with these types:" << std::endl;
        for (const auto& entry : errors) {
            string type = entry.first;
            int delta = entry.second;

            if (delta > 0) {
                std::cout << "\t" << type << ": Leaked " << pluralize(delta, "object") << "."
                          << std::endl;
            } else {
                std::cout << "\t" << type << ": Deallocated " << pluralize(-delta, "more object")
                          << " than allocated." << std::endl;
            }
        }
    } else {
        std::cout << std::endl << "No object leaks." << endl;
    }
}
