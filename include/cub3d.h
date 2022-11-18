#ifndef CUB3D_H
# define CUB3D_H

# ifdef __linux__
#  include "minilibx-linux/mlx.h"
# else
# include <mlx.h>
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
# define OFFSET_CENTER_X 0 // poucentage * 100 negatif=gauche positif=droite
# define OFFSET_CENTER_Y 0 // pourcentage * 100 negatif=haut positif=bas
# define USED_H 100
# define USED_W 100
# define PIXEL_DIST_RATIO -10
# define RESOLUTION_W_DEF 1
# define RESOLUTION_H_DEF 1

typedef struct s_log
{
	int	fd_raycast;
}			t_log;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_texures
{
	char	*n;
	char	*e;
	char	*s;
	char	*w;
	char	*f;
	char	*c;
	int		f_colors[3];
	int		c_colors[3];
	int		f_color;
	int		c_color;
	bool	no_stat;
	bool	so_stat;
	bool	we_stat;
	bool	ea_stat;
	bool	f_stat;
	bool	c_stat;

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
	float	rayangle; //utiliser en boucle a partir de fov, max_usable_screen_width et boucle i
	float	fov_angle_div;//angle diff for each ray launch
	int		ray_i;
	int		ray_i_min;
	int		ray_i_max;
	int		dx; //direction en x
	int		dy; //direction en y
	float	m; //La pente de la droite calculer a partir de l'angle et la direction
	float	b; //Le b pour faire la formule de fonction lineaire (-y = mx + b)
	int		fx00; //first x00 soit la valeur initial de x00 (selon dx)
	int		fy00; //first y00 soit la valeur initial de y00 (selon dy)
	int		shift_x00; //nombre de deplacement en x pour rencontrer un mur (ce chiffre est multiplier par mapscale)
	int		shift_y00; //nombre de deplacement en y pour rencontrer un mur (ce chiffre est multiplier par mapscale)
	int		x00; //Valeur obtenu a partir de fx00 + shift_x00 * mapscale * dx
	int		y00; //Valeur obtenu a partir de fy00 + shift_y00 * mapscale * dy
	int		x_y00; //Valeur de x en y00
	int		y_x00; //Valeur de y en x00
	int		dist[2]; //Distance entre position du joueur et point (x_y00, y00) * precision
	int		smallest_dist; //Distance la plus courte entre dist_x00 et dist_y00
	int		cellx00[2];
	int		celly00[2];
	char	cellvalue[2]; //Valeur de la cell rencontrer pour le point (x00, y_x00) (1 = mur, 0 = rien)
	int		cardinal_wall; //afin d'appliquer le bon xpm determiner par les directions dx et dy et par le point utiliser (smallest dist = dist_x00 ou dist_y00)
	int		wall_height;
}	t_raycast;

typedef struct s_screen
{
	int	max_width; //Nombre de pixel en largeur Obtenu a partir du plus petit entre offset_center_y et de l'espace restant en y et use_height
	int	max_height; //Nombre de pixel en hauteur Obtenu a partir du plus petit entre offset_center_x et de l'espace restant en x et use_width
	int	precision; //Multiple de 10 pour la distance afin de conserver en int ??? si utilise fixpointvalue = pas necessaire
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
	t_textures	textures;
	t_map		map;
	t_perso		perso;
	t_raycast	raycast;
	t_screen	screen;
	t_mlx		mlx_vars;
	t_log		debug_log;
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
void	check_file(char **av, t_vars *vars);
void	ft_map_start(int fd, t_vars *vars);
bool	is_first_line(char *line);
void	map_size(int fd, t_vars *vars);
void	check_ext(char *arg);
void	create_map(int fd, t_vars *vars);
void	flood_fill_inside(t_vars *vars, int pos_x, int pos_y);
void	flood_fill_walls(t_vars *vars, int pos_x, int pos_y);
void	copy_map(t_vars *vars);

//mlx
void	vars_mlx_init(t_vars *vars);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
int		render_next_frame(t_vars *vars);

//Error Handling
void	error_exit(char *error, int fd, char *temp);
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
void	set_fx00_n_fy00(t_vars *vars);
void	shift_add(t_raycast *rc);
void	set_x00_n_y00(t_raycast *rc, t_map *map);
void	set__x_y00__n__y_x00(t_raycast *rc, t_perso *perso, t_map *map);
void	find_cell_coord(t_raycast *rc, t_map *map);
void	distances_calculation(t_raycast *rc, t_perso *perso, t_map *map);
int		wall_hit(t_raycast *rc);
void	drawing_wall(t_vars *vars, t_raycast *rc, int i_pixel);
void	drawing_floor_celling(t_vars *vars, t_raycast *rc, int i_pixel);
void	drawing(t_vars *vars, t_raycast *rc);
void	raycast_main_loop(t_vars *vars);

//raycasting init
void	raycast_init(t_vars *vars);
void	printinglog(int fd, char *intro, char *str, int val);
void	max_height_width(t_screen *screen);
void	center_pixel(t_screen *screen);
void	set_fov_angle_div(t_vars *vars);
void	column_limit(t_screen *screen, t_raycast *raycast);

#endif