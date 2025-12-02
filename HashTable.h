#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdexcept>
#include <string>
#include <ostream>
#include "Dict.h"  
#include "TableEntry.h"
#include "../PRA_2425_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
private:

    int n;         
    int max;       
    ListLinked<TableEntry<V>>** table; 
    int h(std::string key)
    {
        long sum = 0;
        for (char c : key)
       	{
            sum += (int)c;
        }
        return (int)(sum % max);
    }

public:
 
    HashTable(int size) : n(0), max(size)
    {
        if (size <= 0)
       	{
            throw std::runtime_error("El tamaño de la tabla debe ser > 0");
        }
        table = new ListLinked<TableEntry<V>>*[max];
        for (int i = 0; i < max; ++i)
       	{
            table[i] = new ListLinked<TableEntry<V>>();
        }
    }

    virtual ~HashTable()
    {
        for (int i = 0; i < max; ++i) 
	{
            delete table[i];
        }
        delete[] table; 
    }

    virtual int entries() override
    {
        return n;
    }

    virtual void insert(std::string key, V value) override
    {
        int bucketIdx = h(key);
        TableEntry<V> entry(key, value);

        if (table[bucketIdx]->search(entry) != -1) 
	{
            throw std::runtime_error("Key '" + key + "' already exists!");
        }

        table[bucketIdx]->prepend(entry);
        n++;
    }

    virtual V search(std::string key) override 
    {
        int bucketIdx = h(key);
        TableEntry<V> entry(key); 

        int pos = table[bucketIdx]->search(entry);
        if (pos == -1)
       	{
            throw std::runtime_error("Key '" + key + "' not found!");
        }
        return table[bucketIdx]->get(pos).value;
    }

    virtual V remove(std::string key) override
    {
        int bucketIdx = h(key);
        TableEntry<V> entry(key);

        int pos = table[bucketIdx]->search(entry);
        if (pos == -1)
       	{
            throw std::runtime_error("Key '" + key + "' not found!");
        }

        TableEntry<V> removedEntry = table[bucketIdx]->remove(pos);
        n--;

        return removedEntry.value;
    }
    
    int capacity()
    {
        return max;
    }

    V operator[](std::string key)
    {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) 
    {
        out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
        out << "==============";
        for (int i = 0; i < th.max; ++i)
       	{
            out << "\n\n== Cubeta " << i << " ==" << std::endl;
            out << "List => " << *th.table[i];
        }
        out << "\n\n==============";
        return out;
    }
};

#endif
