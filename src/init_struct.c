#include "../include/cub3d.h"

void	texture_struct_init(t_vars *vars)
{
	vars->textures[0].img = NULL;
	vars->textures[1].img = NULL;
	vars->textures[2].img = NULL;
	vars->textures[3].img = NULL;
	vars->textures[0].stat = false;
	vars->textures[1].stat = false;
	vars->textures[2].stat = false;
	vars->textures[3].stat = false;
}
