#include "../include/cub3d.h"

void	error_exit(char *error, char *temp, t_vars *vars)
{
	if (vars->map.fd >= 0)
		close(vars->map.fd);
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	if (vars->tex[0].img)
		free(vars->tex[0].img);
	if (vars->tex[1].img)
		free(vars->tex[1].img);
	if (vars->tex[2].img)
		free(vars->tex[2].img);
	if (vars->tex[3].img)
		free(vars->tex[3].img);
	if (vars->map.map)
		free_map(vars, vars->map.map);
	if (vars->map.map_cpy)
		free_map(vars, vars->map.map_cpy);
	print_error(error);
}

void	print_error(char *error)
{
	ft_putstr_fd(error, 2);
	exit(1);
}

int	end_program(t_vars *vars)
{
	if (vars->map.fd >= 0)
		close(vars->map.fd);
	if (vars->tex[0].img)
		free(vars->tex[0].img);
	if (vars->tex[1].img)
		free(vars->tex[1].img);
	if (vars->tex[2].img)
		free(vars->tex[2].img);
	if (vars->tex[3].img)
		free(vars->tex[3].img);
	if (vars->map.map)
		free_map(vars, vars->map.map);
	exit(0);
}

void	free_map(t_vars *vars, char **map)
{
	int	i;

	i = -1;
	while (++i < vars->map.map_limit[1])
		free(map[i]);
	free(map);
}