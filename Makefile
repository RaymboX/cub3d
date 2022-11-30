#PROGRAM NAME-------------------------------------------------------------------

NAME 			= 	cub3d

#SYSTEM VAR---------------------------------------------------------------------

R = $(shell tput -Txterm setaf 1)
G = $(shell tput -Txterm setaf 2)
C = $(shell tput -Txterm setaf 6)
W = $(shell tput -Txterm setaf 7)
Y = $(shell tput -Txterm setaf 3)
Z = $(shell tput -Txterm setaf 5)

CFLAGS 			= 	-Wall -Werror -Wextra
CC				= 	gcc
RM				= 	rm -rf
VALG_LEAK		=	valgrind --leak-check=full
UNAME_S		 	= 	$(shell uname -s)
REL_PATH		=	$(shell pwd)
LEAK_CMD		=	leaks --atExit --

LIBMLX 			= 	-L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
LIBMLX_BETA		=	-L./mlx -lmlx -framework OpenGL -framework AppKit
LIB_LINUX		=	-L ./include/minilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
LIBRARY			=	$(LIBFT) $(LIBMLX_BETA)
LIBRARY_LINUX	=	$(LIB_LINUX) include/libft/src/*c
MLX				=	libmlx.dylib

#DIRECTORIES--------------------------------------------------------------------

SRCS_DIR 		= 	./src
OBJS_DIR		= 	./obj
INCLUDE_DIR		=	./include
LIBFT_DIR		= 	$(INCLUDE_DIR)/libft
MLX_DIR			=	mlx

NAME_DSYM		=	./$(NAME).dSYM

#FILES--------------------------------------------------------------------------

#  To make the list of all src, do this command in terminal in project folder
#  find ./src/*.c -type f | cut -c7- | sed 's/$/ \\/'
SRCS_FILES	 	= 	0_main.c \
					distance_fct.c \
					drawing.c \
					exit_n_free.c \
					floodfill.c \
					floors_ceilings.c \
					init_utils.c \
					keypress.c \
					map_tools.c \
					map_tools2.c \
					mlx_stuff.c \
					mouse_move.c \
					moving.c \
					parsing.c \
					raycast_utils.c \
					raycasting_main.c \
					textures.c \
					utils.c \
					variables_identification_tools.c \
					various_tools.c \
					vars_init.c 


HEADERS_FILES	=	cub3d.h

LIBFT_FILES		= 	libft.a


#FILES VAR----------------------------------------------------------------------
SRCS 			= 	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

HEADERS			=	$(addprefix $(INCLUDE_DIR)/, $(HEADERS_FILES))

OBJS 			= 	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

LIBFT 			= 	$(addprefix $(LIBFT_DIR)/, $(LIBFT_FILES))

#SYSTEM RULES-------------------------------------------------------------------

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

#$(V).SILENT:

#COMPILING RULES------------------------------------------------------------------

all : 				init $(LIBRD) $(NAME)

init:
					@$(MAKE) -s -C $(LIBFT_DIR)
					@$(MAKE) -s -C $(MLX_DIR)
					@$(RM) $(MLX)
					@cp $(MLX_DIR)/$(MLX) $(MLX)
					@mkdir -p $(OBJS_DIR)

$(NAME):			$(OBJS) 
ifeq ($(UNAME_S),Linux)
					@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBRARY_LINUX)
else
					@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBRARY)
endif					
					@echo "$G$(NAME)         compiled$W"
					
$(LIBFT):
					@cd $(LIBFT_DIR)/ && make

clean:									
					@$(MAKE) -s clean -C $(LIBFT_DIR)
					@$(MAKE) -s clean -C $(MLX_DIR)
					@$(RM) $(OBJS)
					@$(RM) $(OBJS_DIR)
					@echo "$R$ All objects   deleted$W"

fclean: 			clean
					@$(MAKE) -s fclean -C $(LIBFT_DIR)
					@$(RM) $(MLX)
					@$(RM) $(NAME_DSYM)
					@$(RM) $(NAME)
					@echo "$R$(NAME)         deleted$W"

re: 				fclean all

debug: $(LIBFT)
ifeq ($(UNAME_S),Linux)
					gcc -g $(CFLAGS) -o $(NAME) $(SRCS) $(LIBRARY_LINUX) -D DEBUG=1
else
					gcc -g $(CFLAGS) $(LIBRARY) $(SRCS) -o $(NAME) -D DEBUG=0
endif
				
#PHONY--------------------------------------------------------------------------

.PHONY:				all clean fclean re init debug reset

