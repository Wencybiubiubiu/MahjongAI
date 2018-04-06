#pragma once
#include <vector>
#include <iostream>

#include "win.h"
#include "userSet.h"
#include "state.h"


namespace mahjong_unittest
{
	const size_t g_MAX_TILE_INDEX = 144;
	const size_t g_MELD_COUNT = 4;
	const size_t g_PAIR_COUNT = 1;
	constexpr const size_t g_MAX_USER_TILES = (3 * g_MELD_COUNT) + (2 * g_PAIR_COUNT);


	struct UserArray
	{
		int cards[g_MAX_USER_TILES];
		void print() const
		{
			std::cout << "[";
			for (auto value : cards)
			{
				std::cout << " " << value;
			}
			std::cout << "]" << std::endl;
		}
	};

	class TerminalStateGenerator
	{
	private:
		using TileArray = std::vector<int>;
		
		std::vector<TileArray> _meld_set;
		std::vector<TileArray> _pair_set;

	private:
		bool IsLegalState(const TileArray& arr) const
		{
			TileArray tiles(g_MAX_TILE_INDEX, 0);
			for (auto value : arr)
			{
				tiles[value]++;
			}
			for (auto value : tiles)
			{
				if (value > 4)
				{
					return false;
				}
			}
			return true;
		}

		UserArray TileArrayToUserArray(const TileArray& arr) const
		{
			UserArray user_arr;
			for (size_t i = 0; i < g_MAX_USER_TILES; i++)
			{
				user_arr.cards[i] = arr[i];
			}
			return user_arr;
		}

		TileArray GetTerminalState_RedFalse() const
		{
			for (;;)
			{
				TileArray temp;
				for (size_t i = 0; i < g_MELD_COUNT - 1; i++)
				{
					auto rnd = rand() % _meld_set.size();
					for (auto value : _meld_set[rnd])
					{
						temp.push_back(value);
					}
				}
				for (size_t i = 0; i < g_PAIR_COUNT; i++)
				{
					auto rnd = rand() % _pair_set.size();
					for (auto value : _pair_set[rnd])
					{
						temp.push_back(value);
					}
				}

				temp.push_back(31);
				temp.push_back(31);
				temp.push_back(31);

				int single_tile_1 = GetSingleTile(temp);
				temp[g_MAX_USER_TILES - 3] = single_tile_1;
				int single_tile_2 = GetSingleTile(temp);
				temp[g_MAX_USER_TILES - 2] = single_tile_2;
				int single_tile_3 = GetSingleTile(temp);
				temp[g_MAX_USER_TILES - 1] = single_tile_3;
				temp[0] = 31;

				if (IsLegalState(temp))
				{
					return temp;
				}
			}

		}

		TileArray GetTerminalState() const
		{
			for (;;)
			{
				TileArray temp;
				for (size_t i = 0; i < g_MELD_COUNT; i++)
				{
					auto rnd = rand() % _meld_set.size();
					for (auto value : _meld_set[rnd])
					{
						temp.push_back(value);
					}
				}
				for (size_t i = 0; i < g_PAIR_COUNT; i++)
				{
					auto rnd = rand() % _pair_set.size();
					for (auto value : _pair_set[rnd])
					{
						temp.push_back(value);
					}
				}

				if (IsLegalState(temp))
				{
					/*std::cout << "[";
					for (auto value : temp)
					{
					std::cout << " " << value;
					}
					std::cout << "]" << std::endl;*/
					return temp;
				}
			}
		}

		int GetSingleTile(const TileArray& arr) const
		{
			TileArray tiles(g_MAX_TILE_INDEX, 0);
			for (auto value : arr)
			{
				tiles[value] ++;
			}
			for (size_t i = 1; i < 30; i++)
			{
				if (tiles[i - 1] == 0 && tiles[i] == 0 && tiles[i + 1] == 0 && i % 10 != 0)
				{
					return static_cast<int>(i);
				}
			}
			std::cout << "my code failed" << std::endl;
			system("pause");
			return 0; 
		}

		void ReplaceSingleTile(TileArray& arr, int tile) const
		{
			TileArray tiles(g_MAX_TILE_INDEX, 0);
			for (auto value : arr)
			{
				tiles[value] ++;
			}
			for (size_t i = 0; i < g_MAX_USER_TILES; i++)
			{
				if (tiles[arr[i]] == 1)
				{
					arr[i] = tile;
					return;
				}
			}
			std::cout << "my code failed" << std::endl;
			system("pause");
		}


		inline UserArray get() const
		{
			return TileArrayToUserArray(GetTerminalState());
		}


		UserArray get_false_case() const
		{
			TileArray arr = GetTerminalState();
			int single_tile = GetSingleTile(arr);
			size_t rnd = rand() % arr.size();
			arr[rnd] = single_tile;
			return TileArrayToUserArray(arr);
		}


		UserArray get_red_center_case() const
		{
			TileArray arr = GetTerminalState();
			arr[rand() % arr.size()] = 31;
			return TileArrayToUserArray(arr);
		}


		UserArray get_red_center_false_case() const
		{
			TileArray arr = GetTerminalState_RedFalse();
			return TileArrayToUserArray(arr);

		}

		UserArray get_kong() const
		{
			TileArray arr = GetTerminalState();
			int random = rand() % 32;
			bool is_zero = true;
			for (size_t i = 0; i < arr.size(); i++)
			{
				if (arr[i] == random) is_zero = false;
			}
			
			while (!is_zero) 
			{
				is_zero = true;
				random = rand() % 32;
				while(random%10 == 0) 
				{
					random = rand() % 32;
				}

				for (size_t i = 0; i < arr.size(); i++)
				{
					if (arr[i] == random) is_zero = false;
				}
			}

			
			for (int i = 0; i < 4; i++) {
				arr.push_back(random);
			}
			return TileArrayToUserArray(arr);

		}

		UserArray get_kong_red_center_false() const
		{
			TileArray arr = GetTerminalState_RedFalse();
			int random = rand() % 32;
			bool is_zero = true;
			for (size_t i = 0; i < arr.size(); i++)
			{
				if (arr[i] == random) is_zero = false;
			}

			while (!is_zero)
			{
				is_zero = true;
				random = rand() % 32;
				while (random % 10 == 0)
				{
					random = rand() % 32;
				}

				for (size_t i = 0; i < arr.size(); i++)
				{
					if (arr[i] == random) is_zero = false;
				}
			}


			for (int i = 0; i < 4; i++) {
				arr.push_back(random);
			}
			return TileArrayToUserArray(arr);

		}


	public:
		TerminalStateGenerator()
		{
			std::cout << "TerminalStateGenerator initializing." << std::endl;
			for (size_t tens = 0; tens < 3; tens++)
			{
				//tens from 0 to 2.
				for (size_t digit = 1; digit <= 9; digit++)
				{
					//digit from 1 to 9.
					size_t num = tens * 10 + digit;
					if (digit <= 7)
					{
						TileArray meld_temp;
						meld_temp.push_back(num);
						meld_temp.push_back(num + 1);
						meld_temp.push_back(num + 2);
						_meld_set.push_back(meld_temp);
					}
					TileArray pair_temp;
					pair_temp.push_back(num);
					pair_temp.push_back(num);
					_pair_set.push_back(pair_temp);

				}
			}
			std::cout << "initialization finished. meld = " << _meld_set.size() << "pair = " << _pair_set.size() << std::endl;
		}

		void test_true_case() const
		{

			TerminalStateGenerator generator;
			const size_t t = 1000000;

			clock_t start, end, diff;
			start = clock();
			for (size_t i = 0; i < t; i++)
			{
				if (i % (t / 1000) == 0)
				{
					std::cout << "[" << i << "/" << t << "]" << std::endl;
				}
				auto temp = generator.get();
				wency::user_tile a;
				a.set_user_matrix(temp.cards, 14);
				wency::win_tile cur_tile(a);
				if (cur_tile.get_result() == false)
				{
					std::cout << "Assert Failed!, index = " << i << " userArr = ";
					a.printUserArr();
					system("pause");
				}
			}
			end = clock();
			diff = end - start;
			std::cout << "The speed is: " << (float(diff) / CLK_TCK) << std::endl;

		}


		void test_false_case() const
		{

			TerminalStateGenerator generator;
			const size_t t = 1000000;

			clock_t start, end, diff;
			start = clock();
			for (size_t i = 0; i < t; i++)
			{
				if (i % (t / 1000) == 0)
				{
					std::cout << "[" << i << "/" << t << "]" << std::endl;
				}
				auto temp = generator.get_false_case();
				wency::user_tile a;
				a.set_user_matrix(temp.cards, 14);
				wency::win_tile cur_tile(a);
				if (cur_tile.get_result() == true)
				{
					std::cout << "Assert Failed!, index = " << i << " userArr = ";
					a.printUserArr();
					system("pause");
				}
			}
			end = clock();
			diff = end - start;
			std::cout << "The speed is: " << (float(diff) / CLK_TCK) << std::endl;

		}


		void test_red_center_true_case() const
		{

			TerminalStateGenerator generator;
			const size_t t = 1000000;

			clock_t start, end, diff;
			start = clock();
			for (size_t i = 0; i < t; i++)
			{
				if (i % (t / 1000) == 0)
				{
					std::cout << "[" << i << "/" << t << "]" << std::endl;
				}
				auto temp = generator.get_red_center_case();
				wency::user_tile a;
				a.set_user_matrix(temp.cards, 14);
				wency::win_tile cur_tile(a);
				if (cur_tile.get_result() == false)
				{
					std::cout << "Assert Failed!, index = " << i << " userArr = ";
					a.printUserArr();
					system("pause");
				}
			}
			end = clock();
			diff = end - start;
			std::cout << "The speed is: " << (float(diff) / CLK_TCK) << std::endl;

		}

		void test_red_center_false_case() const
		{

			TerminalStateGenerator generator;
			const size_t t = 1000000;

			clock_t start, end, diff;
			start = clock();
			for (size_t i = 0; i < t; i++)
			{
				if (i % (t / 1000) == 0)
				{
					std::cout << "[" << i << "/" << t << "]" << std::endl;
				}
				auto temp = generator.get_red_center_false_case();
				wency::user_tile a;
				a.set_user_matrix(temp.cards, 14);
				wency::win_tile cur_tile(a);
				if (cur_tile.get_result() == true)
				{
					std::cout << "Assert Failed!, index = " << i << " userArr = ";
					a.printUserArr();
					system("pause");
				}
			}
			end = clock();
			diff = end - start;
			std::cout << "The speed is: " << (float(diff) / CLK_TCK) << std::endl;

		}


		void test_kong() const
		{

			TerminalStateGenerator generator;
			const size_t t = 1000000;

			clock_t start, end, diff;
			start = clock();
			for (size_t i = 0; i < t; i++)
			{
				if (i % (t / 1000) == 0)
				{
					std::cout << "[" << i << "/" << t << "]" << std::endl;
				}
				auto temp = generator.get_kong();
				wency::user_tile a;
				a.set_user_matrix(temp.cards, 14);
				wency::win_tile cur_tile(a);
				if (cur_tile.get_result() == false)
				{
					std::cout << "Assert Failed!, index = " << i << " userArr = ";
					a.printUserArr();
					system("pause");
				}
			}
			end = clock();
			diff = end - start;
			std::cout << "The speed is: " << (float(diff) / CLK_TCK) << std::endl;

		}


		void test_kong_red_center_false_case() const
		{

			TerminalStateGenerator generator;
			const size_t t = 1000000;

			clock_t start, end, diff;
			start = clock();
			for (size_t i = 0; i < t; i++)
			{
				if (i % (t / 1000) == 0)
				{
					std::cout << "[" << i << "/" << t << "]" << std::endl;
				}
				auto temp = generator.get_kong_red_center_false();
				wency::user_tile a;
				a.set_user_matrix(temp.cards, 14);
				wency::win_tile cur_tile(a);
				if (cur_tile.get_result() == true)
				{
					std::cout << "Assert Failed!, index = " << i << " userArr = ";
					a.printUserArr();
					system("pause");
				}
			}
			end = clock();
			diff = end - start;
			std::cout << "The speed is: " << (float(diff) / CLK_TCK) << std::endl;

		}
	};
}


