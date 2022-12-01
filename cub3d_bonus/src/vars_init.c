#include "../include/cub3d.h"

void	vars_init(t_vars *vars)
{
	vars->tex[0].img = NULL;
	vars->tex[1].img = NULL;
	vars->tex[2].img = NULL;
	vars->tex[3].img = NULL;
	vars->tex[0].stat = false;
	vars->tex[1].stat = false;
	vars->tex[2].stat = false;
	vars->tex[3].stat = false;
	vars->map.is_map = false;
	vars->map.map = NULL;
	vars->map.map_cpy = NULL;
}
