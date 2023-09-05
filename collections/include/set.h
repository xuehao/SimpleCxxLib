/*
 * File: set.h
 * -----------
 * This file exports the <code>Set</code> class, which implements a
 * collection for storing a set of distinct elements.
 */

/*************************************************************************/
/* Stanford Portable Library                                             */
/* Copyright (c) 2014 by Eric Roberts <eroberts@cs.stanford.edu>         */
/*                                                                       */
/* This program is free software: you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or     */
/* (at your option) any later version.                                   */
/*                                                                       */
/* This program is distributed in the hope that it will be useful,       */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/* GNU General Public License for more details.                          */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

#ifndef _set_h
#define _set_h

#include <initializer_list>
#include <iostream>

#include "compare.h"
#include "map.h"
#include "vector.h"

/*
 * Class: Set<ValueType>
 * ---------------------
 * This class stores a collection of distinct elements.
 */

template <typename ValueType>
class Set {
public:
    /*
     * Constructor: Set
     * Usage: Set<ValueType> set;
     * --------------------------
     * Creates an empty set of the specified element type.
     */

    Set();
    Set(std::initializer_list<ValueType> list);

    /*
     * Destructor: ~Set
     * ----------------
     * Frees any heap storage associated with this set.
     */

    virtual ~Set();

    /*
     * Method: size
     * Usage: count = set.size();
     * --------------------------
     * Returns the number of elements in this set.
     */

    int size() const;

    /*
     * Method: isEmpty
     * Usage: if (set.isEmpty()) ...
     * -----------------------------
     * Returns <code>true</code> if this set contains no elements.
     */

    bool isEmpty() const;

    /*
     * Method: add
     * Usage: set.add(value);
     * ----------------------
     * Adds an element to this set, if it was not already there.  For
     * compatibility with the STL <code>set</code> class, this method
     * is also exported as <code>insert</code>.
     */

    void add(const ValueType& value);
    void insert(const ValueType& value);

    /*
     * Method: remove
     * Usage: set.remove(value);
     * -------------------------
     * Removes an element from this set.  If the value was not
     * contained in the set, no error is generated and the set
     * remains unchanged.
     */

    void remove(const ValueType& value);

    /*
     * Method: contains
     * Usage: if (set.contains(value)) ...
     * -----------------------------------
     * Returns <code>true</code> if the specified value is in this set.
     */

    bool contains(const ValueType& value) const;

    /*
     * Method: isSubsetOf
     * Usage: if (set.isSubsetOf(set2)) ...
     * ------------------------------------
     * Implements the subset relation for sets.  This method returns
     * <code>true</code> if every element of this set is
     * contained in <code>set2</code>.
     */

    bool isSubsetOf(const Set& set2) const;

    /*
     * Method: clear
     * Usage: set.clear();
     * -------------------
     * Removes all elements from this set.
     */

    void clear();

    /*
     * Operator: ==
     * Usage: set1 == set2
     * -------------------
     * Returns <code>true</code> if <code>set1</code> and <code>set2</code>
     * contain the same elements.
     */

    bool operator==(const Set& set2) const;

    /*
     * Operator: !=
     * Usage: set1 != set2
     * -------------------
     * Returns <code>true</code> if <code>set1</code> and <code>set2</code>
     * are different.
     */

    bool operator!=(const Set& set2) const;

    /*
     * Operators: <, >, <=, >=
     * Usage: if (set1 <= set2) ...
     * ...
     * ----------------------------
     * Relational operators to compare two sets.
     * The <, >, <=, >= operators require that the ValueType has a < operator
     * so that the elements can be compared pairwise.
     */
    bool operator<(const Set& set2) const;
    bool operator<=(const Set& set2) const;
    bool operator>(const Set& set2) const;
    bool operator>=(const Set& set2) const;

    /*
     * Operator: +
     * Usage: set1 + set2
     *        set1 + element
     * ---------------------
     * Returns the union of sets <code>set1</code> and <code>set2</code>, which
     * is the set of elements that appear in at least one of the two sets.  The
     * right hand set can be replaced by an element of the value type, in which
     * case the operator returns a new set formed by adding that element.
     */

    Set operator+(const Set& set2) const;
    Set operator+(const ValueType& element) const;

    /*
     * Operator: *
     * Usage: set1 * set2
     * ------------------
     * Returns the intersection of sets <code>set1</code> and <code>set2</code>,
     * which is the set of all elements that appear in both.
     */

    Set operator*(const Set& set2) const;

    /*
     * Operator: -
     * Usage: set1 - set2
     *        set1 - element
     * ---------------------
     * Returns the difference of sets <code>set1</code> and <code>set2</code>,
     * which is all the elements that appear in <code>set1</code> but
     * not <code>set2</code>.  The right hand set can be replaced by an
     * element of the value type, in which case the operator returns a new
     * set formed by removing that element.
     */

    Set operator-(const Set& set2) const;
    Set operator-(const ValueType& element) const;

    /*
     * Operator: +=
     * Usage: set1 += set2;
     *        set1 += value;
     * ---------------------
     * Adds all of the elements from <code>set2</code> (or the single
     * specified value) to <code>set1</code>.  As a convenience, the
     * <code>Set</code> package also overloads the comma operator so
     * that it is possible to initialize a set like this:
     *
     *<pre>
     *    Set<int> digits;
     *    digits += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
     *</pre>
     */

    Set& operator+=(const Set& set2);
    Set& operator+=(const ValueType& value);

    /*
     * Operator: *=
     * Usage: set1 *= set2;
     * --------------------
     * Removes any elements from <code>set1</code> that are not present in
     * <code>set2</code>.
     */

    Set& operator*=(const Set& set2);

    /*
     * Operator: -=
     * Usage: set1 -= set2;
     *        set1 -= value;
     * ---------------------
     * Removes the elements from <code>set2</code> (or the single
     * specified value) from <code>set1</code>.  As a convenience, the
     * <code>Set</code> package also overloads the comma operator so
     * that it is possible to remove multiple elements from a set
     * like this:
     *
     *<pre>
     *    digits -= 0, 2, 4, 6, 8;
     *</pre>
     *
     * which removes the values 0, 2, 4, 6, and 8 from the set
     * <code>digits</code>.
     */

    Set& operator-=(const Set& set2);
    Set& operator-=(const ValueType& value);

    /*
     * Method: first
     * Usage: ValueType value = set.first();
     * -------------------------------------
     * Returns the first value in the set in the order established by the
     * <code>for</code> loop.  If the set is empty, <code>first</code>
     * generates an error.
     */

    ValueType first() const;

    /*
     * Method: toString
     * Usage: string str = set.toString();
     * -----------------------------------
     * Converts the set to a printable string representation.
     */

    std::string toString();

    /*
     * Method: mapAll
     * Usage: set.mapAll(fn);
     * ----------------------
     * Iterates through the elements of the set and calls <code>fn(value)</code>
     * for each one.  The values are processed in ascending order, as defined
     * by the comparison function.
     */

    void mapAll(void (*fn)(ValueType)) const;
    void mapAll(void (*fn)(const ValueType&)) const;

    template <typename FunctorType>
    void mapAll(FunctorType fn) const;

    /*
     * Additional Set operations
     * -------------------------
     * In addition to the methods listed in this interface, the Set class
     * supports the following operations:
     *
     *   - Stream I/O using the << and >> operators
     *   - Deep copying for the copy constructor and assignment operator
     *   - Iteration using the range-based for statement and STL iterators
     *
     * The iteration forms process the Set in ascending order.
     */

    /* Private section */

    /**********************************************************************/
    /* Note: Everything below this point in the file is logically part    */
    /* of the implementation and should not be of interest to clients.    */
    /**********************************************************************/

private:
    Map<ValueType, bool> map; /* Map used to store the element     */
    bool removeFlag;          /* Flag to differentiate += and -=   */

public:
    /*
     * Hidden features
     * ---------------
     * The remainder of this file consists of the code required to
     * support the comma operator, deep copying, and iteration.
     * Including these methods in the public interface would make
     * that interface more difficult to understand for the average client.
     */

    /* Extended constructors */

    template <typename CompareType>
    explicit Set(CompareType cmp) : map(Map<ValueType, bool>(cmp)) {
        /* Empty */
    }

    Set& operator,(const ValueType& value) {
        if (this->removeFlag) {
            this->remove(value);
        } else {
            this->add(value);
        }
        return *this;
    }

    /*
     * Iterator support
     * ----------------
     * The classes in the StanfordCPPLib collection implement input
     * iterators so that they work symmetrically with respect to the
     * corresponding STL classes.
     */

    class iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = ValueType;
        using difference_type = std::ptrdiff_t;
        using pointer = ValueType*;
        using reference = ValueType&;

        iterator() {
            /* Empty */
        }

        iterator(typename Map<ValueType, bool>::iterator it) : mapit(it) {
            /* Empty */
        }

        iterator(const iterator& it) {
            mapit = it.mapit;
        }

        iterator& operator++() {
            ++mapit;
            return *this;
        }

        iterator operator++(int) {
            iterator copy(*this);
            operator++();
            return copy;
        }

        bool operator==(const iterator& rhs) {
            return mapit == rhs.mapit;
        }

        bool operator!=(const iterator& rhs) {
            return !(*this == rhs);
        }

        ValueType operator*() {
            return *mapit;
        }

        ValueType* operator->() {
            return mapit;
        }

    private:
        typename Map<ValueType, bool>::iterator mapit; /* Iterator for the map */
    };

    iterator begin() const {
        return iterator(map.begin());
    }

    iterator end() const {
        return iterator(map.end());
    }
};

extern void error(std::string msg);

template <typename ValueType>
Set<ValueType>::Set() {
    /* Empty */
}

template <typename ValueType>
Set<ValueType>::Set(std::initializer_list<ValueType> list) {
    for (const ValueType& value : list) {
        this->add(value);
    }
}

template <typename ValueType>
Set<ValueType>::~Set() {
    /* Empty */
}

template <typename ValueType>
int Set<ValueType>::size() const {
    return map.size();
}

template <typename ValueType>
bool Set<ValueType>::isEmpty() const {
    return map.isEmpty();
}

template <typename ValueType>
void Set<ValueType>::add(const ValueType& value) {
    map.put(value, true);
}

template <typename ValueType>
void Set<ValueType>::insert(const ValueType& value) {
    map.put(value, true);
}

template <typename ValueType>
void Set<ValueType>::remove(const ValueType& value) {
    map.remove(value);
}

template <typename ValueType>
bool Set<ValueType>::contains(const ValueType& value) const {
    return map.containsKey(value);
}

template <typename ValueType>
void Set<ValueType>::clear() {
    map.clear();
}

template <typename ValueType>
bool Set<ValueType>::isSubsetOf(const Set& set2) const {
    iterator it = begin();
    iterator end = this->end();
    while (it != end) {
        if (!set2.map.containsKey(*it))
            return false;
        ++it;
    }
    return true;
}

/*
 * Implementation notes: set operators
 * -----------------------------------
 * The implementations for the set operators use iteration to walk
 * over the elements in one or both sets.
 */

template <typename ValueType>
bool Set<ValueType>::operator==(const Set& set2) const {
    if (size() != set2.map.size())
        return false;
    iterator it1 = begin();
    iterator it2 = set2.map.begin();
    iterator end = this->end();
    while (it1 != end) {
        if (map.compareKeys(*it1, *it2) != 0)
            return false;
        ++it1;
        ++it2;
    }
    return true;
}

template <typename ValueType>
bool Set<ValueType>::operator!=(const Set& set2) const {
    return !(*this == set2);
}

template <typename ValueType>
bool Set<ValueType>::operator<(const Set& set2) const {
    return compare::compare(*this, set2) < 0;
}

template <typename ValueType>
bool Set<ValueType>::operator<=(const Set& set2) const {
    return compare::compare(*this, set2) <= 0;
}

template <typename ValueType>
bool Set<ValueType>::operator>(const Set& set2) const {
    return compare::compare(*this, set2) > 0;
}

template <typename ValueType>
bool Set<ValueType>::operator>=(const Set& set2) const {
    return compare::compare(*this, set2) >= 0;
}

template <typename ValueType>
Set<ValueType> Set<ValueType>::operator+(const Set& set2) const {
    Set<ValueType> set = *this;
    for (const ValueType& value : set2) {
        set.add(value);
    }
    return set;
}

template <typename ValueType>
Set<ValueType> Set<ValueType>::operator+(const ValueType& element) const {
    Set<ValueType> set = *this;
    set.add(element);
    return set;
}

template <typename ValueType>
Set<ValueType> Set<ValueType>::operator*(const Set& set2) const {
    Set<ValueType> set = *this;
    set.clear();
    for (const ValueType& value : *this) {
        if (set2.contains(value))
            set.add(value);
    }
    return set;
}

template <typename ValueType>
Set<ValueType> Set<ValueType>::operator-(const Set& set2) const {
    Set<ValueType> set = *this;
    for (const ValueType& value : set2) {
        set.remove(value);
    }
    return set;
}

template <typename ValueType>
Set<ValueType> Set<ValueType>::operator-(const ValueType& element) const {
    Set<ValueType> set = *this;
    set.remove(element);
    return set;
}

template <typename ValueType>
Set<ValueType>& Set<ValueType>::operator+=(const Set& set2) {
    for (const ValueType& value : set2) {
        this->add(value);
    }
    return *this;
}

template <typename ValueType>
Set<ValueType>& Set<ValueType>::operator+=(const ValueType& value) {
    this->add(value);
    this->removeFlag = false;
    return *this;
}

template <typename ValueType>
Set<ValueType>& Set<ValueType>::operator*=(const Set& set2) {
    Vector<ValueType> toRemove;
    for (const ValueType& value : *this) {
        if (!set2.map.containsKey(value))
            toRemove.add(value);
    }
    for (const ValueType& value : toRemove) {
        this->remove(value);
    }
    return *this;
}

template <typename ValueType>
Set<ValueType>& Set<ValueType>::operator-=(const Set& set2) {
    Vector<ValueType> toRemove;
    for (const ValueType& value : *this) {
        if (set2.map.containsKey(value))
            toRemove.add(value);
    }
    for (const ValueType& value : toRemove) {
        this->remove(value);
    }
    return *this;
}

template <typename ValueType>
Set<ValueType>& Set<ValueType>::operator-=(const ValueType& value) {
    this->remove(value);
    this->removeFlag = true;
    return *this;
}

template <typename ValueType>
ValueType Set<ValueType>::first() const {
    if (isEmpty())
        error("first: set is empty");
    return *begin();
}

template <typename ValueType>
std::string Set<ValueType>::toString() {
    std::ostringstream os;
    os << *this;
    return os.str();
}

template <typename ValueType>
void Set<ValueType>::mapAll(void (*fn)(ValueType)) const {
    map.mapAll(fn);
}

template <typename ValueType>
void Set<ValueType>::mapAll(void (*fn)(const ValueType&)) const {
    map.mapAll(fn);
}

template <typename ValueType>
template <typename FunctorType>
void Set<ValueType>::mapAll(FunctorType fn) const {
    map.mapAll(fn);
}

template <typename ValueType>
std::ostream& operator<<(std::ostream& os, const Set<ValueType>& set) {
    os << "{";
    bool started = false;
    for (const ValueType& value : set) {
        if (started)
            os << ", ";
        writeGenericValue(os, value, true);
        started = true;
    }
    os << "}";
    return os;
}

template <typename ValueType>
std::istream& operator>>(std::istream& is, Set<ValueType>& set) {
    char ch;
    is >> ch;
    if (ch != '{')
        error("operator >>: Missing {");
    set.clear();
    is >> ch;
    if (ch != '}') {
        is.unget();
        while (true) {
            ValueType value;
            readGenericValue(is, value);
            set += value;
            is >> ch;
            if (ch == '}')
                break;
            if (ch != ',') {
                error(std::string("operator >>: Unexpected character ") + ch);
            }
        }
    }
    return is;
}

#endif
