#include "actionDecision.h"
#include "state.h"

namespace wency
{

	game_state get_next_action(game_state cur_state)
	{
		game_state::act pre_act = cur_state.get_pre_action();
		game_state::player cur_player = cur_state.get_cur_player();
		user_tile cur_user_tile = cur_state.get_exact_player_tile(cur_player);
		user_tile cur_placed_user_tile = cur_state.get_exact_placed_player_tile(cur_player);
		int last_discard_tile = cur_state.get_last_discard_tile();

		game_state::player player_pong = any_one_can_pong(cur_state);
		game_state::player player_exposed_kong = any_one_exposed_kong(cur_state);

		switch (cur_state.get_pre_action())
		{

		case game_state::WIN:

			// std::cout << "Game finished! player " << cur_player << " wins! " << std::endl;
			break;
			// system("pause");

		case game_state::DRAW:

			if (cur_state.get_left_tiles().size() < 1)
			{
				cur_state.set_cur_action(game_state::DRAW_END);
				return cur_state;
			}

			if(can_win(cur_user_tile))
			{
				cur_state.set_cur_action(game_state::WIN);
				return cur_state;
			}
			else if (can_concealed_kong(cur_user_tile))
			{
				cur_state.set_cur_action(game_state::CONCEALED_KONG);
				return cur_state;
			}
			else
			{
				cur_state.set_cur_action(game_state::DISCARD);
				return cur_state;
			}

		case game_state::DISCARD:

				cur_state.set_cur_action(game_state::PASS);
				return cur_state;

		case game_state::PONG:

			if (can_win(cur_user_tile))
			{
				cur_state.set_cur_action(game_state::WIN);
				return cur_state;
			}
			else
			{
				cur_state.set_cur_action(game_state::DISCARD);
				return cur_state;
			}

		case game_state::EXPOSED_KONG:

			if (can_win(cur_user_tile))
			{
				cur_state.set_cur_action(game_state::WIN);
				return cur_state;
			}
			else
			{
				cur_state.set_cur_action(game_state::DRAW);
				return cur_state;
			}

		case game_state::CONCEALED_KONG:

			if (can_win(cur_user_tile))
			{
				cur_state.set_cur_action(game_state::WIN);
				return cur_state;
			}
			else
			{
				cur_state.set_cur_action(game_state::DRAW);
				return cur_state;
			}

		case game_state::PASS:

			
			if (player_pong != cur_player)
			{
				cur_state.set_cur_action(game_state::PASS);
				return cur_state;
			}
			
			if(can_pong(cur_user_tile, last_discard_tile))
			{
				cur_state.set_cur_action(game_state::PONG);
				return cur_state;
			}

			if(player_exposed_kong != cur_player)
			{
				cur_state.set_cur_action(game_state::PASS);
				return cur_state;
			}
			
			if (can_exposed_kong(cur_user_tile, cur_placed_user_tile, last_discard_tile))
			{
				cur_state.set_cur_action(game_state::EXPOSED_KONG);
				return cur_state;
			}

			cur_state.set_cur_action(game_state::DRAW);
			return cur_state;
			
		case game_state::DRAW_END:

			// std::cout << "Game finished! player " << cur_player << " wins! " << std::endl;
			break;

		case game_state::NO_ACT:

			std::cout << "ERROR WITH NO ACTION" << std::endl;
			break;

		default:
			break;
		}

		return cur_state;
	}



	bool can_concealed_kong(user_tile input)
	{
		UserArray temp = input.get_user_set();
		size_t size = temp.size();
		for (size_t i = 0; i < size; i++)
		{
			if (temp[i] == 4)
			{
				return true;
			}
		}
		return false;
	}


	bool can_exposed_kong(user_tile input, user_tile placed_input, int last_discard_til)
	{
		UserArray temp = input.get_user_set();
		UserArray temp_placed = placed_input.get_user_set();

		if(temp[last_discard_til] + temp_placed[last_discard_til] == 4)
		{
			return true;

		}
		return false;
	}

	game_state::player any_one_exposed_kong(game_state input_state)
	{

		int last_discard_tile = input_state.get_last_discard_tile();
		user_tile * player_list = input_state.get_player_list();
		size_t max_user = input_state.get_max_user();

		for (size_t i = 0; i < max_user; i++)
		{
			if (player_list[i].get_user_set()[last_discard_tile] == 3)
			{
				return (game_state::player)i;
			}
		}
		return input_state.get_cur_player();
	}

	bool can_pong(user_tile input, int last_discard_til)
	{
		UserArray temp = input.get_user_set();
		if (temp[last_discard_til] == 2)
		{
			return true;

		}
		return false;
	}

	game_state::player any_one_can_pong(game_state input_state)
	{
		int last_discard_tile = input_state.get_last_discard_tile();
		user_tile * player_list = input_state.get_player_list();
		size_t max_user = input_state.get_max_user();

		for(size_t i = 0; i < max_user; i ++)
		{
			if(player_list[i].get_user_set()[last_discard_tile] == 2)
			{
				return (game_state::player)i;
			}
		}
		return input_state.get_cur_player();
	}

	bool can_win(user_tile input)
	{
		win_tile temp(input);
		return temp.get_result();
	}

}
