#include "../include/cub3d.h"

void	draw_perso(t_vars *vars)
{
	float	pos_x;
	float	pos_y;
	int		i;
	int		ii;
	float	ratio_x;
	float	ratio_y;
	float	limit;

	limit = vars->map.map_limit[0] * MINIMAPSIZE;
	if (vars->map.map_limit[1] >= vars->map.map_limit[0])
		limit = vars->map.map_limit[1] * MINIMAPSIZE;
	ratio_y = SCREEN_H / limit;
	ratio_x = SCREEN_W / limit;
	pos_x = vars->perso.position[0] / MAPSCALE;
	pos_x *= ratio_x;
	pos_x -= ratio_x / 2;
	pos_x += ratio_x * 2.5;
	pos_y = vars->perso.position[1] / MAPSCALE;
	pos_y *= ratio_y;
	pos_y -= ratio_y / 2;
	pos_y += ratio_y * 2.5;
	i = 0;
	while (++i < ratio_y)
	{
		ii = 0;
		while (ii < ratio_x)
		{
			my_mlx_pixel_put(vars, pos_x + ii, pos_y + i,
				create_trgb(1, 0, 255, 0));
			ii++;
		}
	}
}

void	draw_map(t_vars *vars)
{
	int	i;
	int	ii;
	int	x;
	int	y;
	float	limit;

	limit = vars->map.map_limit[0] * MINIMAPSIZE;
	if (vars->map.map_limit[1] >= vars->map.map_limit[0])
		limit = vars->map.map_limit[1] * MINIMAPSIZE;
	i = 1;
	while (++i < vars->map.map_limit[1] + 2)
	{
		y = i * (SCREEN_H / limit);
		while (y < (i + 1) * (SCREEN_H / limit))
		{
			ii = 1;
			while (ii < vars->map.map_limit[0] + 2)
			{			
				x = ii * (SCREEN_W / limit);
				while (x < (ii + 1) * (SCREEN_W / limit))
				{
					if (vars->map.map[i - 2][ii - 2] == '1')
						my_mlx_pixel_put(vars, x, y, 0000);
					else if (vars->map.map[i - 2][ii - 2] == '0'
						|| is_startchar(vars->map.map[i - 2][ii - 2]))
						my_mlx_pixel_put(vars, x, y,
							create_trgb(0, 255, 255, 255));
					x++;
				}
				ii++;
			}
			y++;
		}
	}
}