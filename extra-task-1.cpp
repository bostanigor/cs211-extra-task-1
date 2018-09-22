#include <cmath>
#include <float.h>
#include <assert.h>

double seconds_difference(double time_1, double time_2)
{
	assert(time_1 >= 0);
	assert(time_2 >= 0);
	return time_2 - time_1;
}

double hours_difference(double time_1, double time_2)
{
	assert(time_1 >= 0);
	assert(time_2 >= 0);
	return (time_2 - time_1) / 3600;
}

int get_hours(double time)
{
	return floor(time) / 3600;
}

int get_minutes(double time)
{
	return floor(time) / 60 - get_hours(time) * 60;
}

int get_seconds(double time)
{
	return floor(time) - get_minutes(time) * 60;
}

double to_float_hours(int hours, int minutes, int seconds)
{
	assert(hours >= 0);
	assert(minutes >= 0);
	assert(seconds >= 0);
	return hours + minutes / 60 + seconds / 3600;
}

double to_24_hour_clock(double hours)
{
	assert(hours >= 0);
	return (int)floor(hours) % 24;
}

double time_to_utc(int utc_offset, double time)
{
	assert(time >= 0);
	time -= utc_offset * 3600;
	while (time >= 0)
		time -= 24 * 3600;
	return time / 3600;
}

double time_from_utc(int utc_offset, double time)
{
	assert(time >= 0);
	time += utc_offset * 3600;
	while (time >= 0)
		time -= 24 * 3600;
	return time / 3600;
}

int main()
{
	assert(seconds_difference(1800.0, 3600.0) - 1800.0 <= DBL_EPSILON);
	assert(seconds_difference(3600.0, 1800.0) + 1800.0 <= DBL_EPSILON);
	assert(seconds_difference(1800.0, 2160.0) - 360.0 <= DBL_EPSILON);
	assert(seconds_difference(1800.0, 1800.0) <= DBL_EPSILON);

	assert(hours_difference(1800.0, 3600.0) - 0.5 <= DBL_EPSILON);
	assert(hours_difference(3600.0, 1800.0) + 0.5 <= DBL_EPSILON);
	assert(hours_difference(1800.0, 2160.0) - 0.1 <= DBL_EPSILON);
	assert(hours_difference(1800.0, 1800.0) <= DBL_EPSILON);

	assert(to_float_hours(0, 15, 0) - 0.25 <= DBL_EPSILON);
	assert(to_float_hours(2, 45, 9) - 2.7525 <= DBL_EPSILON);
	assert(to_float_hours(1, 0, 36) - 1.01 <= DBL_EPSILON);

	assert(to_24_hour_clock(24) - 0 <= DBL_EPSILON);
	assert(to_24_hour_clock(48) - 0 <= DBL_EPSILON);
	assert(to_24_hour_clock(25) - 1 <= DBL_EPSILON);
	assert(to_24_hour_clock(4) - 4 <= DBL_EPSILON);
	assert(to_24_hour_clock(28.5) - 4.5 <= DBL_EPSILON);

	assert(get_hours(3800) == 1);
	assert(get_minutes(3800) == 3);

	assert(time_to_utc(+0, 12.0) - 12.0 <= DBL_EPSILON);
	assert(time_to_utc(+1, 12.0) - 11.0 <= DBL_EPSILON);
	assert(time_to_utc(-1, 12.0) - 13.0 <= DBL_EPSILON);
	assert(time_to_utc(-11, 18.0) - 5.0 <= DBL_EPSILON);
	assert(time_to_utc(-1, 0.0) - 1.0 <= DBL_EPSILON);
	assert(time_to_utc(-1, 23.0) - 0.0 <= DBL_EPSILON);
}