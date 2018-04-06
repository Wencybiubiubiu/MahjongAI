#pragma once
#include <ctime>
#include <vector>

namespace wency
{

	const size_t max_size = 32;

	using UserArray = std::vector<int>;

	class user_tile
	{

	private:

		
		UserArray user_set;


		void set_array(UserArray set_input, int * array_input, size_t array_size);

		



	public:

		// input an array, and convert it to the user set vector
		user_tile() :
			user_set(max_size, 0)
		{

			for (size_t i = 0; i < max_size; i++)
			{
				user_set[i] = 0;
			}

		}

		// convert 14 cards array to 32 matrix
		void set_user_matrix(int * input, size_t size);

		void printUserArr();

		UserArray get_user_set();

		// get user_input - reduce_one
		UserArray reduce(UserArray user_input, UserArray reduce_one);

		void set_user_array(UserArray input);

		void add_one_tile(int input);

	};

}