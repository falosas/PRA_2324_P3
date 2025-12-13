#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree 
{
	private:
		int nelem;          
		BSNode<T>* root;
		BSNode<T>* search(BSNode<T>* n, T e) const
	       	{
			if (n == nullptr) {return nullptr;}
			if (e < n->elem) {return search(n->left, e);}
		       	else if (e > n->elem) {return search(n->right, e);}
		       	else {return n;}
		}
		
		BSNode<T>* insert(BSNode<T>* n, T e)
	       	{
			if (n == nullptr) 
			{
				nelem++;
				return new BSNode<T>(e);
			}
		
			if (e < n->elem) {n->left = insert(n->left, e);}
		       	else if (e > n->elem) {n->right = insert(n->right, e);}
		       	else {throw std::runtime_error("Elemento duplicado");}
			return n;
		}
		
		void print_inorder(std::ostream &out, BSNode<T>* n) const
	       	{
			if (n != nullptr)
		       	{
				print_inorder(out, n->left);
			       	out << n->elem << " ";
				print_inorder(out, n->right);
		       	}
		}

		T max(BSNode<T>* n) const
	       	{
			if (n == nullptr) {throw std::runtime_error("Árbol vacío en max()");}
			if (n->right == nullptr) {return n->elem;}
		       	return max(n->right);
		}
		
		BSNode<T>* remove_max(BSNode<T>* n)
	       	{
			if (n->right == nullptr)
		       	{
				BSNode<T>* leftChild = n->left;
			       	delete n;
				return leftChild;
			}
			n->right = remove_max(n->right);
			return n;
		}

		BSNode<T>* remove(BSNode<T>* n, T e)
	       	{
			if (n == nullptr)
		       	{
				throw std::runtime_error("Elemento no encontrado para eliminar");
			}
			
			if (e < n->elem) {n->left = remove(n->left, e);}
		       	else if (e > n->elem) {n->right = remove(n->right, e);}
		       	else 
			{
				nelem--;
				if (n->left != nullptr && n->right != nullptr) 
				{
					T maxLeft = max(n->left);
					n->elem = maxLeft;
					n->left = remove_max(n->left);
				}
				
				else if (n->left != nullptr) 
				{
					BSNode<T>* temp = n->left;
					delete n;
					return temp;
				}
				
				else
			       	{
					BSNode<T>* temp = n->right;
					delete n;
					return temp;
				}
			}

			return n;
		}
		
		void delete_cascade(BSNode<T>* n)
	       	{
			if (n != nullptr)
		       	{
				delete_cascade(n->left);
				delete_cascade(n->right);
				delete n;
			}
		}
	
	public:
		BSTree() : nelem(0), root(nullptr) {}
		int size() const {return nelem;}
		T search(T e) const 
		{
			BSNode<T>* found = search(root, e);
			if (found == nullptr)
		       	{
				throw std::runtime_error("Elemento no encontrado");
			}
			return found->elem;
		}

		T operator [](T e) const {return search(e);}
		void insert(T e) {root = insert(root, e);}
		void remove(T e) {root = remove(root, e);}
		~BSTree() {delete_cascade(root);}
		
		template <class U>
			friend std::ostream& operator<<(std::ostream &out, const BSTree<U> &bst);
};

template <typename T>
std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst)
{
	bst.print_inorder(out, bst.root);
	return out;
}

#endif
