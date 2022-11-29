#include "../include/cub3d.h"

void	assign_texture(t_vars *vars, bool *stat, char *path, char type)
{
	//void	*ptr;
	*stat = true;
	if (type == 'N' || type == 'S' || type == 'W' || type == 'E')
		check_texture_ext(path);
	else if (type == 'F' || type == 'C')
		init_colors(path, vars, type);
	
	/*
	
	SEGFAULT SECTION


	//ptr = mlx_xpm_file_to_image(&vars->mlx_vars.mlx, path, &vars->textures.width, &vars->textures.height);

	if (type == 'N')
	{
		//vars->textures.n = mlx_get_data_addr(ptr, &vars->textures.bpp, &vars->textures.size_line, &vars->textures.endian);
		vars->textures.n = mlx_xpm_file_to_image(&vars->mlx_vars.mlx, path, &vars->textures.width, &vars->textures.height);
		if (vars->textures.n == NULL)
			error_exit("Error: North texture doesn't exist\n", -1, path, vars);
	}
	else if (type == 'S')
	{
		//vars->textures.s = mlx_get_data_addr(ptr, &vars->textures.bpp, &vars->textures.size_line, &vars->textures.endian);
		vars->textures.s = mlx_xpm_file_to_image(&vars->mlx_vars.mlx, path, &vars->textures.width, &vars->textures.height);
		if (vars->textures.s == NULL)
			error_exit("Error: South texture doesn't exist\n", -1, path, vars);
	}
	else if (type == 'W')
	{
		//vars->textures.w = mlx_get_data_addr(ptr, &vars->textures.bpp, &vars->textures.size_line, &vars->textures.endian);
		vars->textures.w = mlx_xpm_file_to_image(&vars->mlx_vars.mlx, path, &vars->textures.width, &vars->textures.height);
		if (vars->textures.w == NULL)
			error_exit("Error: West texture doesn't exist\n", -1, path, vars);
	}
	else if (type == 'E')
	{
		//vars->textures.e = mlx_get_data_addr(ptr, &vars->textures.bpp, &vars->textures.size_line, &vars->textures.endian);
		vars->textures.e = mlx_xpm_file_to_image(&vars->mlx_vars.mlx, path, &vars->textures.width, &vars->textures.height);
		if (vars->textures.e == NULL)
			error_exit("Error: East texture doesn't exist\n", -1, path, vars);
	}
	else if (type == 'C')
		vars->textures.c = ft_strdup(path);
	else if (type == 'F')
		vars->textures.f = ft_strdup(path);
	
	*/
}

bool	ft_avance_in_file(int *ii, char *temp)
{
	while (temp[*ii] != ' ')
	{
		*ii += 1;
		if (temp[*ii] == '\0' || temp[*ii] == '\n')
			return (0);
	}
	while (temp[*ii] == ' ')
	{
		*ii += 1;
		if (temp[*ii] == '\0' || temp[*ii] == '\n')
			return (0);
	}
	return (1);
}

bool	texture_path(char *temp, t_vars *vars)
{
	int		ii;
	bool	r;
	char	*path;

	ii = 0;
	if (!ft_avance_in_file(&ii, temp))
		return (0);
	path = ft_calloc(ft_strlen_nl(&temp[ii]) + 1, sizeof(char));
	ft_strlcpy(path, &temp[ii], ft_strlen_nl(&temp[ii]) + 1);
	r = identify_texture(vars, path, temp);
	free(path);
	return (r);
}

void	check_texture(char *temp, int fd, int *counter, t_vars *vars)
{
	int	i;

	while (1)
	{
		i = 0;
		temp = ft_strtrim(get_next_line(fd), " \n");
		if (temp == NULL)
			return ;
		vars->map.start += 1;
		if (temp[i] == '1')
			return ;
		else if (is_type_texture(temp[i]))
		{
			if (texture_path(&temp[i], vars) != 1)
				error_exit("Error: Wrong texture identifier\n", fd, temp, vars);
			*counter += 1;
			if (*counter == 6)
				return ;
		}
		else if (!is_end(temp[i], 10))
			error_exit("Error: Wrong character in texture's space\n",
				fd, temp, vars);
		free(temp);
	}
}

void	texture_init(int fd, t_vars *vars)
{
	int		counter;
	char	*temp;

	temp = NULL;
	counter = 0;
	vars->map.start = 0;
	check_texture(temp, fd, &counter, vars);
	if (temp)
		free(temp);
	if (counter != 6)
		error_exit("Error: Not all texture identifier present in texture zone\n", fd, temp, vars);
}
