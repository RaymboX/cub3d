
#include "../include/cub3d.h"

/* INIT FUNCTION (screen size reset)
** calcul de la grandeur maximal de raycasting en width et height
*/
void	max_height_width(t_screen *screen)
{
	screen->max_width = 100 - OFFSET_CENTER_X;
	if (100 - abs(OFFSET_CENTER_X) < USED_W)
		screen->max_width = (100 - abs(OFFSET_CENTER_X)) * SCREEN_W / 100;
	else
		screen->max_width = USED_W * SCREEN_W / 100;
	screen->max_height = 100 - OFFSET_CENTER_Y;
	if (100 - abs(OFFSET_CENTER_Y) < USED_H)
		screen->max_height = (100 - abs(OFFSET_CENTER_Y)) * SCREEN_H / 100;
	else
		screen->max_height = USED_H * SCREEN_H / 100;
}

/* INIT FUNCTION (screen size reset)
**calcul du point central du raycasting
*/
void	center_pixel(t_screen *screen)
{
	screen->center_pixel_w = SCREEN_W / 2
		+ (OFFSET_CENTER_X / 100) * SCREEN_W;
	screen->center_pixel_h = SCREEN_H / 2
		+ (OFFSET_CENTER_X / 100) * SCREEN_H;
}

void	set_fov_angle_div(t_raycast *raycast)
{
	raycast->fov_angle_div = (fov / 2) / raycast->ray_i_max;
}

void	column_limit(t_screen *screen, t_raycast *raycast)
{
	raycast->ray_i_min = screen->max_width / 2 * -1;
	if (screen->max_width % 2 == 1)
		raycast->ray_i_max = screen->max_width / 2 - 1;
	else
		raycast->ray_i_max = screen->max_width / 2;
	screen->col_left = screen->center_pixel_w + raycast->ray_i_min;
	screen->col_right = screen->center_pixel_w + raycast->ray_i_max;
}

float	degree_ajust(float degree)
{
	if (degree >= 360)
		degree -= 360;
	if (degree < 0)
		degree += 360;
}

void	raycast_loop_init(t_raycast *rc, t_perso *perso)
{
	rc->shift_x00 = -1;
	rc->shift_y00 = -1;
	rc->rayangle = perso->angle + abs(rc->ray_i) * rc->fov_angle_div;
	rc->rayangle = degree_ajust(rc->rayangle);
	rc->cellvalue_x00 = '0';
	rc->cellvalue_y00 = '0';
	rc->m = 0;
	rc->b = 0;
	rc->fx00 = 0;
	rc->fy00 = 0;
	rc->dist_x00 = INT_MAX;
	rc->dist_y00 = INT_MAX;
}

void	set_grid_parallele_direction(t_raycast *rc)
{
	if (rc->rayangle == 0)
	{
		rc->dx = 1;
		rc->dy = 0;
	}
	if (rc->rayangle == 90)
	{
		rc->dx = 0;
		rc->dy = 1;
	}
	if (rc->rayangle == 180)
	{
		rc->dx = -1;
		rc->dy = 0;
	}
	if (rc->rayangle == 270)
	{
		rc->dx = 0;
		rc->dy = -1;
	}
}

void	set_general_direction_and_m(t_raycast *rc)
{
	if (rc->rayangle > 0 && rc->rayangle < 90)
	{
		rc->dx = 1;
		rc->dy = 1;
		rc->m = tan(rc->rayangle * TO_RAD) * -1;
	}
	if (rc->rayangle > 90 && rc->rayangle < 180)
	{
		rc->dx = -1;
		rc->dy = 1;
		rc->m = tan((180 - rc->rayangle) * TO_RAD);
	}
	if (rc->rayangle > 180 && rc->rayangle < 270)
	{
		rc->dx = -1;
		rc->dy = -1;
		rc->m = tan((rc->rayangle - 180) * TO_RAD) * -1;
	}
	if (rc->rayangle > 270 && rc->rayangle < 360)
	{
		rc->dx = 1;
		rc->dy = -1;
		rc->m = tan((360 - rc->rayangle) * TO_RAD);
	}
}

void	set_direction_and_linear_function(t_raycast *rc, t_perso *perso)
{
	if (rc->rayangle % 90 == 0 || rc->rayangle == 0)
		set_grid_parallele_direction(rc);
	else
	{
		set_general_direction_and_m(rc);
		rc->b = perso->position[1] * -1 - rc->m
			* perso->position[0];
	}
}

void	set_fx00_n_fy00(t_vars *vars)
{
	vars->raycast.fx00 = vars->perso.position[0] / vars->map.mapscale;
	vars->raycast.fx00 *= vars->map.mapscale;
	if (vars->raycast.dx == 1)
		vars->raycast.fx00 += vars->map.mapscale;
	vars->raycast.fy00 = vars->perso.position[1] / vars->map.mapscale;
	vars->raycast.fy00 *= vars->map.mapscale;
	if (vars->raycast.dy == 1)
		vars->raycast.fy00 += vars->map.mapscale;
}

void	shift_add(t_raycast *rc)
{
	if (rc->shift_x00 == -1)
	{
		rc->shift_x00 = 0;
		rc->shift_y00 = 0;
	}
	else
	{
		if (rc->dist_x00 < rc->dist_y00 && rc->dx != 0)
			rc->shift_x00 += 1;
		else
			rc->shift_y00 += 1;
	}
}

void	set_x00_n_y00(t_raycast *rc, t_screen *screen)
{
	rc->x00 = rc->fx00 + rc->shift_x00 * rc->dx * screen->mapscale;
	rc->y00 = rc->fy00 + rc->shift_y00 * rc->dy * screen->mapscale;
}
void	set__x_y00__n__y_x00(t_raycast *rc, t_perso *perso, t_map *map)
{
	if (rc->dx == 0)
	{
		rc->x_y00 = perso->position[0];
		rc->y_x00 = rc->y00;
	}
	else if (rc->dy == 0)
	{
		rc->x_y00 = rc->x00;
		rc->y_x00 = perso->position[1];
	}
	else
	{
		rc->x_y00 = (rc->y00 - rc->b) / rc->m;
		rc->y_x00 = (rc->m * rc->x00 + rc->b) * -1;
	}
	if (rc->x_y00 < 0 || rc->x_y00 > map->map_limit[0] * map->mapscale)
		rc->x_y00 = -1;
	if (rc->y_x00 < 0 || rc->y_x00 > map->map_limit[1] * map->mapscale)
		rc->y_x00 = -1;
}

void	find_cell_coord(t_raycast *rc, t_map *map)
{
	//faire une exeption pour les coins parfait x_y00 % mapscale == 0 && y_x00 % mapscale == 0
	if (rc->dx >= 0)
	{
		if (rc->x_y00 > 0)
			rc->celly00[0] = rc->x_y00 / map->mapscale;
		rc->cellx00[0] = rc->x00 / map->mapscale;
	}
	else
	{
		if (rc->x_y00 > 0)
			rc->celly00[0] = (rc->x_y00 - 1) / map->mapscale;
		rc->cellx00[0] = (rc->x00 - 1) / map->mapscale;
	}
	if (rc->dy >= 0)
	{
		if (rc->y_x00 > 0)
			rc->cellx00[1] = rc->y_x00 / map->mapscale;
		rc->celly00[1] = rc->y00 / map->mapscale;
	}
	else
	{
		if (rc->y_x00 > 0)
			rc->cellx00[1] = (rc->y_x00 - 1) / map->mapscale;
		rc->celly00[1] = (rc->y00 - 1) / map->mapscale;
	}
}

void	distances_calculation(t_raycast *rc, t_perso *perso, t_map *map)
{
	if (y_x00 > 0)
		rc->cellvalue_x00 = map->map[rc->cellx00[1]][rc->cellx00[0]];
	if (rc->cellvalue_x00 == '1')
		rc->dist_x00 =(int)sqrt(
				pow((double)(rc->x00 - perso->position[0], 2)) +
				pow((double)(rc->y_x00 - perso->position[1], 2));
	if (x_y00 > 0)
		rc->cellvalue_y00 = map->map[rc->celly00[1]][rc->celly00[0]];
	if (rc->cellvalue_y00 == '1')
		rc->dist_y00 = (int)sqrt(
				pow((double)(rc->x_y00 - perso->position[0], 2)) +
				pow((double)(rc->y00 - perso->position[1], 2));
	if (rc->cellvalue_x00 == '1' || rc->cellvalue_y00 == '1')
	{
		if (rc->dist_x00 <= rc->dist_y00)
			rc->smallest_dist = rc->dist_x00;
		else
			rc->smallest_dist = rc->dist_y00;
	}
	if (rc->x_y00 == -1 && rc->y_x00 == -1)
		rc->smallest_dist == -1;
}

int		wall_hit(t_raycast *rc)
{
	if (rc->smallest_dist == -1)
		return (-1);
	if (rc->smallest_dist == rc->dist_y00)
	{
		if (rc->dy == -1)
			return (270);
		else
			return (90);
	}
	else
	{
		if (rc->dx == -1)
			return (180);
		else
			return (0);
	}
	return (-1);
}

void	drawing(t_vars *vars)
{
	int	i_pixel;
	
	rc->cardinal_wall = wall_hit(&vars->raycast);
	//calcul du nombre de pixel selon distance
	
	//boucle de dessin de mur
	//boucle restant celling et floor
}

void	raycast_main_loop(t_vars *vars)
{
	t_raycast	*rc;

	rc = &vars->raycast;
	rc->ray_i = rc->ray_i_min;
	while (rc->ray_i <= rc->ray_i_max)
	{
		raycast_loop_init(rc);
		set_direction_and_linear_function(rc, &vars->perso);
		set_fx00_n_fy00(vars);
		while (rc->cellvalue_x00 == '1' || rc->cellvalue_y00 == '1'
			|| rc->smallest_dist == -1)
		{
			shift_add(rc);
			set_x00_n_y00(rc, &vars->screen);
			set__x_y00__n__y_x00(*rc, &vars->perso, &vars.map);
			find_cell_coord(rc, &vars->map);
			distances_calculation(rc, &vars->perso, &vars->map);
		}
		drawing(vars);
	}
}
