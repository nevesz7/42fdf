NAME 		= fdf

HEADERS_DIR		= ./includes/
SOURCES_DIR		= ./sources/

HEADERS_LIST	= fdf.h
SOURCES_LIST	= fdf.c \
				map.c \
				get.c \
				line.c \
				read.c \
				hooks.c \
				image.c \
				fdf_tests.c

HEADERS			= ${addprefix ${HEADERS_DIR}, ${HEADERS_LIST}}
SOURCES			= ${addprefix ${SOURCES_DIR}, ${SOURCES_LIST}}
INCLUDES		= -I ${HEADERS_DIR} -I ${LIBFT_HEADERS}

OBJECTS_DIR		= ./objects/
OBJECTS_LIST	= ${patsubst %.c, %.o, ${SOURCES_LIST}}
OBJECTS			= ${addprefix ${OBJECTS_DIR}, ${OBJECTS_LIST}}

LIBFT			= ${LIBFT_DIR}libft.a
LIBFT_DIR		= ./libft/
LIBFT_HEADERS	= ${LIBFT_DIR}includes/

CC				= cc
CFLAGS			= -Wall -Werror -Wextra
LIBRARIES		= -lm -lmlx -lXext -lX11

RM 				= rm -f

all:			${NAME}
#				@clear 
				@echo Everything went well!

${NAME}:		${LIBFT} ${OBJECTS_DIR} ${OBJECTS}
			${CC} ${CFLAGS} ${OBJECTS} ${LIBFT} ${LIBRARIES} ${INCLUDES} -o ${NAME}

${OBJECTS_DIR}:
			mkdir -p ${OBJECTS_DIR}
			@echo objects folder has been created!
${OBJECTS_DIR}%.o : ${SOURCES_DIR}%.c ${HEADERS}
			${CC} ${CFLAGS} -c ${INCLUDES} $< -o $@

${LIBFT}:
			make -sC ${LIBFT_DIR}
			@echo libft has been compiled!

clean:
			make -sC ${LIBFT_DIR} clean
			rm -rf ${OBJECTS_DIR}

fclean:		clean
			${RM} ${LIBFT}
			${RM} ${NAME}

re:			fclean all

.PHONY:		all, clean, fclean, re