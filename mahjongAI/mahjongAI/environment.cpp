#include "environment.h"

namespace wency
{
	void wency::environment_test()
	{
		for (int n = 0; n < 10000; n++) {
			int cond = 0;
			game_state state_test;
			
			for (int i = 0; i < 10000; i++)
			{
				/*
				if ((n == 4) && (state_test.get_left_tiles().size() < 3))
				{
					state_test.print_left_tiles();
					state_test.print_all_players_arr();
					state_test.print_cur_state();
					system("pause");
				}
				*/
				if (state_test.get_pre_action() == game_state::DRAW_END)
				{
					// cond = 1;
					// std::cout << "No left tiles" << std::endl;
					break;
				}
				
				if (i == 10000)
				{
					cond = 1;
					std::cout << "index 10000 reached, but result still not gotten" << std::endl;
					break;
				}
				if (get_total_tile_num(state_test) != 112)
				{
					cond = 1;
					std::cout << "The total tiles number error, the number now is: " << get_total_tile_num(state_test) << std::endl;
					state_test.print_left_tiles();
					state_test.print_all_players_arr();
					// break;
				}
				state_test.take_action();
				state_test = get_next_action(state_test);
				if (state_test.get_pre_action() == game_state::WIN)
				{
					win_tile temp(state_test.get_player_list()[state_test.get_cur_player()]);
					if (temp.get_result() != true)
					{
						cond = 1;
						std::cout << "Win tile decision false, the player cannot win! " << std::endl;
						return;
					}
					break;
				}
				
			}
			if (cond) {
				state_test.print_left_tiles();
				state_test.print_all_players_arr();
				std::cout << "Error, the index is: " << n << std::endl;
				system("pause");
				// state_test.print_cur_state();
				// system("pause");
			}
			if (n % 100 == 0)
			{
				std::cout << "[" << n << "/10000]" << std::endl;
			}
		}


	}
	int get_total_tile_num(game_state input)
	{
		

		int sum = 0;
		for (size_t n = 0; n < max_user; n++)
		{
			for (size_t j = 0; j < total_diff_tile_num + 1; j++)
			{
				sum = sum + input.get_player_list()[n].get_user_set()[j] + input.get__placed_player_list()[n].get_user_set()[j];

			}
		}
		// std::cout << sum << std::endl;
		sum = sum + input.get_discard_tiles().size() + input.get_left_tiles().size();
		return sum;
	}

}
