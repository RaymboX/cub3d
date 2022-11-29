#ifndef CUB3D_H
# define CUB3D_H

# ifdef __linux__
#  include "minilibx-linux/mlx.h"
# else
#  include "../mlx/mlx.h"
//#  include <mlx.h>
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include "libft/header/libft.h"
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
# define SCREEN_W 1920
# define SCREEN_H 1080
# define OFFSET_CENTER_X 44 // poucentage * 100 negatif=gauche positif=droite
# define OFFSET_CENTER_Y 0 // pourcentage * 100 negatif=haut positif=bas
# define USED_H 100
# define USED_W 56
# define RESOLUTION_W_DEF 1
# define RESOLUTION_H_DEF 1
# define PACE 0.2
# define TURN_ANGLE 5
# define COLLISION_DIST 2
# define MAPSCALE 10000
# define COLL_SPACE 0.1
# define NB_IMG 2

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
	int		bits_per_pixel;
	int		line_length;
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
	int		size_line;
	void	*img;
//	t_wall_texture	wall_texture[4];//0 = East, 1 = south, 2 = west, 3 = north
	int		height;
	int		width;
	bool	stat;
}	t_textures;

typedef struct s_map
{
	char	**map;
	char	**map_cpy;
	int		map_limit[2]; //limit max en x [0] et en y [1]
	int		mapscale; //multiple de 10 de subdivision des coordonnees de la map (peut-etre modifier pour un int)
	int		start;
	int		perso_start[2];
	int		first_wall;
	bool	is_map;
}	t_map;

typedef struct s_perso
{
	int	fov; //Field of view en degrés
	int	pace; //vitesse de deplacement (ratio selon la map exemple 0.5 = deplacement de 50 si mapscale = 10 et 500 si mapsacle = 100)
	int	turn_speed; //vitesse de rotation en degree
	int position[2]; //player position x[0] y[1] selon le mapscale
	int angle; //Direction que regarde player en degree
}	t_perso;

typedef struct s_raycast
{
	float	rayangle; //l'angle pour tout les rayons pour faire l'image
	float	fov_angle_div;//la difference d'angle entre deux rayangle
	int		ray_i;//servant a la boucle pour tout les rayangle
	int		ray_i_min;//le ray_i minimum basee sur screen_width
	int		ray_i_max;//le ray_i maximum (la ou la boucle cesse)
	int		direction[2];//anciennement dx dy->direction en x et y du rayon
	float	m; //La pente du rayon calculer a partir de l'angle et la direction
	float	b; //Le b pour faire la formule de fonction lineaire (-y = mx + b)
	int		first00[2];//premiere rencontre avec le grid (base pour calculer les autres intersection)
	int		shift[2];//sert a passer a un autre insection du grid
	int		x00; //Valeur obtenu a partir de fx00 + shift_x00 * mapscale * dx
	int		y00; //Valeur obtenu a partir de fy00 + shift_y00 * mapscale * dy
	int		x_y00; //Valeur de x en y00
	int		y_x00; //Valeur de y en x00
	int		dist[2]; //Distance entre position du joueur et point (x_y00, y00) * precision
	int		i_dist;// 0 = position de x00 plus proche et 1 = y00 plus proche
	int		smallest_dist; //Distance la plus courte entre dist_x00 et dist_y00
	int		cell00[2][2];//Coordonnee des cellules d'instersection
	char	cellvalue[2]; //Valeur de la cell d'intersection pour le point (x00, y_x00) (1 = mur, 0 = rien)
	int		cardinal_wall; //valeur de 0 a 3 pour le mur rencontrer pour appliquer bonne texture
	int		xpm_x;//valeur de 0 a 100 exprimant la colonne de pixel a prendre
	int		xpm_y_50;//50% du height du xpm
	int		xpm_y_div;//ratio xpm height / wall height
	int		wall_height;//la hauteur du mur en pixel selon la distance
}	t_raycast;

typedef struct s_screen
{
	int	max_width; //Nombre de pixel en largeur Obtenu a partir du plus petit entre offset_center_y et de l'espace restant en y et use_height
	int	max_height; //Nombre de pixel en hauteur Obtenu a partir du plus petit entre offset_center_x et de l'espace restant en x et use_width
	int	dist_pixel_ratio; //Ratio du nombre de pixel en hauteur selon la distance (valeur multiplier par screen_height)
	int	center_pixel_w;
	int	center_pixel_h;
	int	resolution_w;
	int	resolution_h;
	int	col_left;
	int	col_right;
}	t_screen;

typedef struct s_vars
{
	t_textures		textures[4];
	t_map			map;
	t_perso			perso;
	t_raycast		raycast;
	t_screen		screen;
	t_mlx			mlx_vars;
	t_log			debug_log;
	t_cnf			cnf;
}	t_vars;

//Textures/Floors/Ceilings
bool	texture_path(char *temp, t_vars *vars);
void	texture_init(int fd, t_vars *vars);
void	check_texture_ext(char *texture);
void	assign_texture(t_vars *vars, bool *stat, char *path, char type);
void	init_colors(char *colors, t_vars *vars, char type);
void	check_colors(char *colors, char *nb, int *i, int counter);
void	check_last_color(char *colors, int *i, int counter, bool	*is_virg);

//Variable identificaiton
bool	is_mapchar(char c);
bool	is_startchar(char c);
bool	is_type_texture(char c);
bool	is_end(char c, int counter);
bool	is_seperator(char c, bool *is_virg);
bool	identify_texture(t_vars *vars, char *path, char *temp);

//Variable initialisation
void	texture_struct_init(t_vars *vars);

//Gestion de map
void	free_map(t_vars *vars, char **map);
void	check_file(char **av, t_vars *vars);
void	ft_map_start(int fd, t_vars *vars);
bool	is_first_line(char *line, int fd, t_vars *vars);
void	map_size(int fd, t_vars *vars);
void	check_ext(char *arg);
void	create_map(int fd, t_vars *vars);
void	flood_fill_inside(t_vars *vars, int x, int y);
void	flood_fill_walls(t_vars *vars, int x, int y);
void	flood_fill_inside_rooms(t_vars *vars, int y, int x, char c);
void	copy_map(t_vars *vars);

//mlx
void	vars_mlx_init(t_vars *vars);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void	my_mlx_pixel_put_walls(t_vars *vars, int x, int y, char *color);
int		render_next_frame(t_vars *vars);
int		key_hook(int key, t_vars *vars);

//Error Handling
void	error_exit(char *error, int fd, char *temp, t_vars *vars);
void	print_error(char *error);
void	check_map_errors(t_vars *vars);
void	check_map_integrity(t_vars *vars);

//Various tools
char	*ft_strcat(char *s1, int len);
int		ft_strlen_nl(char *str);

//RAYCASTING--------------------------------------------------------------------
//raycasting loop
float	degree_ajust(float degree);
void	raycast_loop_init(t_raycast *rc, t_perso *perso);
void	set_grid_parallele_direction(t_raycast *rc);
void	set_general_direction_and_m(t_raycast *rc);
void	set_direction_and_linear_function(t_raycast *rc, t_perso *perso);
void	set_first00(t_vars *vars);
void	wall_pixel_height(t_vars *vars, t_raycast *rc);
int		xpm_x(t_vars *vars);
int		xpm_y(t_vars *vars, int pixel_h, int way);
void	draw_wall(t_vars *vars, int i_resol[2], int pixel_h);
void	draw_floor_celling(t_vars *vars, int i_resol[2], int pixel_h);
void	drawing(t_vars *vars, t_raycast *rc);
void	cell_x00(t_vars *vars, int x, int y, int cell[2]);
void	cell_y00(t_vars *vars, int x, int y, int cell[2]);
void	nearest_x00_wall(t_vars *vars, t_raycast *rc);
void	nearest_y00_wall(t_vars *vars, t_raycast *rc);
int		find_smallest_dist(t_vars *vars);
int		find_cardinal_wall(t_vars *vars, int i_dist);
void	set_dist_n_wall(t_vars *vars);
void	raycast_main_loop(t_vars *vars);

//raycasting init
void	raycast_init(t_vars *vars);
void	printinglog(int fd, char *intro, char *str, int val);
void	max_height_width(t_screen *screen);
void	center_pixel(t_screen *screen);
void	set_fov_angle_div(t_vars *vars);
void	column_limit(t_screen *screen, t_raycast *raycast);

//keypress.c
int		keypress_handler(int keycode, t_vars *vars);
void	turning(int keycode, t_vars *vars);
void	move(int keycode, t_vars *vars);
void	move_collsion(t_vars *vars, int angle);
char	cell_move_val(t_vars *vars, int angle, int collision);
void	set_move_dist(t_vars *vars, int angle, int movedist[2], int collision);
int		quadrant_angle(int angle);
void	angle_direction_xy(int angle, int dir[2]);

int		mouse_move(int x, int y, t_vars *vars);


#endif