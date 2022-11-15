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

LIBRARY			=	$(LIBFT)

#DIRECTORIES--------------------------------------------------------------------

SRCS_DIR 		= 	./src
OBJS_DIR		= 	./obj
INCLUDE_DIR		=	./include
LIBFT_DIR		= 	$(INCLUDE_DIR)/libft

NAME_DSYM		=	./$(NAME).dSYM

#FILES--------------------------------------------------------------------------

#  To make the list of all src, do this command in terminal in project folder
#  find ./src/*.c -type f | cut -c7- | sed 's/$/ \\/'
SRCS_FILES	 	= 	0_main.c \
					error_handling.c \
					floodfill.c \
					init_struct.c \
					parsing.c \


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
					@mkdir -p $(OBJS_DIR)

$(NAME):			$(OBJS) 
					@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBRARY)
					@echo "$G$(NAME)            compiled$W"
					
$(LIBFT):
					@cd $(LIBFT_DIR)/ && make

clean:									
					@$(MAKE) -s clean -C $(LIBFT_DIR)
					@$(RM) $(OBJS)
					@$(RM) $(OBJS_DIR)
					@echo "$R$ All objects       deleted$W"

fclean: 			clean
					@$(MAKE) -s fclean -C $(LIBFT_DIR)
					@$(RM) $(NAME_DSYM)
					@$(RM) $(NAME)
					@echo "$R$(NAME) & lib   deleted$W"

reset:				fclean
					@echo "$R$ readline lib      reseted$W"

re: 				fclean all

debug: $(LIBFT)
				gcc -g $(CFLAGS) $(LIBRARY) $(SRCS) -o $(NAME)

#PHONY--------------------------------------------------------------------------

.PHONY:				all clean fclean re init debug reset

