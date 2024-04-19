#ifndef TRIE_H
#define TRIE_H

#include <array>
#include <string>
#include <initializer_list>
#include <functional>
#include <iostream>

class Trie {
public:
    class Node {
    public:
        Node(char data = '\0', bool is_finished = false);
        ~Node(); // To manage deletion of children nodes

        Node* parent; // Pointer to the parent node, parent of the root is "nullptr"
        std::array<Node*, 26> children; // Array of 26 Node pointers, covering English alphabet
        char data; // data for root node is "\0"
        bool is_finished;
    };

    // Constructors
    Trie();
    Trie(const Trie& other);
    Trie(Trie&& other);
    Trie(std::initializer_list<std::string> list);

    // Destructor
    ~Trie();

    // Assignment operators
    Trie& operator=(const Trie& other);
    Trie& operator=(Trie&& other);

    // Basic Trie operations
    void insert(const std::string& str);
    bool search(const std::string& query) const;
    bool startsWith(const std::string& prefix) const; // Check if there is any word in the trie that starts with the given prefix
    void remove(const std::string& str); // Remove a word from the Trie, consider removing the trace if needed.

    // Traversal and Utility
    void bfs(std::function<void(Node*&)> func); // Breadth-first over the node and calling "func" function over each of them
    void dfs(std::function<void(Node*&)> func); // (BONUS), Depth-first over the node and calling "func" function over each of them

    // I/O operators
    friend std::ostream& operator<<(std::ostream& os, const Trie& trie); // Output operator
    friend std::istream& operator>>(std::istream& is, Trie& trie); // Input operator

    // Additional Operators
    Trie operator+(const Trie& other) const; // Creates a new Trie containing all unique words from both operands
    Trie& operator+=(const Trie& other); // Adds all words from the right-hand operand into the left-hand Trie
    Trie operator-(const Trie& other) const; // Creates a new Trie containing words from the first Trie not in the second
    Trie& operator-=(const Trie& other); // Removes words from the left-hand Trie found in the right-hand Trie
    bool operator()(const std::string& query) const; // Can be used to check existence or perform other string operations
    bool operator==(const Trie& other) const; // Check if two Tries have exactly the same words
    bool operator!=(const Trie& other) const; // Check if two Tries differ in any word

private:
    Node* root;
};

#endif // TRIE_H