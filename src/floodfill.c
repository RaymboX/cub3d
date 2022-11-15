#include "../include/cub3d.h"

void	flood_fill(t_vars *vars, int x, int y)
{
	int	i;

	i = -1;
	if (vars->map.map_cpy[x][y] != '1' && vars->map.map_cpy[x][y] != 'F')
	{
		if (vars->map.map_cpy[x][y] != '0' && vars->map.map_cpy[x][y] != 'N'
			&& vars->map.map_cpy[x][y] != 'E' && vars->map.map_cpy[x][y] != 'S'
			&& vars->map.map_cpy[x][y] != 'W' && vars->map.map_cpy[x][y] != 'F'
			&& vars->map.map_cpy[x][y] != '1')
			print_error("Error: Map is not enclosed by walls/Spaces in map/Starting point out of bound\n");
		vars->map.map_cpy[x][y] = 'F';
		while (++i < vars->map.map_limit[1])
			printf("%s\n", vars->map.map_cpy[i]);
		flood_fill(vars, x + 1, y);
		flood_fill(vars, x, y + 1);
		flood_fill(vars, x - 1, y);
		flood_fill(vars, x, y - 1);
	}
	return ;
}
