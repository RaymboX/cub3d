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

bool	is_type_texture(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E'
		|| c == 'F' || c == 'C')
		return (true);
	return (false);
}

bool	is_end(char c, int counter)
{
	if ((c == '\0' || c == '\n') && counter < 2)
		print_error("Error: Wrong color format\n");
	if (c == '\0' || c == '\n')
		return (true);
	return (false);
}

bool	identify_texture(t_vars *vars, char *path, char *temp)
{
	if (temp[0] == 'N' && temp[1] == 'O' && temp[2] == ' '
		&& !vars->textures[3].stat)
		assign_texture(vars, &vars->textures[3].stat, path, 'N');
	else if (temp[0] == 'S' && temp[1] == 'O' && temp[2] == ' '
		&& !vars->textures[1].stat)
		assign_texture(vars, &vars->textures[1].stat, path, 'S');
	else if (temp[0] == 'W' && temp[1] == 'E' && temp[2] == ' '
		&& !vars->textures[2].stat)
		assign_texture(vars, &vars->textures[2].stat, path, 'W');
	else if (temp[0] == 'E' && temp[1] == 'A' && temp[2] == ' '
		&& !vars->textures[0].stat)
		assign_texture(vars, &vars->textures[0].stat, path, 'E');
	else if (temp[0] == 'F' && temp[1] == ' ' && !vars->cnf.f_stat)
		assign_texture(vars, &vars->cnf.f_stat, path, 'F');
	else if (temp[0] == 'C' && temp[1] == ' ' && !vars->cnf.c_stat)
		assign_texture(vars, &vars->cnf.c_stat, path, 'C');
	else
		return (false);
	return (true);
}
