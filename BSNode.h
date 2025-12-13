#ifndef BSNode_H
#define BSNode_H

#include <ostream>

template <typename T>
class BSNode
{
	public:
		T elem;
		BSNode<T>* left;
		BSNode<T>* right;
		BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr)
		{
			this->elem = elem;
			this->left = left;
			this->right = right;
		}
		
		template <class V>
			friend std::ostream& operator<<(std::ostream &out, const BSNode<V> &bsn);
};

template <typename T>
std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn)
{
	out << bsn.elem;
	return out;
}

#endif // BSNode_H
