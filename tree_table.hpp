#include<iostream>
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
	int64_t weight;
	int32_t height;
	value_t value;
	
};

template<class value_t>
class AVL_tree_array
{
public:
	AVL_tree_array():root(nullptr),ArrayLength(0){}
	int Insert(value_t value, int64_t index);
	value_t Get(int64_t index);
	int Delete(int64_t index);
	void traverse();

	int64_t ArrayLength;

	
private:
	AVL_node<value_t> *root;
	AVL_node<value_t> *_Insert(AVL_node<value_t> *node, value_t value, int64_t index);
	AVL_node<value_t> *_Get(AVL_node<value_t> *node, int64_t index);
	AVL_node<value_t> *_Delete(AVL_node<value_t> *node, int64_t index);
	uint32_t GetHeight(AVL_node<value_t> *node)
	{
		if (node == nullptr)
			return 0;
		return node->height;
	}
	int64_t GetWeight(AVL_node<value_t> *node)
	{
		if (node == nullptr)
			return 0;
		return node->weight;
	}
	int64_t MAX(int64_t a, int64_t b)
	{
		if (a >= b)
			return a;
		return b;
	}
	
	int IsImbalanced(AVL_node<value_t> *node)
	{
    	int32_t L = GetHeight(node->chd[0]);
    	int32_t R = GetHeight(node->chd[1]);
    	if (L-R > 1 || L-R < -1)
      	  return 1;
    	return 0;
	}
	
	void UpdateHeight(AVL_node<value_t> *node)
	{
   		int32_t LeftHeight = GetHeight(node->chd[0]),
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
		
		UpdateHeight(node);
		UpdateHeight(Child);
		
		UpDateWeight(node);
		UpDateWeight(Child);

		return Child;
	}
	AVL_node<value_t> *_traverse(AVL_node<value_t> *node)
	{
		if (node == nullptr)
			return nullptr;

		_traverse(node->chd[0]);
		std::cout << node->value << " " <<node->weight << '\n';
		_traverse(node->chd[1]);
	}


};


template<class value_t>
int AVL_tree_array<value_t>::Insert(value_t value, int64_t index)
{
	if (index > this->ArrayLength || index < 0)
		return 0;
		
	this->root = _Insert(root, value, index);
	
	this->ArrayLength += 1;
	return 1;
}


template<class value_t>
value_t AVL_tree_array<value_t>::Get(int64_t index)
{
	if (index >= this->ArrayLength || index < 0)
	{
		std::cout<<"you cna't get" <<index<<"th item\n";
		value_t nothing;
		return nothing;
	}
		
	
	AVL_node<value_t> *node = _Get(this->root, index);	

	
	return node->value;
}

template<class value_t>
int AVL_tree_array<value_t>::Delete(int64_t index)
{
	if (index >= this->ArrayLength || index < 0)
		return 0;
		
	this->root = _Delete(this->root, index);

	this->ArrayLength -= 1;
	return 1;
}



template<class value_t>
void AVL_tree_array<value_t>::traverse()
{
	_traverse(this->root);
}






template<class value_t>
AVL_node<value_t> *AVL_tree_array<value_t>::_Insert(AVL_node<value_t> *node, value_t value, int64_t index)
{
	
	if (node == nullptr)
	{
		node = new AVL_node<value_t>(value);
		return node;
	}

	int64_t wei = GetWeight(node->chd[0]);

	

	if(index <= wei)
		node->chd[0] = _Insert(node->chd[0], value, index);
	else
		node->chd[1] = _Insert(node->chd[1], value, index - wei - 1);
	
	if (AVL_tree_array<value_t>::IsImbalanced(node))
	{
		int dir = index > wei;
		AVL_node<value_t> *child = node->chd[dir];

		if (GetHeight(child->chd[!dir]) > GetHeight(child->chd[dir]))
			node->chd[dir] = Rotate(node->chd[dir], !dir);
		node = Rotate(node, dir);

	}
	else
	{
		UpdateHeight(node);
		UpDateWeight(node);
	}
	
	return node;
}

template<class value_t>
AVL_node<value_t> *AVL_tree_array<value_t>::_Get(AVL_node<value_t> *node, int64_t index)
{
	int64_t wei = GetWeight(node->chd[0]);
	AVL_node<value_t> *ret;


	if (index + 1 <= wei)
		ret = _Get(node->chd[0], index);
	else if (index + 1 > wei+1)
		ret = _Get(node->chd[1], index - wei - 1);
	else if (index == wei)
		ret = node;

	return ret;

}





template<class value_t>
AVL_node<value_t> *AVL_tree_array<value_t>::_Delete(AVL_node<value_t> *node, int64_t index)
{
	
	int64_t wei = GetWeight(node->chd[0]);
	
	AVL_node<value_t> *ret;

	if (index + 1 <= wei)
		node->chd[0] = _Delete(node->chd[0], index);
	else if (index + 1 > wei+1)
		node->chd[1] = _Delete(node->chd[1], index - wei - 1);
	else if (index == wei)
	{
		if (node->chd[0] == nullptr || node->chd[1] == nullptr)
		{
			if (node->chd[0])
				ret = node->chd[0];	
            else			
				ret = node->chd[1];
		
            delete node; 

			return ret;
		}
		else
		{
			AVL_node<value_t> *tmp = node->chd[0];

            while(tmp->chd[1])		
				tmp = tmp->chd[1];
			

			node->value = tmp->value;

            node->chd[0] = _Delete(node->chd[0], GetWeight(node->chd[0]) - 1);	
		}
	}		
	

	if(IsImbalanced(node))
	{
		int dir = 0;
		
		if (GetHeight(node->chd[0]) < GetHeight(node->chd[1]))
			dir = 1;

		if (GetHeight(node->chd[dir]->chd[!dir]) > GetHeight(node->chd[dir]->chd[dir]))
			node->chd[dir] = Rotate(node->chd[dir], !dir);
		node = Rotate(node, dir);
	}
	else
	{
		UpdateHeight(node);
		
		UpDateWeight(node);
	}

	
	return node;
}