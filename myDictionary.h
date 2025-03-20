#ifndef P2_MYDICTIONARY_H
#define P2_MYDICTIONARY_H

#include "position.h"
#include <unordered_map>

using namespace std;

/**
 * @class MyDictionary
 * @brief A simple dictionary implementation using an unordered_map.
 *
 * This class stores key-value pairs where the key is a string and the value
 * is a pointer to a Position object. It provides basic dictionary operations
 * like insertion, deletion, lookup, and size checking.
 */
class MyDictionary {

public:

    /**
     * @brief Default constructor.
     *
     * Initializes an empty dictionary.
     */
    MyDictionary() = default;

    /**
     * @brief Inserts a key-value pair into the dictionary.
     *
     * @param key The key (string) to insert.
     * @param value A pointer to the Position object associated with the key.
     */
    void insert(const string& key, Position* value) {
        map.insert({key, value});
    }

    /**
     * @brief Checks if a key is unique (i.e., not present in the dictionary).
     *
     * @param key The key to check.
     * @return True if the key does not exist in the dictionary, false otherwise.
     */
    bool isUnique(const string& key) {
        if (map.find(key) == map.end()) {
            return true;
        }
        return false;
    }

    /**
     * @brief Removes a key-value pair from the dictionary.
     *
     * @param key The key to remove.
     */
    void remove(const string& key) {
        map.erase(key);
    }

    /**
     * @brief Overloaded subscript operator for accessing dictionary values.
     *
     * @param key The key whose associated value is to be accessed.
     * @return A pointer to the Position object corresponding to the key.
     *         If the key does not exist, a new entry is created with a default-initialized Position*.
     */
    Position* operator[](const string& key) {
        return map[key];
    }

    /**
     * @brief Retrieves the number of key-value pairs in the dictionary.
     *
     * @return The number of elements in the dictionary.
     */
    size_t size() const {
        return map.size();
    }

    /**
     * @brief Checks if the dictionary is empty.
     *
     * @return True if the dictionary has no elements, false otherwise.
     */
    bool isEmpty() const {
        return map.empty();
    }

    /**
     * @brief Clears all elements from the dictionary.
     */
    void clear() {
        map.clear();
    }

protected:
    /**
     * @brief Internal unordered map storing key-value pairs.
     *
     * The key is a string, and the value is a pointer to a Position object.
     */
    unordered_map<string, Position*> map;

};

#endif // P2_MYDICTIONARY_H
