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
	// char	*test = "ls -l | grep \"cat $HOME $HOME\" > file.txt";
	// char	*test = "echo Hello;  | echo \"World\"";
	// char	*test = "echo Hello;";
	char	*test = "cat main.c";
	// char	*test = "echo \"$HOME   echo\"";
	char	*input;
	// input = ft_calloc(sizeof(char), 100);	
	// ft_strlcpy(input, test, ft_strlen(test) + 1);

	t_pipex	*p_head;
	struct termios	term;
	// TODO: tcgetattr(STDIO_FILENO, &term);
	// TODO: signal_handler();

	while (true)
	{
		input = readline("gichlee-0.1$ ");
		if (!input)
			;
		if (*input != '\0')
			add_history(input);
		if (*input != '\0' && !is_whitespace(input))
		{
			p_head = parser(input, envp);
			executor(p_head);
		}
		// TODO: handle heredoc
		// TODO: handle $?
	}
	
	return (g_exit_status);
}
