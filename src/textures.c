#include "../include/cub3d.h"

void	assign_texture(t_vars *vars, bool *stat, char *path, int type)
{
	*stat = true;
	if (type == 3 || type == 1 || type == 2 || type == 0)
		check_texture_ext(path, vars);
	else if (type == 'F' || type == 'C')
		init_colors(path, vars, type);
	if (type >= 0 && type <= 3)
	{
		vars->tex[type].img = mlx_xpm_file_to_image(vars->mlx.mlx, path,
				&vars->tex[type].width, &vars->tex[type].height);
		if (vars->tex[type].img == NULL)
		{
			if (type == 0)
				error_exit("Error: East texture doesn't exist\n", path, vars);
			else if (type == 1)
				error_exit("Error: South texture doesn't exist\n", path, vars);
			else if (type == 2)
				error_exit("Error: West texture doesn't exist\n", path, vars);
			else if (type == 3)
				error_exit("Error: North texture doesn't exist\n", path, vars);
		}
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

	while (*counter < 6)
	{
		i = 0;
		temp2 = get_next_line(vars->map.fd);
		if (temp2 == NULL)
			return (NULL);
		temp = ft_strtrim(temp2, " \n");
		free(temp2);
		vars->map.start += 1;
		if (temp[i] == '1')
			return (temp);
		else if (is_type_texture(temp[i]))
		{
			if (!texture_path(&temp[i], vars))
				error_exit("Error: Wrong texture identifier\n", &temp[0], vars);
			*counter += 1;
		}
		else if (!is_end(temp[i], 10))
			error_exit("Error: Wrong character in texture space\n", temp, vars);
		free(temp);
	}
	return (temp);
}

void	texture_init(t_vars *vars)
{
	int		counter;
	char	*temp;

	temp = NULL;
	counter = 0;
	vars->map.start = 0;
	temp = check_texture(temp, &counter, vars);
	if (counter != 6)
		error_exit("Error: Not all texture identifier present \
			in texture zone\n", temp, vars);
	close (vars->map.fd);
}
