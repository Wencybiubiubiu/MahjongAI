#include "win.h"
#include "userSet.h"

namespace wency
{


	bool win_tile::get_result(UserArray input, int pair)
	{


		int sum = 0;
		for (size_t i = 0; i < max_size; i++)
		{
			sum = sum + input[i];
		}
		if (sum == 0)
		{
			return true;
		}
		if (input[31] == 4)
		{
			return true;
		}

		for (size_t m = 0; m < max_size; m++)
		{
			if (input[m] > 0)
			{
				if ((input[m] >= 2) && (pair == 1))
				{
					UserArray temp;
					for (size_t n = 0; n < max_size; n++)
					{
						temp.push_back(0);
					}
					temp[m] = 2;
					if (get_result(cur_tile.reduce(input, temp), pair - 1))
					{
						return true;
					}
				}

				if (input[m] >= 3)
				{
					UserArray temp;
					for (size_t n = 0; n < max_size; n++)
					{
						temp.push_back(0);
					}
					temp[m] = 3;
					if (get_result(cur_tile.reduce(input, temp), pair))
					{
						return true;
					}
				}



				if (input[m] >= 4)
				{
					UserArray temp;
					for (size_t n = 0; n < max_size; n++)
					{
						temp.push_back(0);
					}
					temp[m] = 4;
					if (get_result(cur_tile.reduce(input, temp), pair))
					{
						return true;
					}
				}

				if (m < max_size - 2) {
					if ((m < max_size - 2) && (input[m + 1] > 0) && (input[m + 2] > 0))
					{
						UserArray temp;
						for (size_t n = 0; n < max_size; n++)
						{
							temp.push_back(0);
						}
						temp[m] = 1;
						temp[m + 1] = 1;
						temp[m + 2] = 1;

						if (get_result(cur_tile.reduce(input, temp), pair))
						{
							return true;
						}
					}
				}

				if ((input[max_size - 1] > 0) && (input[m] > 0))
				{
					UserArray temp;
					for (size_t n = 0; n < max_size; n++)
					{
						temp.push_back(0);
					}
					temp[max_size - 1] = 1;
					temp[m] = 1;
					if (get_result(cur_tile.reduce(input, temp), pair - 1))
					{
						return true;
					}
				}

				if ((input[max_size - 1] > 0) && (input[m] >= 2))
				{
					UserArray temp;
					for (size_t n = 0; n < max_size; n++)
					{
						temp.push_back(0);
					}
					temp[max_size - 1] = 1;
					temp[m] = 2;
					if (get_result(cur_tile.reduce(input, temp), pair))
					{
						return true;
					}
				}

				if (m < max_size - 1) {
					if ((input[max_size - 1] > 0) && (input[m] > 0) && (input[m + 1] > 0))
					{
						UserArray temp;
						for (size_t n = 0; n < max_size; n++)
						{
							temp.push_back(0);
						}
						temp[max_size - 1] = 1;
						temp[m] = 1;
						temp[m + 1] = 1;
						if (get_result(cur_tile.reduce(input, temp), pair))
						{
							return true;
						}
					}
				}

				if (m < max_size - 2) {
					if ((input[max_size - 1] > 0) && (input[m] > 0) && (input[m + 2] > 0) && (input[m + 1] == 0))
					{
						UserArray temp;
						for (size_t n = 0; n < max_size; n++)
						{
							temp.push_back(0);
						}
						temp[max_size - 1] = 1;
						temp[m] = 1;
						temp[m + 2] = 1;
						if (get_result(cur_tile.reduce(input, temp), pair))
						{
							return true;
						}
					}
				}
			}
		}

		return false;
	}

	bool win_tile::get_result()
	{
		return get_result(cur_user_set, 1);
	}

}
