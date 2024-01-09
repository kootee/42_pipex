NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

DEBUGFLAGS = -g

SRCS = pipex.c \
		pipex_utils.c \
		libft/libft.a

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} -g ${DEBUGFLAGS} ${SRCS} -o ${NAME}

libft/libft.a:
	${MAKE} -C libft

clean:
	rm -f ${OBJS}
	make clean -C libft

fclean: clean
	rm -f ${NAME}
	make fclean -C libft

re: fclean all