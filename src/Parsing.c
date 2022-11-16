#include "../include/cub3d.h"

//Essayer d'open tous les fichiers textures voir si ils existent
//Parser les extensions des fichier voir s'il s'agi d'un fichier xpm
//Parser les couleurs

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

void	check_file(char **av, t_vars *vars)
{
	int		fd;

	check_ext(av[1]);
	fd = open(av[1], O_RDONLY);
	texture_init(fd, vars);
	fd = open(av[1], O_RDONLY);
	ft_map_start(fd, vars);
	fd = open(av[1], O_RDONLY);
	map_size(fd, vars);
	fd = open(av[1], O_RDONLY, 0777);
	create_map(fd, vars);
	check_map_errors(vars);
	copy_map(vars);
	flood_fill_inside(vars, vars->map.perso_start[1], vars->map.perso_start[0]);
	find_first_wall(vars);
	flood_fill_walls(vars, 0, vars->map.first_wall);
	check_map_integrity(vars);
}
