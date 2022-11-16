#include "../include/cub3d.h"

bool	is_mapchar(char c)
{
	if (c == ' ' || c == '0' || c == '1'
		|| c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (true);
	return (false);
}

bool	is_startchar(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (true);
	return (false);
}