#include<iostream>
#include<algorithm>
#include <sys/types.h>



template<class value_t>
class AVL_node
{
public:
	AVL_node(value_t value): weight(1), height(1), value(value)
	{
		chd[0] = chd[1] = nullptr;
	}
	
	AVL_node *chd[2]; 
	uint64_t weight;
	uint32_t height;
	value_t value;
	
};

template<class value_t>
class AVL_tree_array
{
public:
	AVL_tree_array():root(nullptr),ArrayLength(0){}
	int Insert(value_t value, uint64_t index);
	value_t Get(uint64_t index);
	int Delete(uint64_t index);
	uint64_t ArrayLength;
	
private:
	AVL_node<value_t> *root;
	AVL_node<value_t> *_Insert(AVL_node<value_t> *node, value_t value, uint64_t index);
	AVL_node<value_t> *_Get(AVL_node<value_t> *node, uint64_t index);
	AVL_node<value_t> *_Delete(AVL_node<value_t> *node, uint64_t index);
	
	uint32_t GetHeight(AVL_node<value_t> *node)
	{
		if (node == nullptr)
			return 0;
		return node->height;
	}
	uint64_t GetWeight(AVL_node<value_t> *node)
	{
		if (node == nullptr)
			return 0;
		return node->weight;
	}
	uint64_t MAX(uint64_t a, uint64_t b)
	{
		if (a >= b)
			return a;
		return b;
	}
	
	int IsImbalanced(AVL_node<value_t> *node)
	{
    	uint32_t L = GetHeight(node->chd[0]);
    	uint32_t R = GetHeight(node->chd[1]);
    	if (L-R > 1 || L-R < -1)
      	  return 1;
    	return 0;
	}
	
	void UpDateHeight(AVL_node<value_t> *node)
	{
   		uint32_t LeftHeight = GetHeight(node->chd[0]),
        		RightHeight = GetHeight(node->chd[1]);
    
		node->height = 1+ MAX(LeftHeight, RightHeight);
	}
	
	void UpDateWeight(AVL_node<value_t> *node)
	{
		node->weight = 1 + GetWeight(node->chd[0]) + GetWeight(node->chd[1]);
	}
	AVL_node<value_t> *Rotate(AVL_node<value_t> *node, int dir)
	{
		AVL_node<value_t> *Child = node->chd[dir];
		AVL_node<value_t> *GrandChild = Child->chd[!dir];
		
		node->chd[dir] = GrandChild ;
		Child->chd[!dir] = node;
		
		UpDateHeight(node);
		UpDateHeight(Child);
		
		
		return Child;
	}
	
};


template<class value_t>
int AVL_tree_array<value_t>::Insert(value_t value, uint64_t index)
{
	if (index > this->ArrayLength || index < 0)
		return 0;
		
	this->root = _Insert(root, value, index);
	
	this->ArrayLength += 1;
	return 1;
}


template<class value_t>
value_t AVL_tree_array<value_t>::Get(uint64_t index)
{
	if (index >= this->ArrayLength || index < 0)
		std::cout<<"Get ("<<index<<") ????\n";
	
	AVL_node<value_t> *node ;	

	
	return node->value;
}

template<class value_t>
int AVL_tree_array<value_t>::Delete(uint64_t index)
{
	if (index >= this->ArrayLength || index < 0)
		return 0;
		

	this->ArrayLength -= 1;
	return 1;
}

template<class value_t>
AVL_node<value_t> *AVL_tree_array<value_t>::_Insert(AVL_node<value_t> *node, value_t value, uint64_t index)
{
	
	if (node == nullptr)
	{
		node = new AVL_node<value_t>(value);
		return node;
	}
	uint64_t wei = GetWeight(node->chd[0]);
	if(index <= wei)
		node->chd[0] = _Insert(node->chd[0], value, index);
	else
		node->chd[1] = _Insert(node->chd[1], value, index - wei);
	
	if (AVL_tree_array<value_t>::IsImbalanced(node))
	{
		
	}
	else
		UpDateHeight(node);
		
	UpDateWeight(node);
	return node;
}




