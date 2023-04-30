#ifndef __MYHASHTABLE_H__
#define __MYHASHTABLE_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <string>

#include "MyVector_j026f603.h"
#include "MyLinkedList_j026f603.h"

static const long long uh_param_a = 53;       // universal hash function parameter a
static const long long uh_param_b = 97;       // universal hash function parameter b
static const long long prime_digits = 19;     // parameter used for finding a Mersenne prime
static const long long mersenne_prime = (1 << prime_digits) - 1;  // the Mersenne prime for universal hashing

// fast calculation of (n modulo mersenne_prime)
long long fastMersenneModulo(const long long n)
{
    // code begins
    long long hv = n;
    hv = (hv >> prime_digits) + (hv & mersenne_prime);
    
    if (hv >= mersenne_prime) {
        hv = hv - mersenne_prime;
    }

    return hv;
    // code ends
}

// definition of the template hash function class
template <typename KeyType>
class HashFunc
{
  public:
    long long univHash(const KeyType key, const long long table_size) const;
};

// the hash function class that supports the hashing of the "long long" data type
template <>
class HashFunc<long long>
{
  public:
    long long univHash(const long long key, const long long table_size) const
    {
        long long hv = fastMersenneModulo(static_cast<long long>(uh_param_a * key + uh_param_b));
        hv = hv % table_size;
        return hv;
    }
};

// the has function class that supports the hashing of the "std::string" data type
template <>
class HashFunc<std::string>
{
  private:
    const int param_base = 37;      // the base used for inflating each character
  public:    
    long long univHash(const std::string& key, const long long table_size) const
    {
        long long hv = 0;
        for(size_t i = 0; i < key.length(); ++ i)
        {
            hv = param_base * hv + static_cast<long long>(key[i]);
        }
        hv = fastMersenneModulo(static_cast<long long>(uh_param_a * hv + uh_param_b));
        hv = hv % table_size;
        std::cout << "hv: " << hv << std::endl;
        return hv;
    }
};

// definition of the template hashed object class
template <typename KeyType, typename ValueType>
class HashedObj
{
  public:

    KeyType key;
    ValueType value;

    HashedObj()
    {
        return;
    }

    HashedObj(const KeyType& k, const ValueType& v) :
        key(k),
        value(v)
    {
        return;
    }
  
    HashedObj(KeyType && k, ValueType && v) :
        key(std::move(k)),
        value(std::move(v))
    {
        return;
    }

    bool operator==(const HashedObj<KeyType, ValueType>& rhs)
    {
        return (key == rhs.key);
    }    

    bool operator!=(const HashedObj<KeyType, ValueType>& rhs)
    {
        return !(*this == rhs);
    }   

};

template <typename KeyType, typename ValueType>
class MyHashTable
{ 
  private:
    size_t theSize; // the number of data elements stored in the hash table
    MyVector<MyLinkedList<HashedObj<KeyType, ValueType> >* > hash_table;    // the hash table implementing the separate chaining approach
    MyVector<size_t> primes;    // a set of precomputed and sorted prime numbers

    // pre-calculate a set of primes using the sieve of Eratosthenes algorithm
    // will be called if table doubling requires a larger prime number for table size
    // expected to update the private member "primes"
    void preCalPrimes(const size_t n)
    {
        // code begins
        MyVector<bool> temp;

        for (int i = 0; i <= n; i++) {
            temp.push_back(true);
        }

        for (int i = 2; i < sqrt(n); i++) {
            if (temp[i]) {
                for (int j = i * i; j <= n; j += i) {
                    temp[j] = false;
                }
            }
        }

        primes.resize(0);

        for (int i = 0; i < temp.size(); i++) {
            if (temp[i]) {
                primes.push_back(i);
            }
        }

        for (int i = 0; i < primes.size(); i++) {
            std::cout << primes[i] << std::endl;
        }
        // code ends
    }

    // finding the smallest prime that is larger than or equal to n
    // should perform binary search against the private member "primes"
    size_t nextPrime(const size_t n)
    {
        // code begins
        int i = 0;
        int j = primes.size() - 1;

        while (i != j) {
            int mid = (i + j) / 2;

            if (primes[mid] == n) {
                return primes[mid];
            }

            if (n > primes[mid]) {
                i = mid + 1;
            }

            if (n < primes[mid]) {
                j = mid;
            }
        }

        return primes[i];
        /*
        for (int i = 0; i < primes.size()/2; i++) {
            for (int j = primes.size() - 1; j > primes.size()/2; j--) {
                int mid = (i + j) / 2;

                if (mid == n) {
                    return mid;
                }

                if (n > mid) {
                    i = 
                }
            }
            //if (primes[i] >= n) {

            }
        }
        */
        // code ends
    }

    // finds the MyLinkedList itertor that corresponds to the hashed object that has the specified key
    // returns the end() iterator if not found
    typename MyLinkedList<HashedObj<KeyType, ValueType> >::iterator find(const KeyType& key)
    {
        // code begins
        HashFunc<std::string> f;
        auto & whichList = hash_table[f.univHash(key, capacity())];
        MyLinkedList<HashedObj<std::string, int> > *th = whichList;

        for (MyLinkedList<HashedObj<std::string, int> >::iterator i = whichList -> begin(); i != whichList -> end(); i++) {
            HashedObj<std::string, int> temp = *i;

            if (temp.key == key) {
                return i;
            }
        }

        return whichList -> end();
/*
        for (int i = 0; i < theSize; i++) {
            if (hash_table[i].key == key) {
                return i.begin();
            }
        }

        return 
*/
        // code ends
    }

    // rehashes all data elements in the hash table into a new hash table with new_size
    // note that the new_size can be either smaller or larger than the existing size
    void rehash(const size_t new_size)
    {
        // code begins
        MyVector<MyLinkedList<HashedObj<KeyType, ValueType> >* > temp;
/*
        for (int i = 0; i < 3; i++) {
            std::cout << hash_table[i] -> front().key << std::endl;
        }
*/
        int tempSize = theSize;

        for (int i = 0; i < capacity(); i++) {
            auto & whichList = hash_table[i];
            temp[i] = new MyLinkedList<HashedObj<std::string, int> >;

            for (int j = 0; j < whichList -> size();) {
                temp[i] -> push_back(hash_table[i] -> front());
                hash_table[i] -> pop_front();
            }
        }

        for (int i = 0; i < size(); i++) {
            std::cout << temp[i] -> front().key << std::endl;
        }
/*
        for (int i = 0; i < size(); i++) {
            std::cout << hash_table[i] -> front().key << std::endl;
        }
*/
/*
        for (int i = 0; i < capacity(); i++) {
            hash_table[i] -> clear();
        }
*/
/*
        for (int i = 0; i < 3; i++) {
            std::cout << temp[i] -> front().key << std::endl;
        }

        for (int i = 0; i < 3; i++) {
            std::cout << hash_table[i] -> front().key << std::endl;
        }
*/
        hash_table.resize(new_size);
        theSize = 0;

        for (int i = 0; i < capacity(); i++) {
            hash_table[i] = new MyLinkedList<HashedObj<std::string, int> >;
        }
/*
        for (auto thisList : temp) {
            for (auto x : *thisList) {
                insert(x);
            }
        }
*/
        for (int i = 0; i < tempSize; i++) {
            for (MyLinkedList<HashedObj<std::string, int> >::iterator j = temp[i] -> begin(); j != temp[i] -> end(); j++) {
                HashedObj<std::string, int> t = *j;
                std::cout << "key: " << t.key << std::endl;
                insert(t);
            }
        }

        // code ends
    }

    // doubles the size of the table and perform rehashing
    // the new table size should be the smallest prime that is larger than the expected new table size (double of the old size)
    void doubleTable()
    {
        size_t new_size = nextPrime(2 * hash_table.size());
        this->rehash(new_size);
        return;
    }

    // halves the size of the table and perform rehahsing
    // the new table size should be the smallest prime that is larger than the expected new table size (half of the old size)
    void halveTable()
    {
        size_t new_size = nextPrime(ceil(hash_table.size() / 2));
        this->rehash(new_size);
        return;
    }

  public:

    // the default constructor; allocate memory if necessary
    explicit MyHashTable(const size_t init_size = 3)
    {
        // code begins
        theSize = 0;
        hash_table.resize(init_size);
        preCalPrimes(500);

        for (int i = 0; i < capacity(); i++) {
            hash_table[i] = new MyLinkedList<HashedObj<std::string, int> >;
        }
        // code ends
    }

    // the default destructor; collect memory if necessary
    ~MyHashTable()
    {
        // code begins
        for (int i = 0; i < capacity(); i++) {
            delete hash_table[i];
        }
        // code ends
    }

    // checks if the hash tabel contains the given key
    bool contains(const KeyType& key)
    {
        // code begins
        HashFunc<long long> f;
        auto & whichList = hash_table[f.univHash(key, capacity())];
        return find(key) != whichList.end();
        // code ends
    }

    // retrieves the data element that has the specified key
    // returns true if the key is contained in the hash table
    // return false otherwise
    bool retrieve(const KeyType& key, HashedObj<KeyType, ValueType>& data)
    {
        // code begins
        HashFunc<std::string> f;
        auto & whichList = hash_table[f.univHash(key, capacity())];
        return find(key) != whichList -> end();
/*
        for (int i = whichList.begin(); i < whichList.end(); i++) {
            if ()
        }
*/
        // code ends
    }

    // inserts the given data element into the hash table (copy)
    // returns true if the key is not contained in the hash table
    // return false otherwise
    bool insert(const HashedObj<KeyType, ValueType>& x)
    {
        // code begins
        HashFunc<std::string> f;
        auto & whichList = hash_table[f.univHash(x.key, capacity())];

        if (find(x.key) != whichList -> end()) {
            return false;
        }

        whichList -> push_back(x);
        std::cout << "pushed: " << whichList -> back().key << std::endl;

        if (primes[primes.size() - 1] < capacity() * 2) {
            preCalPrimes(primes[primes.size() - 1] * 3);
        }

        theSize++;
        std::cout << "size: " << size() << std::endl;

//maybe move these if statements to the top of the function
        if ((theSize * 2) > capacity()) {
            std::cout << "size: " << size() << std::endl;
            doubleTable();
        }

        else if ((theSize * 8) < capacity()) {
            halveTable();
        }

        else if (theSize > capacity()) {
            rehash(nextPrime(theSize));
        }
        
        return true;
        // code ends
    }

    // inserts the given data element into the hash table (move)
    // returns true if the key is not contained in the hash table
    // return false otherwise
    bool insert(HashedObj<KeyType, ValueType> && x)
    {
        // code begins
        HashFunc<std::string> f;
        auto & whichList = hash_table[f.univHash(x.key, capacity())];

        if (find(x.key) != whichList -> end()) {
            return false;
        }

        whichList -> push_back(x);
        std::cout << "pushed" << std::endl;

        if (primes[primes.size() - 1] < capacity() * 2) {
            preCalPrimes(primes[primes.size() - 1] * 3);
        }

        theSize++;
        std::cout << "size: " << size() << std::endl;

        if ((theSize * 2) > capacity()) {
            std::cout << "size: " << size() << std::endl;
            doubleTable();
        }

        else if ((theSize * 8) < capacity()) {
            halveTable();
        }

        else if (theSize > capacity()) {
            rehash(nextPrime(theSize));
        }

        return true;
        // code ends
    }

    // removes the data element that has the key from the hash table
    // returns true if the key is contained in the hash table
    // returns false otherwise
    bool remove(const KeyType& key)
    {
        // code begins
        HashFunc<std::string> f;
        auto & whichList = hash_table[f.univHash(key, capacity())];
        auto itr = find(key);

        if (itr == whichList -> end()) {
            return false;
        }

        whichList -> erase(itr);
        theSize--;
        return true;
        // code ends
    }

    // returns the number of data elements stored in the hash table
    size_t size()
    {
        // code begins
        return theSize;
        // code ends
    }

    // returns the capacity of the hash table
    size_t capacity()
    {
        // code begins
        return hash_table.size();
        // code ends
    }

};


#endif // __MYHASHTABLE_H__
