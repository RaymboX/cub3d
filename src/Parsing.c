#include "../include/cub3d.h"

void	check_texture_ext(char *texture, t_vars *vars)
{
	char	*res;
	char	*res2;

	res = ft_strtrim(texture, " ");
	res2 = ft_strrchr(&res[1], '.');
	if (res2 == NULL)
	{
		free(res);
		error_exit("Error: No extension found\n", texture, vars);
	}
	if (*(res2 + 1) == 'x' && *(res2 + 2) == 'p'
		&& *(res2 + 3) == 'm' && is_end(*(res2 + 4), 10))
	{
		if (*texture != '.' && *(texture + 1) != '/')
		{
			free(res);
			error_exit("Error: File not in good directory\n", texture, vars);
		}
		free(res);
		return ;
	}
	free(res);
	error_exit("Error: Texture file is not a '.xpm'\n", texture, vars);
}

void	check_ext(char *arg)
{
	char	*res;

	res = ft_strrchr(arg, '.');
	if (res == NULL)
		print_error("Error: No extension found\n");
	if (*(res + 1) == 'c' && *(res + 2) == 'u'
		&& *(res + 3) == 'b' && *(res + 4) == '\0')
		return ;
	print_error("Error: Extension is not '.cub'\n");
}

void	find_first_wall(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->map.map_limit[0])
	{
		if (vars->map.map[0][i] == '1')
			break ;
		i++;
	}
	vars->map.first_wall = i;
}

void	check_inside_rooms(t_vars *vars)
{
	int	i;
	int	ii;

	i = 0;
	while (i < vars->map.map_limit[1])
	{
		ii = 0;
		while (vars->map.map_cpy[i][ii])
		{
			if (vars->map.map_cpy[i][ii] == '1'
				|| vars->map.map_cpy[i][ii] == '0')
				flood_fill_inside_rooms(vars, i, ii, vars->map.map_cpy[i][ii]);
			ii++;
		}
		i++;
	}
}

void	get_img_addr(t_vars *vars)
{
	vars->textures[0].addr = mlx_get_data_addr(vars->textures[0]. img,
			&vars->textures[0].bpp, &vars->textures[0].size_line,
			&vars->textures[0].endian);
	vars->textures[1].addr = mlx_get_data_addr(vars->textures[1]. img,
			&vars->textures[1].bpp, &vars->textures[1].size_line,
			&vars->textures[1].endian);
	vars->textures[2].addr = mlx_get_data_addr(vars->textures[2]. img,
			&vars->textures[2].bpp, &vars->textures[2].size_line,
			&vars->textures[2].endian);
	vars->textures[3].addr = mlx_get_data_addr(vars->textures[3]. img,
			&vars->textures[3].bpp, &vars->textures[3].size_line,
			&vars->textures[3].endian);
}

void	set_starting_point(t_vars *vars)
{
	int	i;
	int	ii;

	i = -1;
	while (++i < vars->map.map_limit[1])
	{
		ii = 0;
		while (vars->map.map[i][ii])
		{
			if (vars->map.map[i][ii] == 'W' || vars->map.map[i][ii] == 'N'
				|| vars->map.map[i][ii] == 'E' || vars->map.map[i][ii] == 'S')
			{
				if (vars->map.map[i][ii] == 'E')
					vars->perso.angle = 0;
				else if (vars->map.map[i][ii] == 'S')
					vars->perso.angle = 90;
				else if (vars->map.map[i][ii] == 'W')
					vars->perso.angle = 180;
				else if (vars->map.map[i][ii] == 'N')
					vars->perso.angle = 270;
				break ;
			}
			ii++;
		}
	}
}

void	check_file(char **av, t_vars *vars)
{
	vars->map.fd = -1;
	check_ext(av[1]);
	vars->map.fd = open(av[1], O_RDONLY);
	texture_init(vars);
	vars->map.fd = open(av[1], O_RDONLY);
	ft_map_start(vars);
	vars->map.fd = open(av[1], O_RDONLY);
	map_size(vars);
	vars->map.fd = open(av[1], O_RDONLY, 0777);
	create_map(vars);
	check_map_errors(vars);
	copy_map(vars);
	flood_fill_inside(vars, vars->map.perso_start[1], vars->map.perso_start[0]);
	find_first_wall(vars);
	flood_fill_walls(vars, 0, vars->map.first_wall);
	check_inside_rooms(vars);
	check_map_integrity(vars);
	free_map(vars, vars->map.map_cpy);
	get_img_addr(vars);
	set_starting_point(vars);
}
