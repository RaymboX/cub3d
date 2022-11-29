#include "../include/cub3d.h"

bool	is_seperator(char c, bool *is_virg)
{
	if (c == ',' && *is_virg == true)
		print_error("Error: Wrong color format\n");
	if (c == ' ' || c == ',')
	{
		if (c == ',')
			*is_virg = true;
		return (true);
	}
	return (false);
}

void	check_last_color(char *colors, int *i, int counter, bool *is_virg)
{
	*is_virg = false;
	if (!is_seperator(colors[*i], is_virg) && !is_end(colors[*i], counter))
		print_error("Error: Wrong color format\n");
	if (*is_virg == true && counter == 2)
		print_error("Error: Wrong color format\n");
	if (!is_end(colors[*i], counter))
		*i += 1;
	*is_virg = true;
	while (is_seperator(colors[*i], is_virg))
			*i += 1;
	if (!is_end(colors[*i], counter) && counter == 2)
		print_error("Error: Wrong color format\n");
}

void	check_colors(char *colors, char *nb, int *i, int counter)
{
	int		ii;
	bool	is_virg;

	is_virg = false;
	ii = 0;
	if (!is_seperator(colors[*i], &is_virg) && !ft_isdigit(colors[*i]))
		print_error("Error: Wrong color format\n");
	if (is_virg == true && counter == 0)
		print_error("Error: Wrong color format\n");
	if (is_virg == true)
		*i += 1;
	while (is_seperator(colors[*i], &is_virg))
		*i += 1;
	while (ft_isdigit(colors[*i]))
	{
		nb[ii] = colors[*i];
		*i += 1;
		ii++;
	}
	if (ft_is_int_range(nb, 0, 255))
		print_error("Error: Color out of range\n");
	check_last_color(colors, i, counter, &is_virg);
}

void	init_colors(char *colors, t_vars *vars, char type)
{
	int		i;
	int		counter;
	char	*nb;

	i = 0;
	counter = 0;
	while (counter < 3)
	{
		nb = ft_calloc(sizeof(char), 4);
		check_colors(colors, nb, &i, counter);
		if (type == 'C')
			vars->cnf.c_colors[counter] = ft_atoi(nb);
		else if (type == 'F')
			vars->cnf.f_colors[counter] = ft_atoi(nb);
		counter++;
		free(nb);
	}
}