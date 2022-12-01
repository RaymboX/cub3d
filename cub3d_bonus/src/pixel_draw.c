#include "../include/cub3d.h"

void	draw_wall(t_vars *vars, int i_resol[2], int pixel_h)
{
	char	*color;
	int		x;
	int		y;
	int		pos;

	x = xpm_x(vars);
	y = xpm_y(vars, pixel_h, 1);
	pos = y * vars->tex[vars->raycast.cardinal_wall].line_len + x
		* (vars->tex[vars->raycast.cardinal_wall].bpp / 8);
	color = &vars->tex[vars->raycast.cardinal_wall].addr[pos];
	my_mlx_pixel_put_walls(vars,
		vars->screen.center_pixel_w + vars->raycast.ray_i + i_resol[0],
		vars->screen.center_pixel_h + pixel_h,
		color);
	y = xpm_y(vars, pixel_h, -1);
	pos = y * vars->tex[vars->raycast.cardinal_wall].line_len + x
		* (vars->tex[vars->raycast.cardinal_wall].bpp / 8);
	color = &vars->tex[vars->raycast.cardinal_wall].addr[pos];
	my_mlx_pixel_put_walls(vars,
		vars->screen.center_pixel_w + vars->raycast.ray_i + i_resol[0],
		vars->screen.center_pixel_h - pixel_h,
		color);
}

//dessine le plafond et le sol
void	draw_floor_celling(t_vars *vars, int i_resol[2], int pixel_h)
{
	my_mlx_pixel_put(vars,
		vars->screen.center_pixel_w + vars->raycast.ray_i + i_resol[0],
		vars->screen.center_pixel_h + pixel_h,
		create_trgb(0, 0, 102, 0));
	my_mlx_pixel_put(vars,
		vars->screen.center_pixel_w + vars->raycast.ray_i + i_resol[0],
		vars->screen.center_pixel_h - pixel_h,
		create_trgb(0, 0, 255, 255));
}

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

//boucle principal de dessin sur image
void	drawing(t_vars *vars, t_raycast *rc)
{
	int	pixel_h;
	int	i_resol[2];

	wall_pixel_height(vars, &vars->raycast);
	i_resol[0] = -1;
	while (++i_resol[0] < vars->screen.resolution_w
		&& vars->screen.center_pixel_w + rc->ray_i + i_resol[0] < SCREEN_W)
	{
		pixel_h = 0;
		while (pixel_h < (vars->screen.max_height - 1) / 2)
		{
			if (pixel_h < rc->wall_height / 2)
				draw_wall(vars, i_resol, pixel_h);
			else
				draw_floor_celling(vars, i_resol, pixel_h);
			pixel_h += vars->screen.resolution_h;
		}
	}
}
