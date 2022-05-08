#include<iostream>
#include"tree_table.hpp"
#include <time.h>
#include <vector>
int main()
{
	srand(time(NULL));

	AVL_tree_array<int> AVL_array;

	std::vector<int> Myarray(500001);

	AVL_array.Insert(100, 0);
	
	Myarray.insert(Myarray.begin(),100);



	for(int i = 1 ; i < 3000000 ; i++)
	{
		
		int num = rand()%10000000;
		int idx = rand()%(AVL_array.ArrayLength);
		int opr = rand()%7;
		
		if (opr == 0 && AVL_array.ArrayLength > 1)//ArrayLength must be at least 1, if it's 0, leading to wrong random operation. 
		{
			//Myarray.erase(Myarray.begin()+idx);
			AVL_array.Delete(idx);
		}


		if (opr >= 1 && opr <= 3)
		{
			//Myarray.insert(Myarray.begin()+idx, num);
			AVL_array.Insert(num, idx);
		}


		if (opr >= 4)
		{
			//if (AVL_array.Get(idx) != Myarray.at(idx))
			//	std::cout<<"???\n";
			AVL_array.Get(idx);
		}

		
		if (i % 1000000 == 0)
			srand(time(NULL));
	}
}
