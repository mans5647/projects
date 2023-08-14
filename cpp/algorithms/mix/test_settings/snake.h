#pragma once
#include <vector>
#include <windows.h>
class Snake
{
public:
	Snake() = default;
	std::vector<COORD> snake_body;
	std::size_t length = 0;
	void set_expand_false();
	void set_expand_true();
	void disable_timer();
	void set_max_size(int new_size);
	void enable_timer();
	void SetTimerTime(time_t new_time)
	{
		timer_time = new_time;
	}
	time_t & GetTimerTime()
	{
		return timer_time;
	}
	int GetSize()
	{
		return max_size;
	}
	bool exp_enabled = true;
	bool timer_enabled_public = false;
private:
	int max_size = 10;
	bool isExpandable = true;
	bool timer_enabled = false;
	time_t timer_time = 60;
};


void Snake::set_expand_false()
{
	isExpandable = false;
	exp_enabled = false;
}

void Snake::set_expand_true()
{
	isExpandable = true;
	exp_enabled = true;
}

void Snake::set_max_size(int new_size)
{
	max_size = new_size;
}

void Snake::enable_timer()
{
	timer_enabled = true;
	timer_enabled_public = true;
}
void Snake::disable_timer()
{
	timer_enabled = false;
	timer_enabled_public = false;
}
