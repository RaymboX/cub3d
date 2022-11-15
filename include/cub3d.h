#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include "libft/header/libft.h"

# define TO_RAD 0.174532925
# define N 270
# define E 0
# define S 90
# define O 180
# define FOV 60

typedef struct s_texures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
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
	int		map_limit[2]; //limit max en x [0] et en y [1]
	int		mapscale; //multiple de 10 de subdivision des coordonnees de la map (peut-etre modifier pour un int)
	int		start;
	bool	is_map;
}	t_map;

typedef struct s_perso
{
	int	fov; //Field of view en degrés
	int	player_pace; //vitesse de deplacement (ratio selon la map exemple 0.5 = deplacement de 50 si mapscale = 10 et 500 si mapsacle = 100)
	int	player_turn_speed; //vitesse de rotation en degree
	int player_position[2]; //player position x[0] y[1] selon le mapscale
	int player_angle; //Direction que regarde player en degree
}	t_perso;

typedef struct s_raycast
{
	int		max_usable_screen_height; //Nombre de pixel en hauteur Obtenu a partir du plus petit entre offset_center_x et de l'espace restant en x et use_width
	int		max_usable_screen_width; //Nombre de pixel en largeur Obtenu a partir du plus petit entre offset_center_y et de l'espace restant en y et use_height
	int		fov_rayangle; //difference entre player angle et
	float	rayangle; //utiliser en boucle a partir de fov, max_usable_screen_width et boucle i
	int		dx; //direction en x
	int		dy; //direction en y
	int		m; //La pente de la droite calculer a partir de l'angle et la direction
	int		b; //Le b pour faire la formule de fonction lineaire (-y = mx + b)
	int		fx00; //first x00 soit la valeur initial de x00 (selon dx)
	int		fy00; //first y00 soit la valeur initial de y00 (selon dy)
	int		shift_x00; //nombre de deplacement en x pour rencontrer un mur (ce chiffre est multiplier par mapscale)
	int		shift_y00; //nombre de deplacement en y pour rencontrer un mur (ce chiffre est multiplier par mapscale)
	int		x00; //Valeur obtenu a partir de fx00 + shift_x00 * mapscale * dx
	int		y00; //Valeur obtenu a partir de fy00 + shift_y00 * mapscale * dy
	int		x_y00; //Valeur de x en y00
	int		y_x00; //Valeur de y en x00
	int		dist_x00; //Distance entre position du joueur et point (x00, y_x00) * precision
	int		dist_y00; //Distance entre position du joueur et point (x_y00, y00) * precision
	int		smallest_dist; //Distance la plus courte entre dist_x00 et dist_y00
	int		mapcellvalue_x00; //Valeur de la cell rencontrer pour le point (x00, y_x00) (1 = mur, 0 = rien)
	int		mapcellvalue_y00; //Valeur de la cell rencontrer pour le point (x_y00, y00) (1 = mur, 0 = rien)
	int		cardinal_wall; //afin d'appliquer le bon xpm determiner par les directions dx et dy et par le point utiliser (smallest dist = dist_x00 ou dist_y00)
}	t_raycast;

typedef struct s_screen
{
	int	precision; //Multiple de 10 pour la distance afin de conserver en int ??? si utilise fixpointvalue = pas necessaire
	int	dist_pixel_ratio; //Ratio du nombre de pixel en hauteur selon la distance (valeur multiplier par screen_height)
	int	screen_height; //Hauteur de l'ecran
	int	sreen_width; //largeur de l'ecran
	int	offset_center_x; //pourcentage negatif (gauche) ou positif (droite) de l'offset du centre de l'ecran
	int	offset_center_y; //pourcentage negatif (haut) ou positif (bas) de l'offset du centre de l'ecran
	int	use_width; //pourcentage d'utilisation en largeur de l'ecran
	int	use_height; //pourcentage d'utilisation en hauteur de l'ecran
} t_screen;

typedef struct s_vars
{
	t_textures	textures;
	t_map		map;
	t_perso		perso;
	t_raycast	raycast;
	t_screen	screen;
}	t_vars;

//Gestion de map
void	check_map(char **av, t_vars *vars);
void	ft_map_start(int fd, t_vars *vars);
bool	is_first_line(char *line);
void	map_size(int fd, t_vars *vars);
void	check_ext(char *arg);
int		texture_init(int fd, t_vars *vars);
bool	texture_path(char *temp, t_vars *vars);
void	create_map(int fd, t_vars *vars);

#endif