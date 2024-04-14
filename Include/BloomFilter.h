#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include <functional>  // Included for std::hash
#include <bitset>      // Included for std::bitset

#include "CDNServer.h" // Dependency for checking definitively if an item is in the dataset

// BloomFilter class template for probabilistic set membership checking
template <std::size_t N = 81920>  // Default size of the Bloom filter bit array set to 81920 bits (10 kilobytes)
class BloomFilter {
public:
    // Constructor initializing the number of hash functions
    BloomFilter(unsigned int num_hashes);

    // Copy constructor
    BloomFilter(const BloomFilter& other);

    // Move constructor with noexcept specifier for optimal performance
    BloomFilter(BloomFilter&& other) noexcept;

    // Destructor
    ~BloomFilter();

    // Add an item to the Bloom filter
    void add(const std::string& item);
    // Overload for adding items from a file, where words are assumed to be separated by ", "
    void add(std::string&& file_name="words_expect_true.txt");

    // Check if an item might be in the Bloom filter
    bool possiblyContains(const std::string& item) const;
    // Overload for r-value references, forwards to the l-value reference version
    bool possiblyContains(std::string&& item) const;

    // Definitive check for an item's presence combining Bloom filter and CDNServer
    bool certainlyContains(const std::string& item) const;
    // Overload for r-value strings
    bool certainlyContains(std::string&& item) const;

    // Reset the Bloom filter, clearing all set bits
    void reset();

    // Operator overloads for combining Bloom filters
    BloomFilter& operator&(const BloomFilter& other); // Intersection of two filters
    BloomFilter& operator|(const BloomFilter& other); // Union of two filters

    // Operator to check direct access, same as possiblyContains
    bool operator()(const std::string& item) const;

    // I/O operators for reading and writing Bloom filter states
    friend std::ostream& operator<<(std::ostream& os, const BloomFilter& bloom_filter); // Output stream operator
    friend std::istream& operator>>(std::istream& is, BloomFilter& bloom_filter); // Input stream operator

private:
    // Bit array to represent elements presence probabilistically
    std::bitset<N> bits;

    // Number of hash functions used in this filter
    std::size_t num_hashes;

    // Seeds for the hash functions to ensure diversity
    std::vector<std::size_t> seeds;

    // Pointer to a CDNServer used to definitively check items
    CDNServer* server;

    // Private method to hash an item using a specific seed
    std::size_t hash(const std::string& item, std::size_t seed) const {
        std::hash<std::string> hasher;
        return hasher(item + std::to_string(seed));  // Concatenate the seed to the item before hashing
    }
};

#endif // BLOOM_FILTER_H
