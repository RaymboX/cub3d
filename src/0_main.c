#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc == 2)
	{
		texture_struct_init(&vars);
		check_file(argv, &vars);
	}
	return (0);
}