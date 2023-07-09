#include "main.h"

int	g_exit_status = 0;

bool	is_whitespace(char *str)
{
	while (*str)
	{
		if (*str != 32 && !(*str >= 9 && *str <= 13))
			return (false);
		str++;
	}
	return (true);
}

void signal_handler(int signal_num) {
   	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal_num == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

int main(int argc, char *argv[], char *envp[]) {
	// char	*test = "ls -l | grep \"cat $HOME $HOME\" > file.txt";
	char	*test = "cat main.c";
	char	*input;
	// input = ft_calloc(sizeof(char), 100);	
	// ft_strlcpy(input, test, ft_strlen(test) + 1);
	t_pipex	*p_head;
	struct termios	term;
	t_env		*env;
	// TODO: tcgetattr(STDIO_FILENO, &term);
	// TODO: signal_handler();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);

	env = envp_to_t_env(envp);
	while (true)
	{
		input = readline("gichlee-0.1$ ");
		if (!input)
			;
		if (*input != '\0')
			add_history(input);
		if (*input != '\0' && !is_whitespace(input))
		{
			p_head = parser(input, env);
			executor(p_head);
		}
		free(input);
		// TODO: handle heredoc
		// TODO: handle $?
	}
	// TODO: tcsetattr()
	return (g_exit_status);
}
