NAME = minishell
CC = gcc
CFLAGS = 

READLINE_LIB 	= -lreadline -L/Users/gichlee/.brew/opt/readline/lib
READLINE_INC	= -I/Users/gichlee/.brew/opt/readline/include

SRCS =	main.c \
		main_check_signal.c \
		main_envp_to_t_env.c \
		parser.c \
		parser_lexical_analyzer.c \
		parser_replace_envs.c \
		parser_syntax_analyzer.c \
		executor.c \
		libft_ft_calloc.c \
		libft_ft_split.c \
		libft_ft_strjoin.c \
		libft_ft_strnstr.c \
		libft_ft_strtrim.c \
		libft_strings.c

HEADERS = main.h

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(READLINE_LIB) -g

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	rm -f minishell