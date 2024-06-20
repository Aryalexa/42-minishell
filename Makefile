CC		= gcc

# FT_SAN = -fsanitize=address
FT_SAN 	= 
CFLAGS	= -Wall -Wextra -Werror $(FT_SAN)

AR		= ar -rcs
RM		= /bin/rm -rf

NAME	= minishell

SRCS_S	=	builtin/echo.c \
			main/main.c \
			pipex/pipex.c \
			pipex/utils.c

OBJS_S	=  $(SRCS_S:.c=.o)

LIBFT_PATH  = libft
LIBFT	= $(LIBFT_PATH)/libft.a

all:		$(NAME) 


${NAME}: ${OBJS_S}
	@${MAKE} -C $(LIBFT_PATH)
	@${CC} ${CFLAGS} $(OBJS_S) $(LIBFT) -o ${NAME}

# bonus:		$(NAME_C)

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) 

$(LIBFT):	
			make -C $(LIBFT_PATH) all

clean:
			make -C $(LIBFT_PATH) clean
			$(RM) $(OBJS_S)

fclean:		clean
			make -C $(LIBFT_PATH) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re pipex bonus