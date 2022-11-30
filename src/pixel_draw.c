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