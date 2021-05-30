//
// Created by Yoav Gochman, id 205530983 on 14/01/2020.
//

#ifndef EX3_HASHMAP_HPP
#define EX3_HASHMAP_HPP

#include <iostream>
#include <vector>
#include<list>
#include <utility>

#define UPPER_THRESHOLD 0.75
#define LOWER_THRESHOLD 0.25

using namespace std;

template<typename keyT, typename valueT>

/**
 * @brief This class represents a HashMap container
 * @tparam keyT template key
 * @tparam valueT template value
 */
class HashMap
{
private:
    list <pair<keyT, valueT>> *_table;
    int _size = 0;
    int _capacity = 16;

    /**
     * @brief Helper function to calc hash index of a key
     * @param key a key to calc
     * @return an index in range (0---capacity()-1)
     */
    int _hash_func(keyT key) const
    {
        hash<keyT> hash_functor;
        int x = hash_functor(key);

        return (x & (_capacity - 1));

    }

    /**
     * @brief helper function to get the next the next non empty bucket
     * @param curBucketIndex - a bucket to start from
     * @return the next bucket index that is not empty. 0 if didn't find.
     */
    int _getNextNonEmptyBucket(int curBucketIndex) const
    {
        if (curBucketIndex == (_capacity -1)){
            return 0;
        }

        for (int i = curBucketIndex + 1; i < _capacity; i++)
        {
            if (_table[i].size() > 0)
            {
                return i;
            }
        }

        return 0;
    }

public:
    /**
     * @brief Basic constructor
     */
    HashMap() :
            _size(0), _capacity(16), _table(new list<pair<keyT, valueT> >[16])
    {
    }

    /**
     * @brief 2 vectors constructor (builds respectively)
     * @param typeVec vector of keys
     * @param valueVec vector of values
     */
    HashMap(vector<keyT> typeVec, vector<valueT> valueVec) :
            _table(new list<pair<keyT, valueT> >[16])
    {
        if (typeVec.size() != valueVec.size())
        {
            delete[] _table;
            throw (bad_exception());
        }

        _size = 0;
        _capacity = 16;

        for (int i = 0; i < typeVec.capacity(); i++)
        {
            (*this)[typeVec[i]] = valueVec[i];
        }
    }

    /**
     * @brief copy constructor (deep copy)
     * @param other another map
     */
    HashMap(HashMap const &other)
            : _table(new list<pair<keyT, valueT> >[other.capacity()])
    {
        _size = 0;
        _capacity = other.capacity();

        for (int i = 0; i < other.capacity(); i++)
        {

            auto iterator = other._table[i].begin();
            for (iterator; iterator != other._table[i].end(); ++iterator)
            {
                insert((*iterator).first, (*iterator).second);
            }
        }

    }


    /**
     * @brief Destructor
     */
    ~HashMap()
    {
        delete[] _table;
    }

    /**
     * @brief returns size
     * @return size of map
     */
    int size() const
    {
        return _size;
    }

    /**
     * @brief returns Capacity of map
     * @return capacity of the map
     */
    int capacity() const
    {
        return _capacity;
    }

    /**
     * @brief returns true if map is empty
     * @return true if map is empty (size is 0)
     */
    bool empty() const
    {
        return (_size == 0);
    }

    /**
     * @brief Calculate load factor (size/capacity)
     * @return double representing the loadFactor
     */
    double getLoadFactor() const
    {
        return (double) _size / (double) _capacity;
    }

    /**
     * @brief insert key,value to the map
     * @param k key
     * @param v value
     * @return true if succeeded, else if already exist
     */
    bool insert(const keyT &k, const valueT &v)
    {
        if (containsKey(k))
        {
            return false;
        }


        int index = _hash_func(k);
        _table[index].push_back(make_pair(k, v));
        _size++;


        if (getLoadFactor() > UPPER_THRESHOLD)
        {
            re_hash_table_increase();
        }

        return true;

    }

    /**
     * @brief Helper func to increase table in rehashing
     */
    void re_hash_table_increase()
    {
        vector<keyT> keysVec;
        vector<valueT> valuesVec;

        for (auto const &pair: *this)
        {
            keysVec.push_back(pair.first);
            valuesVec.push_back(pair.second);
        }

        // auto temp = new HashMap<keyT, valueT>(keysVec,valuesVec); // This is full copy using copy
        // constructor

        clear(); // sets size to 0 and clears all the elements.
        _capacity = _capacity * 2; // size stays the same

        delete[] (_table);
        _table = new list <pair<keyT, valueT>>[capacity() * 2];

        for (int i = 0; i < keysVec.size(); i++)
        {
            insert(keysVec[i], valuesVec[i]);
        }

    }

    /**
     * @brief check if a key is in the map
     * @param keyToCheck a key to check
     * @return true if exists in the mao
     */
    bool containsKey(keyT keyToCheck) const
    {
        int index = _hash_func(keyToCheck);
        auto &current_bucket = _table[index];
        for (auto &p : current_bucket)
        {
            if (p.first == keyToCheck)
            {
                return true;
            }
        }

        return false;
    }

    /**
     * @brief const version, returns the respective value for the given key. throws exception if
     * not exist
     * @param keyToCheck a key to search
     * @return respective value
     */
    valueT &at(keyT keyToCheck) const
    {

        if (!containsKey(keyToCheck))
        {
            throw (bad_exception());
        }

        int index = bucketIndex(keyToCheck);
        auto &current_bucket = _table[index];
        for (auto &p : current_bucket)
        {
            if (p.first == keyToCheck)
            {
                return p.second;
            }
        }


    }

    /**
     * @brief erase a key from map
     * @param keyToErase a key to erase
     * @return true if deleted succesfuly.
     */
    bool erase(keyT keyToErase)
    {
        if (!containsKey(keyToErase))
        {
            return false;
        }

        int index = bucketIndex(keyToErase);
        auto &current_bucket = _table[index];

        typename list<pair<keyT, valueT>>::iterator it;
        for (it = current_bucket.begin(); it != current_bucket.end(); ++it)
        {
            if ((*it).first == keyToErase)
            {
                current_bucket.erase(it);
                _size--;
                break;
            }
        }


        if (getLoadFactor() < LOWER_THRESHOLD)
        {
            re_hash_table_decrease();
        }

        return true;
    }


    /**
     * @brief helper function to decrease table in re-hash
     */
    void re_hash_table_decrease()
    {

        auto temp = new HashMap<keyT, valueT>(*this); // This is full copy using copy
        // constructor

        _capacity = _capacity / 2; // size stays the same

        clear(); // sets size to 0 and clears all the elements.

        for (auto &pair : (*temp))
        {
            insert(pair.first, pair.second);
        }

        delete temp;

    }

    /**
     * @brief gets a key an returns it's bucket size.
     * @param keyToCheck a key to check
     * @return integer of the bucket size
     */
    int bucketSize(keyT keyToCheck) const
    {
        if (!containsKey(keyToCheck))
        {
            throw (bad_exception());
        }

        int index = bucketIndex(keyToCheck);
        auto &current_bucket = _table[index];
        return current_bucket.size();

    }

    /**
     * @brief gets a key and returns its bucket index
     * @param keyToCheck a key to check
     * @return the index of its bucket
     */
    int bucketIndex(keyT keyToCheck) const
    {
        if (!containsKey(keyToCheck))
        {
            throw (bad_exception());
        }

        int index = _hash_func(keyToCheck);
        return index;

    }

    /**
     * @brief clears table (capacity stays the same)
     */
    void clear()
    {

        for (int i = 0; i < _capacity; i++)
        {
            _table[i].clear();
        }

        _size = 0; // capacity stays the same

    }

    /**
     * @brief assignment operator
     * @param other a map to assign
     * @return a ref to (*this)
     */
    HashMap &operator=(const HashMap &other)
    {
        if ((*this) == other)
        {
            return *this;
        }


        clear();
        _capacity = other.capacity();

        delete[] (_table);
        _table = new list<pair<keyT, valueT> >[other.capacity()];

        for (int i = 0; i < other._capacity; i++)
        {
            for (auto const &p : other._table[i])
            {
                insert(p.first, p.second);
            }
        }

        return *this;


    }

    /**
     * @brief operator[] const version
     * @param keyToCheck a key to search
     * @return returns respective value (undifined behavior when non exist)
     */
    valueT operator[](const keyT keyToCheck) const
    {

        int index = bucketIndex(keyToCheck);
        auto &current_bucket = _table[index];
        for (auto const &p : current_bucket)
        {
            if (p.first == keyToCheck)
            {
                return p.second;
            }
        }

    }

    /**
     *
     * @brief operator[] non-const (for assigment or value changing)
     * @param keyToEnter a key to search
     * @return respective value reference.
     */
    valueT &operator[](keyT keyToEnter)
    {
        if (!containsKey(keyToEnter))
        {
            valueT valueToEnter = {};   // default value
            insert(keyToEnter, valueToEnter);
        }

        valueT &refValue = (*this).at(keyToEnter);

        // return a ref so caller can change it.
        // MyHashMap["Yoav"] = 6;

        return refValue;


    }

    /**
     * @brief operator== for comparing
     * @param other
     * @return true if maps are the same
     */
    bool operator==(HashMap<keyT, valueT> other) const
    {

        if ((*this).size() != other.size())
        {
            return false;
        }



        // assuming both HashMaps has same size.
        for (auto &p: *this)
        {
            keyT &curKey = p.first;
            if (!other.containsKey(curKey))
            {
                return false;
            }
            else // key in the other map
            {
                // check same value
                if ((*this).at(curKey) != other.at(curKey))
                {
                    return false;
                }
            }
        }


        return true;

    }

    /**
     * @brief operator !=
     * @param other another map
     * @return true if maps are not equal
     */
    bool operator!=(HashMap<keyT, valueT> other) const
    {
        return (!(*this == other));
    }

    /**
     * @brief Nested class - iterator for HashMap
     */
    class const_iterator
    {
    public:
        typedef const_iterator self_type;
        typedef pair<keyT, valueT> value_type;
        typedef pair<keyT, valueT> &reference;
        typedef pair<keyT, valueT> *pointer;
        typedef int difference_type;
        typedef std::forward_iterator_tag iterator_category;

        /**
         * @brief constructor
         * @param lst_it an iterator of stl list
         * @param map a HashMap reference
         */
        explicit const_iterator(const typename list<value_type>::iterator &lst_it, const HashMap
        &map) :
                lst_iterator_(lst_it),
                map_(map)
        {
        }

        /**
         * @brief iterator ++ method. ++it version.
         * @return self_type
         */
        self_type operator++()          // ++it
        {
            // Get Current Bucket reference
            keyT cur_key = (*lst_iterator_).first;
            int index = map_.bucketIndex(cur_key);
            list <value_type> &curBucket = map_._table[index];

            // create iterator for the inner list starting from ptr_
            typename list<value_type>::iterator bucket_it = lst_iterator_;
            // increase bucket iterator and set ptr to new value
            ++bucket_it;
            lst_iterator_ = bucket_it;
            // case we reached end.
            if (bucket_it == curBucket.end())
            {
                int nextNonEmptyBucketIndex = map_._getNextNonEmptyBucket(index);
                if (nextNonEmptyBucketIndex == 0)   // this was the last cell in the map
                {
                    lst_iterator_ = map_._table[map_.capacity() - 1].end();
                }
                else
                {
                    lst_iterator_ = map_._table[nextNonEmptyBucketIndex].begin();
                }
            }

            return *this;
        }

        /**
         * @brief iterator ++ method    // postfix it++
         * @return self_type
         */
        self_type operator++(int)     // postfix it++
        {
            self_type temp = *this;
            // Get Current Bucket reference
            keyT cur_key = (*lst_iterator_).first;
            int index = map_.bucketIndex(cur_key);
            list <value_type> &curBucket = map_._table[index];

            // create iterator for the inner list starting from ptr_
            typename list<value_type>::iterator bucket_it = lst_iterator_;
            // increase bucket iterator and set ptr to new value
            ++bucket_it;
            lst_iterator_ = bucket_it;
            // case we reached end.
            if (bucket_it == curBucket.end())
            {
                int nextNonEmptyBucketIndex = map_._getNextNonEmptyBucket(index);
                if (nextNonEmptyBucketIndex == 0)   // this was the last cell in the map
                {
                    lst_iterator_ = map_._table[map_.capacity() - 1].end();
                }
                else
                {
                    lst_iterator_ = map_._table[nextNonEmptyBucketIndex].begin();
                }
            }

            return temp;

        }

        /**
         * @brief operator de-reference of an iterator
         * @return pair<keyT, valueT> &
         */
        reference operator*()
        {
            return *lst_iterator_;
        }

        /**
         * @brief operator ->
         * @return pair<keyT, valueT> *
         */
        pointer operator->()
        {
            return &(*lst_iterator_);
        }

        /**
         * @brief operator==
         * @param other another iterator
         * @return true if they point on the same pair
         */
        bool operator==(const self_type &other) const
        {
            return lst_iterator_ == other.lst_iterator_;
        }

        /**
         * @brief operator !=
         * @param other another iterator
         * @return true if they don't point the same pair
         */
        bool operator!=(const self_type &other) const
        {
            return lst_iterator_ != other.lst_iterator_;
        }

    private:
        typename list<value_type>::iterator lst_iterator_;
        const HashMap &map_;
    };

    /**
     * @brief iterator start position
     * @return the begin position of an iterator
     */
    const_iterator cbegin() const
    {
        return const_iterator(_table[first_occupied_bucket()].begin(), *this);
    }

    /**
     * @brief iterator end position
     * @return the end position of an iterator
     */
    const_iterator cend() const
    {
        if (_size == 0)
        {
            return const_iterator(_table[0].end(), *this);
        }
        return const_iterator(_table[capacity() - 1].end(), *this);
    }

    /**
     * @brief iterator start position
     * @return the begin position of an iterator
     */
    const_iterator begin() const
    {

        return const_iterator(_table[first_occupied_bucket()].begin(),
                              *this);
    }

    /**
     * @brief iterator end position
     * @return the end position of an iterator
     */
    const_iterator end() const
    {

        if (_size == 0)
        {
            return const_iterator(_table[0].end(), *this);
        }
        return const_iterator(_table[capacity() - 1].end(), *this);
    }

    /**
     * @brief helper function that calculates the first occupied bucket
     * @return int representing the first occupied bucket
     */
    int first_occupied_bucket() const
    {
        for (int i = 0; i < capacity(); i++)
        {
            if (_table[i].size() > 0)
            {
                return i;
            }
        }

        return 0;
    }

    /**
     * @brief helper function that sets all the values to their default value.
     */
    void setValuesToDefault() const
    {
        for (auto &pair : (*this))
        {
            pair.second = {};
        }
    }


};


#endif //EX3_HASHMAP_HPP
