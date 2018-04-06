#include "state.h"

namespace wency
{

	void game_state::init_all_tiles()
	{
		for(size_t i = 0; i < total_tile_num; i ++)
		{
			left_tiles.push_back(i % type_num);
			if (i % type_num == 0)
			{
			   left_tiles.pop_back();
			   left_tiles.push_back(red_center);
			}
		}
	}

	UserArray game_state::get_left_tiles()
	{
		return left_tiles;
	}

	UserArray game_state::get_init_player()
	{
		user_tile temp_tile;
		
		int temp[init_tile_num];

		for (size_t i = 0; i < init_tile_num; i++)
		{
			int rnd = rand() % total_tile_num;
			while (left_tiles[rnd] == 0)
			{
				rnd = rand() % total_tile_num;
			}
			temp[i] = left_tiles[rnd];
			left_tiles[rnd] = 0;
		}
		temp_tile.set_user_matrix(temp, init_tile_num);
		return temp_tile.get_user_set();
	}


	void game_state::init_player_rnd()
	{
		UserArray temp;
		for (int i = 0; i < max_user; i++)
		{
			temp = get_init_player();
			player_list[i].set_user_array(temp);
		}

	}

	void game_state::print_all_players_arr()
	{

		for (int i = 0; i < max_user; i++)
		{
			print_player_arr(player_list[i], i);
			print_player_arr(player_placed[i], i);
		}
	

	}

	void game_state::print_left_tiles()
	{
		int count = 0;

		std::cout << "The left tiles array is: [ ";
		size_t size = left_tiles.size();
		for (size_t i = 0; i < size; i ++)
		{
			if (left_tiles[i] != 0) {
				count++;
				std::cout << left_tiles[i] << " ";
			}
		}
		std::cout << "]" << std::endl;

		std::cout << "The discard tiles array is: [ ";
		for (size_t i = 0; i < discard_tiles.size(); i++)
		{
			if (discard_tiles[i] != 0) {
				
				std::cout << discard_tiles[i] << " ";
			}
		}
		std::cout << "]" << std::endl;

		int discard = 0;
		for (size_t n = 0; n < max_user; n++)
		{
			for (size_t j = 0; j < total_diff_tile_num + 1; j++)
			{
				discard = discard + player_list[n].get_user_set()[j]+ player_placed[n].get_user_set()[j];
				
			}
		}
		
		std::cout << "Left tiles number: " << count << std::endl;
		std::cout << "Discard tiles number: " << discard_tiles.size() << std::endl;
		std::cout << "Total user tiles number: " << discard << std::endl;
		
	}

	void game_state::print_cur_state()
	{
		std::cout << "Current player is : " << cur_player << std::endl;
		std::cout << "Dealer is : " << dealer << std::endl;
	
		std::cout << "Last discard player is : " << last_discard << std::endl;
		std::cout << "Last discard tile is : " << last_discard_tile << std::endl;
		
		print_action_list();
	}

	void game_state::print_player_arr(user_tile input_player, int player_num)
	{
		std::cout << "The player " << player_num << " array is: [ ";
		int count = 0;
		for( size_t i = 0; i <= total_diff_tile_num; i++)
		{
			count += input_player.get_user_set()[i];
			std::cout << input_player.get_user_set()[i] << " ";
		}
		std::cout << "] tiles num: " << count << std::endl;
	}

	void game_state::print_action_list()
	{

		std::cout << "The previous action is: " << action_list[pre_act] << std::endl;
		std::cout << "The current action is: " << action_list[cur_act] << std::endl;
	}

	game_state::player game_state::get_dealer_rnd()
	{
		int i = rand() % 4;
		return (player)i;
		
	}

	void game_state::delete_zero_of_left_tiles()
	{
		UserArray temp;
		for (size_t i = 0; i < left_tiles.size(); i++)
		{
			if (left_tiles[i] != 0)
			{
				temp.push_back(left_tiles[i]);
			}
		}
		left_tiles = temp;
		
	}


	void game_state::draw(player need_draw)
	{
		size_t left_tiles_size = left_tiles.size();
		if (left_tiles_size < 1)
		{
			std::cout << "Left tiles used up, index error" << std::endl;
			action_list[pre_act] = DRAW_END;
			action_list[cur_act] = DRAW_END;
			return;
		}
		int temp = rand() % left_tiles_size;
		while (left_tiles[temp] == 0)
		{
			temp = rand() % left_tiles_size;
		}
		int result = left_tiles[temp];
		left_tiles[temp] = 0;
		delete_zero_of_left_tiles();
		
		UserArray temp_cur_tile = player_list[need_draw].get_user_set();
		temp_cur_tile[result] ++;
		player_list[need_draw].set_user_array(temp_cur_tile);

		//std::cout << "The drawn tile is : " << result << std::endl;
	}

	void game_state::discard(player need_discard)
	{
		int tile_matrix_index = rand() % (total_diff_tile_num);
		UserArray temp_cur_tile = player_list[need_discard].get_user_set();
		while (temp_cur_tile[tile_matrix_index] < 1)
		{
			tile_matrix_index = rand() % (total_diff_tile_num);
		}
	/*
		int tile_matrix_index = decide_index_to_discard(need_discard);
		UserArray temp_cur_tile = player_list[need_discard].get_user_set();
		if (temp_cur_tile[tile_matrix_index] < 1)
		{
			std::cout << "No tile can be discarded, index error in DISCARD" << std::endl;
			return;
		}
    */
		temp_cur_tile[tile_matrix_index] --;
		player_list[need_discard].set_user_array(temp_cur_tile);


		last_discard = cur_player;

		last_discard_tile = tile_matrix_index;
		discard_tiles.push_back(last_discard_tile);
		
		return;
		
	}

	int game_state::decide_index_to_discard(player need_discard)
	{
		size_t size = player_list[need_discard].get_user_set().size();
		for (size_t i = 0; i < size; i++)
		{
			if (player_list[need_discard].get_user_set()[i] != 0)
			{
				return i;
			}
		}
		std::cout << "index error in discard" << std::endl;
		return -1;
	}

	void game_state::pong(player need_pong)
	{
		int tile_matrix_index = last_discard_tile;

		if (tile_matrix_index >  total_diff_tile_num)
		{
			return;
		}

		UserArray temp_user_arr;
		UserArray temp_placed;


		temp_user_arr = player_list[need_pong].get_user_set();
		if (temp_user_arr[tile_matrix_index] < 2)
		{
			std::cout << "index error in PONG" << std::endl;
			return;
		}
		temp_user_arr[tile_matrix_index] -= 2;
		player_list[need_pong].set_user_array(temp_user_arr);

		temp_placed = player_placed[need_pong].get_user_set();
		temp_placed[tile_matrix_index] += 3;
		player_placed[need_pong].set_user_array(temp_placed);

		discard_tiles.pop_back();
		//discard(need_pong);
	}

	void game_state::exposed_kong(player need_kong)
	{
		int tile_matrix_index = last_discard_tile;

		UserArray temp_cur_tile = player_list[need_kong].get_user_set();
		UserArray temp_placed_tile = player_placed[need_kong].get_user_set();

		for (size_t i = 0; i < temp_cur_tile.size(); i++)
		{
			if (temp_cur_tile[i] + temp_placed_tile[i] == 4)
			{
				temp_cur_tile[i] = 0;
				temp_placed_tile[i] = 4;
				player_list[need_kong].set_user_array(temp_cur_tile);
				player_placed[need_kong].set_user_array(temp_placed_tile);
				return;
			}
		}

		if ((temp_cur_tile[tile_matrix_index] + temp_placed_tile[tile_matrix_index] < 3))
		{
			std::cout << "No pong to kong, error" << std::endl;
			return;
		}
		if (temp_cur_tile[tile_matrix_index] == 3)
		{
			temp_cur_tile[tile_matrix_index] -= 3;
			player_list[need_kong].set_user_array(temp_cur_tile);

			temp_placed_tile[tile_matrix_index] += 4;
			player_placed[need_kong].set_user_array(temp_placed_tile);
		}
		else if(temp_placed_tile[tile_matrix_index] == 3)
		{
			temp_placed_tile[tile_matrix_index] ++;
			player_placed[need_kong].set_user_array(temp_placed_tile);
		}
		else
		{
			temp_cur_tile[tile_matrix_index] = 0;
			temp_placed_tile[tile_matrix_index] = 4;
			player_list[need_kong].set_user_array(temp_cur_tile);
			player_placed[need_kong].set_user_array(temp_placed_tile);
		}
		discard_tiles.pop_back();
		//draw(need_kong);
		//discard(need_kong);
	}

	void game_state::concealed_kong(player need_kong)
	{
		int tile_matrix_index;
		UserArray temp_cur_tile = player_list[need_kong].get_user_set();
		for (size_t i = 0; i < temp_cur_tile.size(); i++)
		{
			if (temp_cur_tile[i] == 4)
			{
				tile_matrix_index = i;
				
			}
		}
		UserArray temp_placed_tile = player_placed[need_kong].get_user_set();
		if (temp_cur_tile[tile_matrix_index] != 4)
		{
			std::cout << "No pong to kong, error" << std::endl;
			return;
		}

		temp_cur_tile[tile_matrix_index] -= 4;
		player_list[need_kong].set_user_array(temp_cur_tile);

		temp_placed_tile[tile_matrix_index] += 4;
		player_placed[need_kong].set_user_array(temp_placed_tile);

		//discard_tiles.pop_back();
		//draw(need_kong);
		//discard(need_kong);
	}

	void game_state::pass(player need_pass)
	{
		cur_player = (player)(((int)need_pass + 1) % 4);
	}

	void game_state::win(player need_win)
	{

		std::cout << "Game finished! player " << need_win << " wins! " << std::endl;

		// system("pause");

	}

	void game_state::draw_end()
	{
		std::cout << "No left tiles, the game end without winner! " << std::endl;
		return;
	}

	void game_state::take_action()
	{
		
		act now_acting = action_list[cur_act];
		
			switch(now_acting)
			{
			case WIN:
				win(cur_player);
				break;
			case DRAW:
				draw(cur_player);
				break;
			case DISCARD:
				discard(cur_player);
				break;
			case PONG:
				pong(cur_player);
				break;
			case EXPOSED_KONG:
				exposed_kong(cur_player);
				break;
			case CONCEALED_KONG:
				concealed_kong(cur_player);
				break;
			case PASS:
				pass(cur_player);
				break;

			case DRAW_END:
				// std::cout << "ENDENDENDENDENDENDENDNENDNEND " << std::endl;
				draw_end();
				break;

			case NO_ACT:

				// std::cout << "No ACT" << std::endl;
				return;

			default:
				std::cout << "Take action error" << std::endl;
				return;
			}
		

		action_list[pre_act] = now_acting;
		action_list[cur_act] = NO_ACT;

		return;

	}
	

}
