#pragma once
#include <cstdint>
#include <ctime>


struct Clock
{
public:
	Clock(uint32_t s, uint32_t m, uint32_t h) : seconds(s), minutes(m), hours(h) {}
	
	uint32_t GetSeconds() { return seconds; }
	uint32_t GetMinutes() { return minutes; }
	uint32_t GetHours() { return hours; }
private:
	uint32_t seconds;
	uint32_t minutes;
	uint32_t hours;

};


static Clock make_time(uint32_t s, uint32_t m, uint32_t h)
{
	return Clock(s, m, h);
}

Clock to_clock(time_t rawtime)
{
	auto hours = (double)rawtime / 3600.00;
	auto full_part = (long)hours;
	auto hours_fract = hours - (long)hours;
	auto min = hours_fract * 60.00;
	auto full_min_part = (long)min;
	auto min_fract = min - (long)min;
	auto sec = min_fract * 60;
	return make_time((unsigned)sec, (unsigned)min, (unsigned)hours);
}