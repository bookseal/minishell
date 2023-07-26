#include "main.h"

t_pipex *init_syntax(void)
{
	t_pipex	*p_head;

	p_head = ft_calloc(1, sizeof(t_pipex));
	return (p_head);
}

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

char	**token_to_t_cmd_argv(t_token **t)
{
	t_token	*token;
	char	**argv;
	int		argc;
	int		idx;

	token = *t;
	argc = 0;
	while (token != 0)
	{
		if (token->tag != 0)
			break ;
		argc++;
		token = token->next;
	}
	token = *t;
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

t_cmd	*token_to_t_cmd(t_token **token, t_env *env_head)
{
	t_cmd	*cmd;
	char	**env_path;
	
	cmd = ft_calloc(1, sizeof(t_cmd));
	// TODO: cmd->builtin = is_builtin_cmd();
	if (!cmd->builtin)
	{
		env_path = t_env_to_env_path(env_head);
		int i = 0;
		while (env_path[i])
		{
			cmd->path = ft_strjoin(env_path[i], (*token)->value, '/');
			if (access(cmd->path, X_OK) == 0)
				break;
			i++;
		}
		// TODO: free env_path
		if (env_path[i] == 0)
			return (0);
	}
	cmd->argv = token_to_t_cmd_argv(token);
	*token = (*token)->next;
	return (cmd);
}

t_pipex *token_to_pipex(t_token **token, t_env *env_head)
{
	t_pipex	*p;

	p = ft_calloc(1, sizeof(t_pipex));
	if ((*token)->single_quotes || (*token)->double_quotes)
		return (0);
	p->cmd = token_to_t_cmd(token, env_head);
	if (!p->cmd)
		return (0);
	token_to_redirection(p, token);
	return (p);
}

t_pipex	*syntax_analyzer(t_token	*token_head, t_env *env)
{
	t_token	*token;
	t_pipex	*p_head;
	t_pipex	*p;
	
	p_head = init_synax();
	token = token_head->next;
	p = p_head->next;
	p = token_to_pipex(&token, env);
	if (!p)
		return (0);
	// TODO: next token
	// while (token || token->tag == PIPE)
	// {
	// 	// TODO: pipe_tag();
	//	p = p->next;
	//	p = token_to_pipex(token, env);
	//	if (!p)
	//		return (0);
	// }
	// TODO: lstclear_token();
	return (p_head);
}