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

int main(int argc, char *argv[], char *envp[]) {
	char			*input;
	t_pipex			*p_head;
	struct termios	term;
	t_env			*env;

	// ^c no print
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	check_signal();
	env = envp_to_t_env(envp);
	while (true)
	{
		input = readline("gichlee-0.1$ ");
		if (!input)
		{
			// printf("\033[1A");
			// printf("\033[10C");
			printf(" exit\n");
			exit(-1);
		}
		if (*input != '\0')
			add_history(input);
		if (*input != '\0' && !is_whitespace(input))
		{
			p_head = parser(input, env);
			// executor(p_head);
		}
		free(input);
		// TODO: handle $?
	}
	// strerror()
	return (g_exit_status  % 256);
}
