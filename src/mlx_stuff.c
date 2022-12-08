/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:16:13 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/08 09:49:09 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	vars_mlx_init(t_vars *vars)
{
	vars->mlx.mlx = mlx_init();
	vars->mlx.win = mlx_new_window(vars->mlx.mlx, SCREEN_W, SCREEN_H,
			"cub3d");
	vars->mlx.i_img = 0;
	vars->mlx.img[0] = mlx_new_image(vars->mlx.mlx, SCREEN_W, SCREEN_H);
}

int	render_next_frame(t_vars *vars)
{
	int	i[2];

	i[1] = vars->mlx.i_img;
	i[0] = i[1] + 1;
	if (i[0] >= NB_IMG)
		i[0] = 0;
	vars->mlx.i_img = i[0];
	vars->mlx.img[i[0]] = mlx_new_image(vars->mlx.mlx, SCREEN_W, SCREEN_H);
	vars->mlx.addr = mlx_get_data_addr(vars->mlx.img[i[0]], &vars->mlx.bpp,
			&vars->mlx.line_len, &vars->mlx.endian);
	mlx_hook(vars->mlx.win, 2, 0, keypress_handler, vars);
	raycast_main_loop(vars);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win,
		vars->mlx.img[i[0]], 0, 0);
	mlx_destroy_image (vars->mlx.mlx, vars->mlx.img[i[1]]);
	return (0);
}

void	my_mlx_pixel_put_walls(t_vars *vars, int x, int y, char *color)
{
	char			*dst;
	unsigned char	t;

	dst = vars->mlx.addr + (y * vars->mlx.line_len + x
			* (vars->mlx.bpp / 8));
	t = FLUIDITY;
	*dst++ = *color++;
	*dst++ = *color++;
	*dst++ = *color++;
	*dst++ = t;
}

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->mlx.addr + (y * vars->mlx.line_len + x
			* (vars->mlx.bpp / 8));
	*(unsigned int *)dst = color;
}
