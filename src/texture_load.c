#include "include/cub3d.h"

void	load_texture(t_vars *vars)
{
	char	*xpm_path[4];
	int		i;

	transfert_xpm_path(vars, xpm_path);
	
	i = -1;
	while (++i < 4 && test_path(vars, xpm_path[i], i) != -1)
	{
		
	}
	
	//for each texture
	//test path
	//load limit
	//load nb_color
	//nbchar par couleur
	//malloc char
	//malloc color
	//extract color to int (trgb fonction)
	//extract map
}

void	transfert_xpm_path(t_vars *vars, char *xpm_path[4])
{
	xpm_path[0] = vars->textures.e;
	xpm_path[1] = vars->textures.s;
	xpm_path[2] = vars->textures.w;
	xpm_path[3] = vars->textures.n;

}

int	test_path(t_vars *vars, char *path, int i)
{
	vars->wall_t[i].fd = open(path, O_RDONLY);
	if ()
	return (vars->wall_t[i].fd);
}