#include<iostream>
#include<algorithm>
#include <sys/types.h>
#include"tree_table.hpp"



int main()
{
	AVL_node<int> x(50);
	AVL_node<int> *n = new AVL_node<int>(15);
	std::cout<< n->height << " " << n->weight << " " << n->value <<'\n';
	
	AVL_tree_array<int> y;
	std::cout<<y.Insert(25, 0);
	std::cout<<y.Insert(25, 0);
	std::cout<<y.Insert(25, 0);
	std::cout<<y.Insert(25, 0);
}
