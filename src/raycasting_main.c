
#include "../include/cub3d.h"


float	degree_ajust(float degree)
{
	if (degree >= 360)
		degree -= 360;
	if (degree < 0)
		degree += 360;
	return (degree);
}

void	raycast_loop_init(t_raycast *rc, t_perso *perso)
{
	rc->shift[0] = -1;
	rc->shift[1] = -1;
	rc->rayangle = perso->angle + rc->ray_i * rc->fov_angle_div;
	rc->rayangle = degree_ajust(rc->rayangle);
	rc->cellvalue[0] = '0';
	rc->cellvalue[1] = '0';
	rc->m = 0;
	rc->b = 0;
	rc->first00[0] = 0;
	rc->first00[1] = 0;
	rc->dist[0] = INT_MAX;
	rc->dist[1] = INT_MAX;
	rc->smallest_dist = INT_MAX;
}

void	set_grid_parallele_direction(t_raycast *rc)
{
	if (rc->rayangle == 0)
	{
		rc->direction[0] = 1;
		rc->direction[1] = 0;
	}
	if (rc->rayangle == 90)
	{
		rc->direction[0] = 0;
		rc->direction[1] = 1;
	}
	if (rc->rayangle == 180)
	{
		rc->direction[0] = -1;
		rc->direction[1] = 0;
	}
	if (rc->rayangle == 270)
	{
		rc->direction[0] = 0;
		rc->direction[1] = -1;
	}
}

void	set_general_direction_and_m(t_raycast *rc)
{
	if (rc->rayangle > 0 && rc->rayangle < 90)
	{
		rc->direction[0] = 1;
		rc->direction[1] = 1;
		rc->m = tanf(rc->rayangle * PI / 180) * -1;
	}
	if (rc->rayangle > 90 && rc->rayangle < 180)
	{
		rc->direction[0] = -1;
		rc->direction[1] = 1;
		rc->m = tanf((180.00 - rc->rayangle) * PI / 180);
	}
	if (rc->rayangle > 180 && rc->rayangle < 270)
	{
		rc->direction[0] = -1;
		rc->direction[1] = -1;
		rc->m = tanf((rc->rayangle - 180) * PI / 180) * -1;
	}
	if (rc->rayangle > 270 && rc->rayangle < 360)
	{
		rc->direction[0] = 1;
		rc->direction[1] = -1;
		rc->m = tanf((360 - rc->rayangle) * PI / 180);
	}
}

void	set_direction_and_linear_function(t_raycast *rc, t_perso *perso)
{
	if (rc->rayangle == 0 || rc->rayangle == 90
		|| rc->rayangle == 180 || rc->rayangle == 270)
		set_grid_parallele_direction(rc);
	else
	{
		set_general_direction_and_m(rc);
		rc->b = perso->position[1] * -1 - rc->m
			* perso->position[0];
	}
}

void	set_first00(t_vars *vars)
{
	vars->raycast.first00[0] = vars->perso.position[0] / vars->map.mapscale;
	vars->raycast.first00[0] *= vars->map.mapscale;
	if (vars->raycast.direction[0] == 1)
		vars->raycast.first00[0] += vars->map.mapscale;
	vars->raycast.first00[1] = vars->perso.position[1] / vars->map.mapscale;
	vars->raycast.first00[1] *= vars->map.mapscale;
	if (vars->raycast.direction[1] == 1)
		vars->raycast.first00[1] += vars->map.mapscale;
}

void	set_x00_n_y00(t_raycast *rc, t_map *map)
{
	rc->x00 = rc->first00[0] + rc->shift[0] * rc->direction[0] * map->mapscale;
	rc->y00 = rc->first00[1] + rc->shift[1] * rc->direction[1] * map->mapscale;
}
void	set__x_y00__n__y_x00(t_raycast *rc, t_perso *perso, t_map *map)
{
	if (rc->direction[0] == 0)
	{
		rc->x_y00 = perso->position[0];
		rc->y_x00 = rc->y00;
	}
	else if (rc->direction[1] == 0)
	{
		rc->x_y00 = rc->x00;
		rc->y_x00 = perso->position[1];
	}
	else
	{
		rc->x_y00 = (-rc->y00 - rc->b) / rc->m;
		rc->y_x00 = (rc->m * rc->x00 + rc->b) * -1;
	}
	if (rc->x_y00 < 0 || rc->x_y00 > map->map_limit[0] * map->mapscale)
		rc->x_y00 = -1;
	if (rc->y_x00 < 0 || rc->y_x00 > map->map_limit[1] * map->mapscale)
		rc->y_x00 = -1;
}

void	wall_pixel_height(t_vars *vars, t_raycast *rc)
{
	if (rc->smallest_dist > 0)
		rc->wall_height = (vars->screen.max_height * vars->map.mapscale)
			/ rc->smallest_dist;
	if (rc->wall_height > vars->screen.max_height || rc->smallest_dist == 0)
		rc->wall_height = vars->screen.max_height;
}


//utiliser mlx_get_address pour aler chercher l'adresse d'un pixel
void	draw_wall(t_vars *vars, int i_resol[2], int pixel_h)
{
	int	color;

	if (vars->raycast.cardinal_wall == 0)
		color = create_trgb(0, 102, 0, 0);//brun east
	if (vars->raycast.cardinal_wall == 1)
		color = create_trgb(0, 96, 96, 96);//grey south
	if (vars->raycast.cardinal_wall == 2)
		color = create_trgb(0, 204, 102, 0);//orange west
	if (vars->raycast.cardinal_wall == 3)
		color = create_trgb(0, 204, 204, 0);//yellow north
	my_mlx_pixel_put(vars,
		vars->screen.center_pixel_w + vars->raycast.ray_i + i_resol[0],
		vars->screen.center_pixel_h + pixel_h,
		color);
	my_mlx_pixel_put(vars,
		vars->screen.center_pixel_w + vars->raycast.ray_i + i_resol[0],
		vars->screen.center_pixel_h - pixel_h,
		color);
}

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

void	drawing(t_vars *vars, t_raycast *rc)
{
	int	pixel_h;
	int	i_resol[2];

	wall_pixel_height(vars, &vars->raycast);
	printinglog(vars->debug_log.fd_raycast, "drawing start", "------------", 0);
	printinglog(vars->debug_log.fd_raycast, "wall_height", "", rc->wall_height);
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

void	cell_x00(t_vars *vars, int x, int y, int cell[2])
{
	if (vars->raycast.direction[0] == -1)
		x -= 1;
	x /= vars->map.mapscale;
	y /= vars->map.mapscale;
	cell[0] = x;
	cell[1] = y;
}

void	cell_y00(t_vars *vars, int x, int y, int cell[2])
{
	
	if (vars->raycast.direction[1] == -1)
		y -= 1;
	y /= vars->map.mapscale;
	x /= vars->map.mapscale;
	cell[0] = x;
	cell[1] = y;
}

int	calcul_dist(t_vars *vars, int x, int y)
{
	printinglog(vars->debug_log.fd_raycast,"calcul dist x", "", x);
	printinglog(vars->debug_log.fd_raycast,"calcul dist y", "", y);
	return ((int)sqrt(pow((double)(x - vars->perso.position[0]), 2)
			+ pow((double)(y - vars->perso.position[1]), 2)));
}

void	nearest_x00_wall(t_vars *vars, t_raycast *rc)
{
	if (rc->direction[0] == 0)
		rc->cellvalue[0] = '-';
	else
	{
		while (rc->cellvalue[0] != '1' && rc->cellvalue[0] != '-')
		{
			rc->shift[0] += 1;
			rc->x00 = rc->first00[0] + rc->shift[0] * rc->direction[0] * vars->map.mapscale;
			if (rc->direction[1] != 0)
				rc->y_x00 = (rc->m * rc->x00 + rc->b) * -1;
			else
				rc->y_x00 = vars->perso.position[1];
			cell_x00(vars, rc->x00, rc->y_x00, rc->cell00[0]);
			printinglog(vars->debug_log.fd_raycast,"shift[0]", "", rc->shift[0]);
			printinglog(vars->debug_log.fd_raycast,"cell00[0][0]", "", rc->cell00[0][0]);
			printinglog(vars->debug_log.fd_raycast,"cell00[0][1]", "", rc->cell00[0][1]);
			if (rc->cell00[0][0] < vars->map.map_limit[0]
				&& rc->cell00[0][0] >= 0
				&& rc->cell00[0][1] < vars->map.map_limit[1]
				&& rc->cell00[0][1] >= 0)
				vars->raycast.cellvalue[0]
					= vars->map.map[rc->cell00[0][1]][rc->cell00[0][0]];
			else
				vars->raycast.cellvalue[0] = '-';
		}
		if (rc->cellvalue[0] != '-')
			rc->dist[0] = calcul_dist(vars, rc->x00, rc->y_x00);
		else
			printinglog(vars->debug_log.fd_raycast,"x00_out of bound", "--", 0);
	}
}

void	nearest_y00_wall(t_vars *vars, t_raycast *rc)
{
	if (rc->direction[1] == 0)
		rc->cellvalue[1] = '-';
	else
	{
		while (rc->cellvalue[1] != '1' && rc->cellvalue[1] != '-')
		{
			rc->shift[1] += 1;
			rc->y00 = rc->first00[1] + rc->shift[1] * rc->direction[1] * vars->map.mapscale;
			if (rc->direction[0] != 0)
				rc->x_y00 = (-rc->y00 - rc->b) / rc->m;
			else
				rc->x_y00 = vars->perso.position[0];
			cell_y00(vars, rc->x_y00, rc->y00, rc->cell00[1]);
			printinglog(vars->debug_log.fd_raycast,"shift[1]", "", rc->shift[1]);
			printinglog(vars->debug_log.fd_raycast,"cell00[1][0]", "", rc->cell00[1][0]);
			printinglog(vars->debug_log.fd_raycast,"cell00[1][1]", "", rc->cell00[1][1]);
			if (rc->cell00[1][0] < vars->map.map_limit[0]
				&& rc->cell00[1][0] >= 0
				&& rc->cell00[1][1] < vars->map.map_limit[1]
				&& rc->cell00[1][1] >= 0)
				vars->raycast.cellvalue[1]
					= vars->map.map[rc->cell00[1][1]][rc->cell00[1][0]];
			else
				vars->raycast.cellvalue[1] = '-';
		}
		if (rc->cellvalue[1] != '-')
			rc->dist[1] = calcul_dist(vars, rc->x_y00, rc->y00);
		else
			printinglog(vars->debug_log.fd_raycast,"y00_out of bound", "--", 0);
	}
}

int	find_smallest_dist(t_vars *vars)
{
	nearest_x00_wall(vars, &vars->raycast);
	nearest_y00_wall(vars, &vars->raycast);
	if (vars->raycast.cellvalue[0] == '-' && vars->raycast.cellvalue[1] == '-')
		return (-1);
	if (vars->raycast.cellvalue[0] == '-')
		return (1);
	if (vars->raycast.cellvalue[1] == '-')
		return (0);
	if (vars->raycast.dist[0] < vars->raycast.dist[1])
		return (0);
	if (vars->raycast.dist[0] > vars->raycast.dist[1])
		return (1);
	printinglog(vars->debug_log.fd_raycast,"dist[0]", "", vars->raycast.dist[0]);
	printinglog(vars->debug_log.fd_raycast,"dist[1]", "", vars->raycast.dist[1]);
	printinglog(vars->debug_log.fd_raycast, "i_dist", "", vars->raycast.i_dist);
	return (vars->raycast.i_dist);
}

int	find_cardinal_wall(t_vars *vars, int i_dist)
{
	if (i_dist == 0)
	{
		if (vars->raycast.direction[0] == -1)
			return (1);
		else
			return (0);
	}
	else
	{
		if (vars->raycast.direction[1] == -1)
			return (2);
		else
			return (3);
	}
}

void	set_dist_n_wall(t_vars *vars)
{
	int	i_dist;

	vars->raycast.i_dist = find_smallest_dist(vars);
	i_dist = vars->raycast.i_dist;
	printinglog(vars->debug_log.fd_raycast, "i_dist", "", i_dist);
	if (i_dist == -1)
	{
		vars->raycast.cardinal_wall = -1;
		vars->raycast.smallest_dist = -1;
	}
	else
	{
		vars->raycast.smallest_dist = vars->raycast.dist[i_dist];
		vars->raycast.smallest_dist = cosf(degree_ajust(
					fabsf(vars->perso.angle - vars->raycast.rayangle)) * PI / 180)
			* vars->raycast.smallest_dist;
		vars->raycast.cardinal_wall = find_cardinal_wall(vars, i_dist);
	}
	if (i_dist == 0)
	{
		printinglog(vars->debug_log.fd_raycast, "x00 wall hit", " ", 0);
		printinglog(vars->debug_log.fd_raycast, "cell_x", "", vars->raycast.cell00[0][0]);
		printinglog(vars->debug_log.fd_raycast, "cell_y", "", vars->raycast.cell00[0][1]);
	}
	else if (i_dist == 1)
	{
		printinglog(vars->debug_log.fd_raycast, "y00 wall hit", " ", 0);
		printinglog(vars->debug_log.fd_raycast, "cell_x", "", vars->raycast.cell00[1][0]);
		printinglog(vars->debug_log.fd_raycast, "cell_y", "", vars->raycast.cell00[1][1]);
	}
}

void	raycast_main_loop(t_vars *vars)
{
	t_raycast	*rc;

	rc = &vars->raycast;
	rc->i_dist = 0;
	rc->ray_i = rc->ray_i_min;
	while (rc->ray_i <= rc->ray_i_max)
	{
		raycast_loop_init(rc, &vars->perso);
		set_direction_and_linear_function(rc, &vars->perso);
		set_first00(vars);
		printinglog(vars->debug_log.fd_raycast, "------------", "---------", 0);
		printinglog(vars->debug_log.fd_raycast, "ray_i", "", rc->ray_i);
		printinglog(vars->debug_log.fd_raycast, "first00[0]", "", rc->first00[0]);
		printinglog(vars->debug_log.fd_raycast, "first00[1]", "", rc->first00[1]);
		printinglog(vars->debug_log.fd_raycast, "rayangle int", "", (int)rc->rayangle);
		printinglog(vars->debug_log.fd_raycast, "direction[0]", "", rc->direction[0]);
		printinglog(vars->debug_log.fd_raycast, "direction[1]", "", rc->direction[1]);
		set_dist_n_wall(vars);
		printinglog(vars->debug_log.fd_raycast, "wall_cardinal", "", vars->raycast.cardinal_wall);
		printinglog(vars->debug_log.fd_raycast, "smallest_dist", "", vars->raycast.smallest_dist);
		drawing(vars, rc);
		rc->ray_i += vars->screen.resolution_w;
	}
}
