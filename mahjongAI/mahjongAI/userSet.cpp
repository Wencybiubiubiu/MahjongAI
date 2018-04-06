#include "userSet.h"
#include <vector>
#include <iostream>
#include <stdlib.h>

namespace wency
{

	void user_tile::set_array(UserArray set_input, int * array_input, size_t array_size)
	{
		size_t array_count = 0;
		for (size_t i = 0; i < array_size; i++)
		{
			while (set_input[i] > 0) {
				array_input[array_count] = i;
				array_count++;
			}
		}
		return;
	}

	UserArray user_tile::reduce(UserArray user_input, UserArray reduce_one)
	{
		for (size_t i = 0; i < max_size; i++)
		{
			user_input[i] = user_input[i] - reduce_one[i];
		}
		return user_input;
	}

	void user_tile::set_user_array(UserArray input)
	{
		for (int i = 0; i < max_size; i++)
		{
			user_set[i] = input[i];
		}
	}

	void user_tile::add_one_tile(int input)
	{
		user_set[input]++;
	}


	void user_tile::set_user_matrix(int * input, size_t size)
	{

		for (size_t i = 0; i < size; i++)
		{
			user_set[input[i]]++;
		}

	}

	void user_tile::printUserArr()
	{
		std::cout << "[";
		for (auto value : user_set)
		{
			std::cout << " " << value;
		}
		std::cout << "]" << std::endl;

		std::vector<int> temp;
		for (size_t index = 0; index < user_set.size(); index++)
		{
			for (size_t i = 0; i < user_set[index]; i++)
			{
				temp.push_back(index);
			}
		}
		std::cout << "[";
		for (auto v : temp)
		{
			std::cout << v << " ";
		}
		std::cout << "]" << std::endl;
	}

	UserArray user_tile::get_user_set()
	{
		return user_set;
	}

}
