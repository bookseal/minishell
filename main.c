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

int setting_before_readline(int argc, char **envp, t_env **env)
{
	if (argc > 1)
	{
		perror("argument");
		return (1);
	}
	set_signals();
	*env = envp_to_t_env(envp);
	return (0);
}

int main(int argc, char *argv[], char *envp[]) {
	char			*input;
	t_pipex			*p_head;
	struct termios	term;
	t_env			*env;

	if (setting_before_readline(argc, envp, &env))
		return (g_exit_status  % 256);
	while (1)
	{
		input = readline("minishell $ ");
		if (!input)
			return (g_exit_status  % 256);
		if (*input != '\0')
			add_history(input);
		if (*input != '\0' && !is_whitespace(input))
		{
			p_head = parser(input, env);
			if (!p_head)
				return (g_exit_status  % 256);
			executor(p_head);
		}
		free(input);
		// TODO: handle $?
	}
	// TODO: lstclear(env);
	return (g_exit_status  % 256);
}
