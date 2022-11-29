#include "../include/cub3d.h"
/*
static void	tempvar(t_vars *vars)
{
	int	fd;
	int	i = -1;
	
	if (DEBUG == 1)
		vars->debug_log.fd_raycast = open("raycast_log",
				O_RDWR | O_CREAT | O_TRUNC, 0777);
	vars->map.map_limit[0] = 10;
	vars->map.map_limit[1] = 5;
	vars->map.perso_start[0] = 3;
	vars->map.perso_start[1] = 2;
	vars->perso.angle = 0;
	
	vars->map.map = (char**)malloc(sizeof(char*) * 6);
	fd = open("testmap", O_RDONLY);
	while (++i < 5)
	{
		vars->map.map[i] = get_next_line(fd);
		vars->map.map[i][10] = '\0';
		printinglog(vars->debug_log.fd_raycast, vars->map.map[i],"",9); 
	}
	close(fd);
	vars->map.map[i] = NULL;
}
*/

void	log_print_map(t_vars *vars)
{
	int i = -1;
	char row[2];

	row[1] = '\0';
	while (++i < vars->map.map_limit[1])
		row[0] = i + '0';
}


/* INIT FUNCTION (screen size reset)
** calcul de la grandeur maximal de raycasting en width et height
*/
void	raycast_init(t_vars *vars)
{

	//temp test
	//tempvar(vars);

	if (DEBUG == 1)
		vars->debug_log.fd_raycast = open("raycast_log",
				O_RDWR | O_CREAT | O_TRUNC, 0777);

	vars->perso.angle = 0;
	vars->perso.pace = PACE * MAPSCALE;
	//test
	vars->perso.position[0] = vars->map.perso_start[0] * MAPSCALE
		+ MAPSCALE / 2;
	vars->perso.position[1] = vars->map.perso_start[1] * MAPSCALE
		+ MAPSCALE / 2;
	vars->perso.fov = FOV;
	vars->screen.resolution_h = RESOLUTION_H_DEF;
	vars->screen.resolution_w = RESOLUTION_W_DEF;

	max_height_width(&vars->screen);
	center_pixel(&vars->screen);
	column_limit(&vars->screen, &vars->raycast);
	set_fov_angle_div(vars);

	log_print_map(vars);
}

void	printinglog(int fd, char *intro, char *str, int val)
{
	char	*str_val;

	if (DEBUG == 1)
	{
		write(fd, intro, ft_strlen(intro));
		write(fd, ": ", 2);
		if (ft_strlen(str) > 0)
			write(fd, str, ft_strlen(str));
		else
		{
			str_val = ft_itoa(val);
			write(fd, str_val, ft_strlen(str_val));
			free(str_val);
		}
		write(fd, "\n", 1);
	}
}

void	max_height_width(t_screen *screen)
{
	screen->max_width = 100 - abs(OFFSET_CENTER_X);
	if (100 - abs(OFFSET_CENTER_X) < USED_W)
		screen->max_width = (100 - abs(OFFSET_CENTER_X)) * SCREEN_W / 100;
	else
		screen->max_width = USED_W * SCREEN_W / 100;
	screen->max_height = 100 - abs(OFFSET_CENTER_Y);
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
	screen->center_pixel_w = (SCREEN_W / 2)
		+ ((OFFSET_CENTER_X * SCREEN_W / 2) / 100);
	screen->center_pixel_h = (SCREEN_H / 2)
		+ (OFFSET_CENTER_Y * SCREEN_H / 2) / 100;
}

void	set_fov_angle_div(t_vars *vars)
{
	vars->raycast.fov_angle_div = (vars->perso.fov / 2);
	vars->raycast.fov_angle_div /= vars->raycast.ray_i_max;
}

void	column_limit(t_screen *screen, t_raycast *raycast)
{
	raycast->ray_i_min = screen->max_width / 2 * -1;
	if (screen->max_width % 2 == 0)
		raycast->ray_i_max = screen->max_width / 2 - 1;
	else
		raycast->ray_i_max = screen->max_width / 2;
	screen->col_left = screen->center_pixel_w + raycast->ray_i_min;
	screen->col_right = screen->center_pixel_w + raycast->ray_i_max;
}

