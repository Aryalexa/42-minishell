CC		= cc

# FT_SAN = -fsanitize=address
EXCFLGS = -lreadline -lncurses
CFLAGS	= -Wall -Wextra -Werror $(FT_SAN)

AR		= ar -rcs
RM		= /bin/rm -rf

NAME	= minishell
SRCDIR = src
OBJDIR = build
LIBFT_DIR  = $(SRCDIR)/1_libft
LIBFT	= $(LIBFT_DIR)/libft.a

SRCS = $(filter-out $(wildcard $(LIBFT_DIR)/*.c), $(shell find $(SRCDIR) -name '*.c'))
# SRCS	=	3_utils/utils.c \
# 			3_utils/debug.c \
# 			3_utils/error.c \
# 			3_utils/memory.c \
# 			4_builtin/builtin.c \
# 			4_builtin/expand.c \
# 			4_builtin/echo.c \
# 			4_builtin/exit.c \
# 			4_builtin/pwd.c \
# 			4_builtin/unset.c \
# 			4_builtin/export.c \
# 			4_builtin/cd.c \
# 			4_builtin/env.c \
# 			5_parsing/lexer.c \
# 			5_parsing/lexer_utils.c \
# 			5_parsing/parser.c \
# 			5_parsing/parsing_print.c \
# 			6_pipex/pipex.c \
# 			6_pipex/utils.c \
# 			main/main.c
# 			#main/test.c

$(info SRCS: $(SRCS))

#OBJS	=  $(SRCS:.c=.o)
# $(patsubst search_pattern, replace_pattern, text)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))


all:		$(NAME) 

${NAME}: ${OBJS}
	${MAKE} -C $(LIBFT_DIR)
	${CC} ${CFLAGS} $(OBJS) $(LIBFT) $(EXCFLGS) -o ${NAME}

# bonus:		$(NAME_C)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)
# .c.o:
# 			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) 

$(LIBFT):	
			make -C $(LIBFT_DIR) all

clean:
			make -C $(LIBFT_DIR) clean
			$(RM) $(OBJDIR)

fclean:		clean
			make -C $(LIBFT_DIR) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re