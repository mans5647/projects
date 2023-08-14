#include <windows.h>
#include <conio.h>
#include <iostream>
#include <ctime>
#include <utility>
#include <thread>
#include <string>
#include "snake.h"
#include "clock.h"

#define WIDTH 50
#define HEIGTH 20
#define ALWAYS_STEADY_BY_X 40

#define RESET_POSITION() SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});

void timer(time_t * seconds)
{
	if (*seconds == 0) return;
	auto time = to_clock(*seconds);
	unsigned h = time.GetHours(), m = time.GetMinutes(), s = time.GetSeconds();
	bool hours_passed = false, minutes_passed = false, disabled_extra = true;
	if (*seconds <= 60)
	{
		h = 0;
		m = 0;
		hours_passed = true, minutes_passed = true;
		s = *seconds;
	}
	
	bool full_time = false;
	while (!full_time)
	{
		if (*seconds == 0) full_time = true;
		if (s == 0)
		{
			if (m != 0)
			{
				--m;
				s = 60;
			}
		}
		if (m == 0)
		{
			if (h != 0)
			{
				--h;
				m = 59;
				s = 60;
			}
			
		}
		--*(seconds);
		std::cout << h << " hours " << m << " minutes " << s-- << " seconds\r";
		Sleep(1000);
	}
}

COORD get_food()
{
	COORD xy;
	xy.X = (std::rand() % WIDTH - 1) + 1;
	xy.Y = (std::rand() % HEIGTH - 1) + 1;
	return xy;
}

bool check_borders(COORD & snake_pos)
{
	return ((snake_pos.X < 1 || snake_pos.X > WIDTH) || (snake_pos.Y < 1 || snake_pos.Y > HEIGTH)) ? true : false;
}

void set_pos(COORD & pos)
{
	auto var = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(var, pos);
}

void field(COORD & snake_pos, COORD & food_pos, int * current_score, Snake & snake)
{
	std::cout << " ---- CURRENT SCORE: " << *current_score << " points\n\n\n";
	std::cout << "Food position: " << food_pos.X << " " << food_pos.Y << "\n";
	for (auto i = 0u; i < HEIGTH; i++)
	{
		std::cout << "\t\t#";
		for (auto j = 0u; j < WIDTH; j++)
		{
			if (i == 0 || i == HEIGTH - 1) std::cout << '#';
			else if (i == food_pos.Y && j == food_pos.X) std::cout << '%';
			else if (i == snake_pos.Y && j == snake_pos.X)
			{
				std::cout << '@';
			}
			else
			{
				bool bodyPart = false;
				for (auto k : snake.snake_body)
				{
					if (i == k.Y && j == k.X)
					{
						std::cout << '*';
						bodyPart = true;
						break;
					}
				}

				if (!bodyPart) std::cout << ' ';

			}
		}
		std::cout << "#\n";
		
	}
}

void Start_Game(Snake & snake)
{

	bool ate = false, finished = false;
	auto new_food = get_food();
	COORD snake_pos, field_pos;
	field_pos.X = 0;
	field_pos.Y = 0;
	snake_pos.X = 10;
	snake_pos.Y = 10;
	snake.snake_body.push_back(snake_pos);
	int current_score = 0;
	snake.length = 0;
	std::srand((unsigned)time(NULL));
	std::thread th(timer, &(snake.GetTimerTime()));
	th.detach();
	while (1)
	{
		if (finished) break;
		char key = _getch();
		switch (key)
		{
		case 'w':
		{
			snake_pos.Y -= 1;
			break;
		}
		case 's':
		{
			snake_pos.Y += 1;
			break;
		}
		case 'a':
		{
			snake_pos.X -= 1;
			break;
		}
		case 'd':
		{
			snake_pos.X += 1;
			break;
		}
		}
		snake.snake_body.push_back(snake_pos);
		if (snake.snake_body.size() > snake.length)
		{
			snake.snake_body.erase(snake.snake_body.begin());
		}
		if ((check_borders(snake_pos)) || (snake.GetTimerTime() == 0))
		{
			
			break;
		}
		if (snake_pos.Y > HEIGTH || snake_pos.Y < 1)
		{
			snake_pos.Y = HEIGTH - 1;
		}
		if (snake_pos.X > WIDTH || snake_pos.X < 1)
		{
			snake_pos.X = WIDTH - 1;
		}
		if (ate)
		{
			new_food = get_food();
			ate = false;
		}
		if (snake_pos.Y == new_food.Y && snake_pos.X == new_food.X)
		{
			ate = true;
			current_score += 1;
			snake.snake_body.push_back(snake_pos);
			++snake.length;
		}
		std::system("cls");
		field(snake_pos, new_food, &current_score, snake);
		
		
	}
	std::cout << "Game over!!!";
}


void SetText(COORD location, const char* text)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), location);
	std::cout << text;
}

void EditSettings(Snake & snake)
{
	std::system("cls");
	bool menu_return = false;
	char key = NULL;
	COORD settings_coord;
	int act = 9999;
	settings_coord.X = ALWAYS_STEADY_BY_X;
	settings_coord.Y = 10;

	while (!menu_return)
	{
		key = _getch();
		switch (key)
		{
		case 'w':
		{
			settings_coord.Y -= 1;
			break;
		}
		case 's':
		{
			settings_coord.Y += 1;
			break;
		}
		case 13:
		{
			// enabling settings
			if (act == 1)
			{
				if (snake.exp_enabled)
				{
					snake.set_expand_false();
				}
				else
				{
					snake.set_expand_true();
				}
			}
			else if (act == 2)
			{
				std::system("cls");
				
				bool exit_from_set_ = false;
				char control = NULL;
				int total = 0;
				std::string str_time;
				while (!exit_from_set_)
				{
					control = _getch();
					switch (control)
					{
					case 'a':
					{
						--total;
						break;
					}
					case 'd':
					{
						++total;
						break;
					}
					case 27:
					{
						exit_from_set_ = true;
						break;
					}
					case 13:
					{
						if (total == 0)
						{
							total = 1;
						}
						snake.set_max_size(total);
						exit_from_set_ = true;
						break;
					}
					}
					if (total < 0)
					{
						total = 0;
					}
					else if (total > 50)
					{
						total = 50;
					}
					std::system("cls");
					str_time = "\t < " + std::to_string(total) + " > ";
					SetText({ ALWAYS_STEADY_BY_X, 9 }, " --- BODY LENGTH --- \n");
					SetText({ ALWAYS_STEADY_BY_X, 10 }, str_time.c_str());
				}
			}
			else if (act == 3)
			{
				if (snake.timer_enabled_public)
				{
					snake.disable_timer();
				}
				else
				{
					snake.enable_timer();
				}
			}
			else if (act == 4)
			{
				std::system("cls");
				bool exit_from_setting = false;
				time_t maximum_time = 0;
				char key = NULL;
				std::string str_time;
				while (!exit_from_setting)
				{
					key = _getch();
					switch (key)
					{
					case 'a':
					{
						--maximum_time;
						break;
					}
					case 'd':
					{
						++maximum_time;
						break;
					}
					case 13:
					{
						if (maximum_time == 0) maximum_time = 60;
						snake.SetTimerTime(maximum_time);
						exit_from_setting = true;
						break;
					}
					case 27:
					{
						if (maximum_time == 0) maximum_time = 60;
						snake.SetTimerTime(maximum_time);
						exit_from_setting = true;
						break;
					}
					}
					if (maximum_time < 0)
					{
						maximum_time = 0;
					}
					else if (maximum_time > 300)
					{
						maximum_time = 300;
					}
					std::system("cls");
					str_time = ("\t < " + std::to_string(maximum_time) + " > ");
					SetText({ ALWAYS_STEADY_BY_X, 9 }, " --- SET TIMER TIME --- \n");
					SetText({ ALWAYS_STEADY_BY_X, 10 }, str_time.c_str());

				}
			}
			break;
		}
		case 27:
		{
			return;
		}
		}
		if (settings_coord.Y == 10) act = 1;
		else if (settings_coord.Y == 11) act = 2;
		else if (settings_coord.Y == 12) act = 3;
		else if (settings_coord.Y == 13) act = 4;
		if (settings_coord.Y < 10)
		{
			settings_coord.Y = 10;
		}
		else if (settings_coord.Y > 13)
		{
			settings_coord.Y = 13;
		}
		std::system("cls");
		std::string what_text = (snake.exp_enabled) ? "\t1. Disable expansion\n" : "\t1. Enable expansion\n";
		std::string timer_st = (snake.timer_enabled_public) ? "\t3. Disable timer\n" : "\t3. Enable timer\n";
		SetText({ ALWAYS_STEADY_BY_X, 10 }, what_text.c_str());
		SetText({ ALWAYS_STEADY_BY_X, 11 }, "\t2. Set snake's body length\n");
		SetText({ ALWAYS_STEADY_BY_X, 12 }, timer_st.c_str());
		SetText({ ALWAYS_STEADY_BY_X, 13 }, "\t4. Set timer time\n");
		set_pos(settings_coord);
		std::cout << '>';
	}
}

void Menu()
{
	Snake snake;
	int action = 1;
	COORD only_up;
	only_up.X = ALWAYS_STEADY_BY_X;
	only_up.Y = 10;
	char act = NULL;
	bool exitApproved = false;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), only_up);
	while (!exitApproved)
	{
		
		act = _getch();
		switch (act)
		{
		case 'w':
		{
			only_up.Y -= 1;
			break;
		}
		case 's':
		{
			only_up.Y += 1;
			break;
		}
		case 13:
		{
			if (action == 1)
			{
				Start_Game(snake);
			}
			else if (action == 2)
			{
				EditSettings(snake);
			}
			else if (action == 3)
			{
				exitApproved = true;
			}
			break;
		}
		}
		if (only_up.Y == 10)
		{
			action = 1;
		}
		else if (only_up.Y == 11)
		{
			action = 2;
		}
		else if (only_up.Y == 12)
		{
			action = 3;
		}
		if (only_up.Y < 10)
		{
			only_up.Y = 10;
		}
		else if (only_up.Y > 12)
		{
			only_up.Y = 12;
		}
		std::system("cls");
		SetText({ 40, 10 }, "\t1. Play\n");
		SetText({ 40, 11 }, "\t2. Settings\n");
		SetText({ 40, 12 }, "\t3. Quit\n");
		set_pos(only_up);
		std::cout << '>';

	}
	
	
}


int main()
{
	Menu();
	return 0;
}