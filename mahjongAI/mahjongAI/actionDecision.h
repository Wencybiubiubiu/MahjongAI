#pragma once
#include "state.h"
#include "win.h"


#include <iostream>
#include <vector>

namespace wency
{
	game_state get_next_action(game_state cur_state);

	bool can_concealed_kong(user_tile input);

	bool can_exposed_kong(user_tile input, user_tile placed_input, int last_discard_til);

	game_state::player any_one_exposed_kong(game_state input_state);

	bool can_pong(user_tile input, int last_discard_til);

	game_state::player any_one_can_pong(game_state input_state);

	bool can_win(user_tile input);

}