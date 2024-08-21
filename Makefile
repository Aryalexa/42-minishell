CC		= gcc

# FT_SAN = -fsanitize=address
EXCFLGS = -lreadline -lncurses
CFLAGS	= -Wall -Wextra -Werror $(FT_SAN)

AR		= ar -rcs
RM		= /bin/rm -rf

NAME	= minishell

SRCS_S	=	3_utils/utils.c \
			3_utils/debug.c \
			3_utils/error.c \
			3_utils/memory.c \
			4_builtin/builtin.c \
			4_builtin/echo.c \
			4_builtin/exit.c \
			4_builtin/pwd.c \
			4_builtin/unset.c \
			4_builtin/export.c \
			4_builtin/cd.c \
			4_builtin/env.c \
			5_parsing/lexer.c \
			5_parsing/lexer_utils.c \
			5_parsing/parser.c \
			5_parsing/parsing_print.c \
			6_pipex/pipex.c \
			6_pipex/utils.c \
			main/main.c
			#main/test.c

OBJS_S	=  $(SRCS_S:.c=.o)

LIBFT_PATH  = 1_libft
LIBFT	= $(LIBFT_PATH)/libft.a

all:		$(NAME) 

${NAME}: ${OBJS_S}
	${MAKE} -C $(LIBFT_PATH)
	${CC} ${CFLAGS} $(OBJS_S) $(LIBFT) $(EXCFLGS) -o ${NAME}

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

.PHONY:		all clean fclean re