#include "../include/cub3d.h"

void	free_map_cpy(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->map.map_limit[1])
		free(vars->map.map_cpy[i]);
	free(vars->map.map_cpy);
}