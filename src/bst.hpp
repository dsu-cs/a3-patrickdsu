#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include "node.hpp"

template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T new_data);
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T val);
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void);
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void);
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void);
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T> *search(T val);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);
private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;
    // Helps insert data into the tree
    Node<T>* insert_helper(T &new_data, Node<T> *tree );
    // Helps search for data in the tree
    Node<T>* search_helper(T &val, Node<T> *tree );
    // Helps inorder
    void inorder_helper(Node<T> *tree, std::vector<T> *vec);
    // Helps preorder
    void preorder_helper(Node<T> *tree, std::vector<T> *vec);
    // Helps postorder
    void postorder_helper(Node<T> *tree, std::vector<T> *vec);
    // Helps remove
    Node<T>* remove_helper(T &val, Node<T> *tree);
    // Finds min node in tree and returns, used in remove
    Node<T>* find_min(Node<T> *tree);
    // Helps get_size;
    int get_size_helper(Node<T> *tree, T size);
};

template<class T>
BST<T>::BST()
{
    	root = NULL;
    	node_count = 0;
}

template<class T>
BST<T>::~BST()
{
	root = NULL;
	
	while(root != NULL)
	{
        	remove(root->get_data());
    	}
}

template<class T>
 std::vector<T> * BST<T>::inorder()
{
		std::vector<T> *vec = new std::vector<T>;   
		inorder_helper(root, vec);
		
	return vec;
}

template<class T>
void BST<T>::inorder_helper(Node<T> *tree, std::vector<T> *vec)
{

	
	if (tree == NULL)	return;
	//std::cout<<"l\n";	
	inorder_helper(tree->get_left(), vec);
	vec->push_back(tree->get_data());	
	//std::cout<<"r\n";	
	inorder_helper(tree->get_right(), vec);
	
	
}



template<class T>
 std::vector<T> * BST<T>::preorder()
{
    	std::vector<T> *vec = new std::vector<T>;
    	preorder_helper(root, vec);
    	return vec;
}


template<class T>
void BST<T>::preorder_helper(Node<T> *tree, std::vector<T> *vec)
{
	if(tree == NULL)	return;
	vec->push_back(tree->get_data());
	preorder_helper(tree->get_left(), vec);
	preorder_helper(tree->get_right(), vec);


}

template<class T>
 std::vector<T> * BST<T>::postorder()
{
    	std::vector<T> *vec = new std::vector<T>;
	postorder_helper(root, vec);
    	return vec;
}

template<class T>
void BST<T>::postorder_helper(Node<T> *tree, std::vector<T> *vec)
{

	if(tree == NULL)	return;
	postorder_helper(tree->get_left(), vec);
	postorder_helper(tree->get_right(), vec);
	vec->push_back(tree->get_data());

}

template<class T>
void BST<T>::insert(T new_data)
{	
	//if (root != NULL)	
	//std::cout << root->get_data() << "\n\n";	
	root = insert_helper(new_data, root);
}


template<class T>
Node<T> *BST<T>::insert_helper(T &new_data, Node<T> *tree)
{
	if (tree == NULL)
	{
		//std::cout << "Set\n";			
		Node<T> *tmp = new Node<T>(new_data);
		return tmp;
	}
	
	if (new_data == tree->get_data())
	{
		
		std::cout <<"Item was already in tree\n";
		return tree;
	}
	
	if (new_data < tree->get_data())
	{		
		//std::cout << "left\n";		
		tree->set_left(insert_helper(new_data, tree->get_left()));
	
	}

	else
	{

		//std::cout << "right\n";
		tree->set_right(insert_helper(new_data, tree->get_right()));
		
	}
	
	return tree;

}

template<class T>
Node<T> *BST<T>::search(T val)
{

	Node<T> *tmp = root;
	//std::cout << val << "\n";	
	tmp = search_helper(val, tmp);
	return tmp;

}

template<class T>
Node<T> *BST<T>::search_helper(T &val, Node<T> *tree)

{
	if (tree == NULL)

	{
		return NULL;
	}
	
	if (val == tree->get_data())

	{
		return tree;
	}

	if (val < tree->get_data())

	{
		//std::cout << "left\n";
		search_helper(val, tree->get_left());
	}

	else 

	{
		//std::cout << "right\n";
		search_helper(val, tree->get_right());
	}

}

template<class T>
void BST<T>::remove(T val)
{

	root = remove_helper(val, root);
	
	
}

template<class T>
Node<T> *BST<T>::remove_helper(T &val, Node<T> *tree)
{	
		
		
	if (tree == NULL)	return tree;

	else if (val < tree->get_data())
		
		tree->set_left(remove_helper(val, tree->get_left()));

	else if (val > tree->get_data())

		tree->set_right(remove_helper(val, tree->get_right()));

	
	
	else
	{
	 
		if (tree->get_left() == NULL && tree->get_right() == NULL)
		{
	
			delete tree;
			tree = NULL;
		}
	
		else if (tree->get_left() == NULL)
		{
		
			Node<T> *tmp = tree;
			tree = tree->get_right();
			delete tmp;
	
		}
	
		else if (tree->get_right() == NULL)
		{			
			Node<T> *tmp = tree;
			tree = tree->get_left();
			delete tmp;
		}
	
		else 
		{
			Node<T> *tmp = find_min(tree->get_right());			
			T setval = tmp->get_data();
			tree->set_data(setval);
			tree->set_right(remove_helper(setval, tree->get_right()));
		}	
	}

	
	return tree;

}

template<class T>
Node<T> *BST<T>::find_min(Node<T> *tree)
{
		
	if (tree->get_left() == NULL)	
	return tree;
	
	else	
	find_min(tree->get_left());
}

template<class T>
int BST<T>::get_size()
{
	get_size_helper(root, 1);
}

template<class T>
int BST<T>::get_size_helper(Node<T> *tree, T size)
{

	
	if(tree == NULL)	return 0;
	
	if(tree->get_left() != NULL)
	{
		size = size + 1;
		size = get_size_helper(tree->get_left(), size);
	}

	if(tree->get_right() != NULL)
	{
		size = size + 1;
		size = get_size_helper(tree->get_right(), size);
	}
	
	return size;	


}
