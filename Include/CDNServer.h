#ifndef CDNSERVER_H
#define CDNSERVER_H

#include <string>
#include <unordered_set>

// CDNServer class manages a set of strings and provides functionality to check the presence of items
class CDNServer {
public:
    // Constructor initializes the server with a usage count of zero
    CDNServer() : usage_count(0) {}

    // Adds a word to the server's internal storage
    void addWord(const std::string& word) {
        words.insert(word);  // Insert the word into the unordered set
    }

    // Checks if a word exists in the server's storage and increments the usage count
    bool checkWord(const std::string& word) {
        ++usage_count;  // Increment usage count with each check
        return words.find(word) != words.end();  // Return true if the word is found
    }

    // Returns the number of times the server has been queried
    size_t getUsageCount() const {
        return usage_count;  // Provide the total usage count
    }

    // Estimates the memory usage of the server's data in kilobytes
    double RAMUsage() const {
        size_t total_memory = 0;
        for (const auto& word : words) {
            // Calculate memory used by each string including its storage overhead
            total_memory += sizeof(std::string) + word.capacity() * sizeof(char);
        }
        // Add the memory used by the unordered_set's internal structures
        total_memory += words.bucket_count() * sizeof(void*);
        return static_cast<double>(total_memory) / 1024.0;  // Convert bytes to kilobytes
    }

private:
    std::unordered_set<std::string> words;  // Container to store unique words
    size_t usage_count;                     // Counter for the number of queries made to the server
};

#endif // CDNSERVER_H
