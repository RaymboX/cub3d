#include "../include/cub3d.h"

void	texture_struct_init(t_vars *vars)
{
	vars->textures.no = NULL;
	vars->textures.so = NULL;
	vars->textures.ea = NULL;
	vars->textures.we = NULL;
	vars->textures.f_stat = false;
	vars->textures.c_stat = false;
	vars->textures.no_stat = false;
	vars->textures.so_stat = false;
	vars->textures.ea_stat = false;
	vars->textures.we_stat = false;
}
