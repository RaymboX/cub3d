#PROGRAM NAME-------------------------------------------------------------------

NAME = 			libft.a

#SYSTEM VAR---------------------------------------------------------------------

R = $(shell tput -Txterm setaf 1)
G = $(shell tput -Txterm setaf 2)
C = $(shell tput -Txterm setaf 6)
W = $(shell tput -Txterm setaf 7)
Y = $(shell tput -Txterm setaf 3)
Z = $(shell tput -Txterm setaf 5)

CFLAGS = 		-Wall -Wextra -Werror
CC		= 		@gcc
RM		= 		rm -rf

#DIRECTORIES--------------------------------------------------------------------

SRCS_DIR 		= 	./src
OBJS_DIR		= 	./obj

#FILES--------------------------------------------------------------------------

SRCS_FILES = 	ft_atoi.c \
				ft_atol.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_ltoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_nbr10tohex.c \
				ft_pow.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				get_next_line.c \
				ft_isspace.c \
				ft_ptrlen.c \
				ft_atoi_base.c \
				progress_bar.c \
				rad_rc2_deg_conversion.c \
				create_trgb.c \
				free_dbl_ptr.c \
				ft_strchr_i.c \
				ft_strrchr_i.c \
				ft_is_str_digit.c \
				ft_is_int_range.c \
				ft_msleep.c \
				ft_now_millisecond.c

#FILES VAR----------------------------------------------------------------------

SRCS 			= 	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS 			= 	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

#SYSTEM RULES-------------------------------------------------------------------

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

#COMPILING RULES------------------------------------------------------------------



all:			init $(NAME)

init:
				@mkdir -p $(OBJS_DIR)

$(NAME):		$(OBJS)
				@ar rcs $(NAME) $(OBJS)
				@echo "$Glibft         compiled$W"

clean:			
ifneq ($(wildcard $(OBJS_DIR)),)
				@$(RM) $(OBJS)
				@$(RM) $(OBJS_DIR)
				@echo "$Rlibft objects deleted$W"
endif

fclean: 		clean
ifneq ($(wildcard $(NAME)),)
				@$(RM) $(NAME)
				@echo "$Rlibft.a       deleted$W"
endif

re: 			fclean all

.PHONY:			all clean fclean re init

test:
ifneq ($(wildcard $(OBJS_DIR)),)
	@echo "Found"
else
	@echo "Did not find"
endif