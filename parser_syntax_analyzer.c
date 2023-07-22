#include "main.h"

char	**t_env_to_env_path(t_env *env_head)
{
	t_env	*env;

	env = env_head->next;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", ft_strlen("PATH")) == 0)
			break;
		env = env->next;
	}
	return(ft_split(env->value, ':'));
}

char	**token_to_t_cmd_argv(t_token *token_head)
{
	t_token	*token;
	char	**argv;
	int		argc;
	int		idx;

	token = token_head->next;
	argc = 0;
	while (token != 0)
	{
		if (token->tag != 0)
			break ;
		argc++;
		token = token->next;
	}
	token = token_head->next;
	argv = ft_calloc(argc + 1, sizeof(char *));
	idx = 0;
	while (idx < argc)
	{
		argv[idx] = token->value;
		token = token->next;
		idx++;
	}
	return (argv);
}

t_cmd	*token_to_t_cmd(t_token *token_head, t_env *env_head)
{
	t_cmd	*cmd;
	char	**env_path;
	t_token	*token;
	
	token = token_head->next;
	cmd = ft_calloc(1, sizeof(t_cmd));
	env_path = t_env_to_env_path(env_head);
	int i = 0;
	while (env_path[i])
	{
		cmd->path = ft_strjoin(env_path[i], token->value, '/');
		if (access(cmd->path, X_OK) == 0)
			break;
		i++;
	}
	if (env_path[i] == 0)
		exit(1);
	cmd->argv = token_to_t_cmd_argv(token_head);
	// TODO: cmd->builtin = is_builtin_cmd();
	return (cmd);
}

void	token_to_redirection(t_pipex *p, t_token *token_head)
{
	t_token		*token;
	int			idx;

	token = token_head->next;
	while (token)
	{
		if (token->tag == PIPE)
			printf("pipe");
		else if (token->tag == REDIRECT_IN)
		{
			token = token->next;
			p->infile = ft_strdup(token->value);
		}
		else if (token->tag == HEREDOC)
			;
		else if (token->tag == REDIRECT_OUT || token->tag == APPEND_OUT)
		{
			token = token->next;
			p->outfile = ft_strdup(token->value);
			// FIXME: append
		}
		token = token->next;
	}
}

bool is_single_command(t_pipex *p, t_token *token_head, t_env *env_head)
{
	t_token	*token;

	token = token_head->next;
	while (token)
	{
		if (token->tag == PIPE)
			return (false);
		token = token->next;
	}
	token = token_head->next;
	if (token->single_quotes || token->double_quotes)
		exit(1);
	p->cmd = token_to_t_cmd(token_head, env_head);
	token_to_redirection(p, token_head);
	return (true);
}

t_pipex	*syntax_analyzer(t_token	*token_head, t_env *env)
{
	t_token	*token;
	t_pipex *p_head;
	
	token = token_head->next;
	p_head = ft_calloc(1, sizeof(t_pipex));
	p_head->next = ft_calloc(1, sizeof(t_pipex));
	if (is_single_command(p_head->next, token_head, env))
		return (p_head);
	// TODO: else single_command
	return (p_head);
}