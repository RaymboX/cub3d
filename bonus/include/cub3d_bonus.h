/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:48:18 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/05 12:04:10 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include "../../include/libft/header/libft.h"
# include <math.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

# define PI 3.141592654
# define N 270
# define E 0
# define S 90
# define O 180	
# define FOV 60
# define SCREEN_W 1080
# define SCREEN_H 1080
# define OFFSET_CENTER_X 0 // poucentage * 100 negatif=gauche positif=droite
# define OFFSET_CENTER_Y 0 // pourcentage * 100 negatif=haut positif=bas
# define USED_H 100
# define USED_W 100
# define RESOLUTION_W_DEF 1
# define RESOLUTION_H_DEF 1
# define PACE 0.2
# define TURN_ANGLE 5
# define COLLISION_DIST 2
# define MAPSCALE 10000
# define COLL_SPACE 0.1
# define NB_IMG 2
# define FLUIDITY 50
# define DARKER 1
# define MINIMAPSIZE 3
# define COLL_CHAR "1"
# define WALL_CHAR "1"

typedef struct s_log
{
	int	fd_raycast;
}			t_log;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img[NB_IMG];
	int		i_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_cnf
{
	char	*f;
	char	*c;
	int		f_colors[3];
	int		c_colors[3];
	int		f_color;
	int		c_color;
	bool	f_stat;
	bool	c_stat;
}	t_cnf;
typedef struct s_texures
{
	char	*addr;
	int		endian;
	int		bpp;
	int		line_len;
	void	*img;
	int		height;
	int		width;
	bool	stat;
}	t_textures;

typedef struct s_map
{
	char	**map;
	char	**map_cpy;
	int		map_limit[2];
	int		mapscale;
	int		start;
	int		perso_start[2];
	int		first_wall;
	int		fd;
	bool	is_map;
	int		coll_buff;
}	t_map;

typedef struct s_perso
{
	int		fov;
	int		pace;
	int		turn_speed;
	int		position[2];
	int		angle;
}	t_perso;

typedef struct s_raycast
{
	float	rayangle;
	float	fov_angle_div;
	int		ray_i;
	int		ray_i_min;
	int		ray_i_max;
	int		direction[2];
	float	m;
	float	b;
	int		first00[2];
	int		shift[2];
	int		x00;
	int		y00;
	int		x_y00;
	int		y_x00;
	int		dist[2];
	int		i_dist;
	int		smallest_dist;
	int		cell00[2][2];
	char	cellvalue[2];
	int		cardinal_wall;
	int		xpm_x;
	int		xpm_y_50;
	int		xpm_y_div;
	int		wall_height;
	int		real_wall_height;
}	t_raycast;

typedef struct s_screen
{
	int		max_width;
	int		max_height;
	int		dist_pixel_ratio;
	int		center_pixel_w;
	int		center_pixel_h;
	int		resolution_w;
	int		resolution_h;
	int		col_left;
	int		col_right;
}	t_screen;

typedef struct s_minimap
{
	float		pos_x;
	float		pos_y;
	float		ratio_x;
	float		ratio_y;
	float		limit;
}	t_minimap;

typedef struct s_vars
{
	t_textures	tex[4];
	t_map		map;
	t_perso		perso;
	t_raycast	raycast;
	t_screen	screen;
	t_mlx		mlx;
	t_log		debug_log;
	t_cnf		cnf;
	t_minimap	minimap;
}	t_vars;

//PROTOTYPES-------------------------------------------------------------------

//collision.c
void	movecollision(int keycode, t_vars *vars);
void	move_if(t_vars *vars, int angle);
void	position_ajust(t_vars *vars);
void	position_ajust_cardinal_walls(t_vars *vars, int pos_cell[2]);
void	position_ajust_diag_walls(t_vars *vars, int pos_cell[2]);
void	apply_position_ajust(t_vars *vars, int x0y1, int pos_cell[2],
			int lu0rd1);
int		iscoll(t_vars *vars, int x, int y, char *coll_char);
void	set_move_dist(int angle, int mvdis[2], int pace);
int		get_dist_front(t_vars *vars, int angle);
void	raycast_loop_init_coll(t_raycast *rc, int angle);

//distance_fct.c
void	set_dist_n_wall(t_vars *vars, char *stop_char);
int		calcul_dist(t_vars *vars, int x, int y);
int		find_smallest_dist(t_vars *vars, char *stop_char);
void	nearest_x00_wall(t_vars *vars, t_raycast *rc, char *stop_char);
void	nearest_y00_wall(t_vars *vars, t_raycast *rc, char *stop_char);

//drawing.c
int		xpm_x(t_vars *vars);
int		xpm_y(t_vars *vars, int pixel_h, int way);
void	draw_wall(t_vars *vars, int i_resol[2], int pixel_h);
void	draw_floor_celling(t_vars *vars, int i_resol[2], int pixel_h);
void	drawing(t_vars *vars, t_raycast *rc);

//exit_n_free.c
void	error_exit(char *error, char *temp, t_vars *vars);
void	print_error(char *error);
int		end_program(t_vars *vars);
void	free_map(t_vars *vars, char **map);

//floodfill.c
void	flood_fill_inside(t_vars *vars, int y, int x);
void	flood_fill_walls(t_vars *vars, int y, int x);
void	flood_fill_inside_rooms(t_vars *vars, int y, int x, char c);

//floors_ceilings.c
bool	is_seperator(char c, bool *is_virg);
void	check_last_color(char *colors, int *i, int counter, bool *is_virg);
void	check_colors(char *colors, char *nb, int *i, int counter);
void	init_colors(char *colors, t_vars *vars, char type);

//init_utils.c
void	reset_perso(t_vars *vars);
void	max_height_width(t_screen *screen);
void	center_pixel(t_screen *screen);
void	set_fov_angle_div(t_vars *vars);
void	column_limit(t_screen *screen, t_raycast *raycast);

//keypress.c
int		keypress_handler(int keycode, t_vars *vars);
void	turning(int keycode, t_vars *vars);
void	pace_change(int keycode, t_vars *vars);
//void	move(int keycode, t_vars *vars);

//map_tools.c
void	create_map(t_vars *vars);
void	map_size(t_vars *vars);
void	copy_map(t_vars *vars);
bool	is_first_line(char *line, t_vars *vars);
void	ft_map_start(t_vars *vars);

//map_tools2.c
void	set_start(bool *start, t_vars *vars, int i, int ii);
void	check_map_errors(t_vars *vars);
void	check_map_integrity(t_vars *vars);
void	check_inside_rooms(t_vars *vars);
void	find_first_wall(t_vars *vars);

//minimap.c
void	minimap_init(t_vars *vars);
void	draw_perso(t_vars *vars);
void	draw_map(t_vars *vars);

//mlx_stuffs.c
void	vars_mlx_init(t_vars *vars);
int		render_next_frame(t_vars *vars);
void	my_mlx_pixel_put_walls(t_vars *vars, int x, int y, char *color);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);

//mouse_move.c
int		mouse_move(int x, int y, t_vars *vars);

//moving.c
void	valid_position_check(t_vars *vars);
//void	move_position(t_vars *vars, int angle);
//void	set_move_dist(int angle, int mvdis[2], int pace);

//parsing.c
void	check_texture_ext(char *texture, t_vars *vars);
void	check_ext(char *arg);
void	get_img_addr(t_vars *vars);
void	set_starting_point(t_vars *vars);
void	check_file(char **av, t_vars *vars);

//raycast_utils.c
void	wall_pixel_height(t_vars *vars, t_raycast *rc);
void	cell_x00(t_vars *vars, int x, int y, int cell[2]);
void	cell_y00(t_vars *vars, int x, int y, int cell[2]);
void	set_grid_parallele_direction(t_raycast *rc);
void	set_general_direction_and_m(t_raycast *rc);

//raycasting_main.c
void	raycast_main_loop(t_vars *vars);
void	raycast_loop_init(t_raycast *rc, t_perso *perso);
void	set_direction_and_linear_function(t_raycast *rc, t_perso *perso);
void	set_first00(t_vars *vars);

//textures.c
void	assign_texture(t_vars *vars, bool *stat, char *path, int type);
bool	ft_avance_in_file(int *ii, char *temp);
bool	texture_path(char *temp, t_vars *vars);
char	*check_texture(char *temp, int *counter, t_vars *vars);
void	texture_init(t_vars *vars);

//utils.c
int		quadrant_angle(int angle);
void	angle_direction_xy(int angle, int dir[2]);
float	degree_ajust(float degree);
int		find_cardinal_wall(t_vars *vars, int i_dist);
int		is_in_map(t_vars *vars, int x, int y);

//variables_identification_tools.c
bool	is_mapchar(char c);
bool	is_startchar(char c);
bool	is_type_texture(char c);
bool	is_end(char c, int counter);
bool	identify_texture(t_vars *vars, char *path, char *temp);

//various.c
char	*ft_strcat(char *s1, int len);
int		ft_strlen_nl(char *str);

//vars_init.c
void	vars_init(t_vars *vars);
void	raycast_init(t_vars *vars);

#endif