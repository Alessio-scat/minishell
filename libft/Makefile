.PHONY: all clean fclean re bonus

NAME 		= libft.a

SRCS 		= ft_isspace.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_printf.c ft_convert_%c_%s.c ft_convert_%p.c ft_convert_hex.c ft_convert_nbr_unsign.c ft_convert_nbr.c get_next_line_bonus.c get_next_line_utils_bonus.c ft_strncpy.c ft_is_quote.c ft_split_no_quote.c
OBJS 		= ${SRCS:.c=.o}

BONUS 		= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS_BONUS 	= ${BONUS:.c=.o}

HEADER 		= libft.h 

CC 			= gcc
FLAGS 		= -Wall -Wextra -Werror

LIB 		= ar rc

RM 			= rm -f

all:    	${NAME} Makefile

%.o: 		%.c $(HEADER) Makefile 
			@${CC} ${FLAGS} -include${HEADER} -c $< -o $@
#			@echo "..."

$(NAME):    $(OBJS) $(OBJS_BONUS) Makefile
			@${LIB} ${NAME} ${OBJS}
#			@echo "Loading ..."

bonus:		$(OBJS) $(OBJS_BONUS)
			@${LIB} ${NAME} $(OBJS) $(OBJS_BONUS)

clean:
			@${RM} ${OBJS} $(OBJS_BONUS)

fclean:		clean
			@${RM} ${NAME}

re:        	fclean all