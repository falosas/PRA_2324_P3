#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <string>
#include <stdexcept>
#include "dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> 
{
	private:
		BSTree<TableEntry<V>>* tree;
	
	public:
		BSTreeDict() {tree = new BSTree<TableEntry<V>>();}
		~BSTreeDict() {delete tree;}
		int entries() override {return tree->size();}
		void insert(std::string key, V value) override
	       	{
			TableEntry<V> entry(key, value);
			tree->insert(entry);
		}
		
		V search(std::string key) override
	       	{
			TableEntry<V> query(key);
			return tree->search(query).value;
		}
		
		V remove(std::string key) override
	       	{
		     TableEntry<V> query(key);
		     V val = tree->search(query).value;
		     tree->remove(query);
		     return val;
		}
		
		V operator[](std::string key) {return search(key);}
		friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs)
	       	{
			out << *bs.tree;
			return out;
		}
};

#endif
