#pragma once
#include "userSet.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>

namespace wency
{
	class win_tile
	{
	private:

		
		user_tile cur_tile;
		UserArray cur_user_set;

		bool get_result(UserArray input, int pair);

	public:

		win_tile(user_tile input)
		{
			cur_tile = input;
			cur_user_set = input.get_user_set();
		}

		bool get_result();

		inline UserArray get_cur_user_set()
		{
			return cur_user_set;
		}

		inline void set_cur_user_set(UserArray input)
		{
			cur_user_set = input;
		}
	};
}