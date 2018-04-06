#pragma once

#include "userSet.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>

namespace wency
{

	static const size_t total_tile_num = 112;
	static const size_t total_diff_tile_num = 31;
	static const int init_tile_num = 13;
	static const int max_user = 4;
	const int red_center = 31;
	const int type_num = 28;
	const int repeat_num = 4;

	class game_state 
	{

	public:

		enum player : int
		{
			PLAYER0 = 0,
			PLAYER1 = 1,
			PLAYER2 = 2,
			PLAYER3 = 3,
			NO_PLAYER = -1,

		};

		enum act : int
		{
			WIN = 4,
			DISCARD = 5,
			DRAW = 6,
			PONG = 7,
			EXPOSED_KONG = 8,
			CONCEALED_KONG = 9,
			PASS = 10,
			DRAW_END = 11,
			NO_ACT = -1,
		};

	private:

		user_tile player_list[max_user];
		user_tile player_placed[max_user];

		player cur_player;
		player last_discard;
		player dealer;


		UserArray discard_tiles;
		UserArray left_tiles;
		act action_list[2];
	    int pre_act = 0;
		int cur_act = 1;
	
		int last_discard_tile;

		void init_all_tiles();

		void print_player_arr(user_tile input_player, int player_num);

		void print_action_list();

		player get_dealer_rnd();

		UserArray get_init_player();

		

	public:


		game_state() :
			discard_tiles(0)
		{
			init_all_tiles();
			delete_zero_of_left_tiles();

			dealer = get_dealer_rnd();
			last_discard = NO_PLAYER;
			cur_player = dealer;
			
			
			action_list[pre_act] = NO_ACT;
			action_list[cur_act] = NO_ACT;

			last_discard_tile = 0;

			init_player_rnd();
			delete_zero_of_left_tiles();

			draw(dealer);
			action_list[pre_act] = DRAW;
			/*
			discard(PLAYER0);
			last_discard_tile = 26;
			discard_tiles.push_back(last_discard_tile);
			pong(PLAYER0);	
			last_discard_tile = 25;
			discard_tiles.push_back(last_discard_tile);
			pong(PLAYER3);

			*/

			/*
			UserArray temp = player_list[0].get_user_set();
			temp[29] = 3;
			player_list[0].set_user_array(temp);
			last_discard_tile = 29;
			discard_tiles.push_back(last_discard_tile);
			exposed_kong(PLAYER0);
			*/
		}

		// initialization

		UserArray get_left_tiles();

		void init_player_rnd();
		
		void delete_zero_of_left_tiles();

		// print

		void print_all_players_arr();

		void print_left_tiles();

		void print_cur_state();


		

		// action list

		// draw a tile from left tiles, and return the drawn tile
		// need to add the return value to exact user set
		void draw(player need_draw);

		// discard a tile from user set to discard_tiles
		// return the tile that is discarded(index), need to deal with it then
		void discard(player need_discard);

		int decide_index_to_discard(player need_discard);

		// place 2 same tiles and one pong tile in user set to placed tile set
		// need to discard one tile in user set to exchange that pong tile
		void pong(player need_pong);

		// exposed kong 
		void exposed_kong(player need_kong);

		// concealed kong
		void concealed_kong(player need_kong);

		// pass to next action( do nothing )
		void pass(player need_pass);

		// if win, just print out player who wins
		void win(player need_win);

		// if there are no left tiles, this game ends without winner
		void draw_end();

		// take current action
		void take_action();



		// inline function
		inline int get_max_user()
		{
			return max_user;
		}

		inline act get_pre_action()
		{
			return action_list[pre_act];
		}

		inline void set_cur_action(act input)
		{
			action_list[cur_act] = input;
		}

		inline user_tile get_exact_player_tile(player input)
		{
			return player_list[input];
		}


		inline user_tile get_exact_placed_player_tile(player input)
		{
			return player_placed[input];
		}

		inline user_tile * get_player_list()
		{
			return player_list;
		}


		inline user_tile * get__placed_player_list()
		{
			return player_placed;
		}

		inline player get_cur_player()
		{
			return cur_player;
		}

		inline int get_last_discard_tile()
		{
			return last_discard_tile;
		}

		inline UserArray get_discard_tiles()
		{
			return discard_tiles;
		}

	};
	
}