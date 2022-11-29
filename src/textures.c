#include "../include/cub3d.h"

void	assign_texture(t_vars *vars, bool *stat, char *path, char type)
{
	*stat = true;
	if (type == 'N' || type == 'S' || type == 'W' || type == 'E')
		check_texture_ext(path, vars);
	else if (type == 'F' || type == 'C')
		init_colors(path, vars, type);
	if (type == 'E')
	{
		vars->textures[0].img = mlx_xpm_file_to_image(vars->mlx_vars.mlx, path, &vars->textures[0].width, &vars->textures[0].height);
		if (vars->textures[0].img == NULL)
			error_exit("Error: East texture doesn't exist\n", path, vars);
	}
	else if (type == 'S')
	{
		vars->textures[1].img = mlx_xpm_file_to_image(vars->mlx_vars.mlx, path, &vars->textures[1].width, &vars->textures[1].height);
		if (vars->textures[1].img == NULL)
			error_exit("Error: South texture doesn't exist\n", path, vars);
	}
	else if (type == 'W')
	{
		vars->textures[2].img = mlx_xpm_file_to_image(vars->mlx_vars.mlx, path, &vars->textures[2].width, &vars->textures[2].height);
		if (vars->textures[2].img == NULL)
			error_exit("Error: West texture doesn't exist\n", path, vars);
	}
	else if (type == 'N')
	{
		vars->textures[3].img = mlx_xpm_file_to_image(vars->mlx_vars.mlx, path, &vars->textures[3].width, &vars->textures[3].height);
		if (vars->textures[3].img == NULL)
			error_exit("Error: North texture doesn't exist\n", path, vars);
	}
	else if (type == 'C')
		vars->cnf.c = ft_strdup(path);
	else if (type == 'F')
		vars->cnf.f = ft_strdup(path);
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
	path = NULL;
	return (r);
}

char	*check_texture(char *temp, int *counter, t_vars *vars)
{
	int		i;
	char	*temp2;

	while (1)
	{
		i = 0;
		temp2 = get_next_line(vars->map.fd);
		if (temp2 == NULL)
			return (NULL);
		temp = ft_strtrim(temp2, " \n");
		free(temp2);
		vars->map.start += 1;
		if (temp[i] == '1')
			return (NULL);
		else if (is_type_texture(temp[i]))
		{
			if (!texture_path(&temp[i], vars))
				error_exit("Error: Wrong texture identifier\n", &temp[0], vars);
			*counter += 1;
			if (*counter == 6)
				return (temp);
		}
		else if (!is_end(temp[i], 10))
			error_exit("Error: Wrong character in texture's space\n",
				temp, vars);
		free(temp);
	}
	return (NULL);
}

void	texture_init(t_vars *vars)
{
	int		counter;
	char	*temp;

	temp = NULL;
	counter = 0;
	vars->map.start = 0;
	temp = check_texture(temp, &counter, vars);
	if (temp)
		free(temp);
	if (counter != 6)
		error_exit("Error: Not all texture identifier present in texture zone\n", temp, vars);
}
