#include "../main.h"

// void	special_token_to_pipex(t_pipex *p, t_token	**token)
// {
// 	const char	*tags[10] = {"|", "<<", ">>", "<", ">", 0};
// 	int	idx;

// 	// TODO: What special is
// 	idx = 1;
// 	while (*token)
// 		{
			
// 			(*token) = (*token)->next;
// 		}
	
	
	
	
// 	(*token) = (*token)->next;
// 	// TODO: token to 
// }

// void	command_token_to_pipex(t_pipex *p, t_token **token)
// {
// 		(*token) = (*token)->next;
// }
bool is_builtin_cmd(t_pipex *p, t_token *token)
{
	return (false);
}

void	cmd_and_argument(t_pipex *p, t_token **token, t_env *env_head)
{
	t_env	*env;
	char	*cmd_with_path;
	char	**path;
	char	*cmd_name;
	
	cmd_name = (*token)->value;
	env = env_head->next;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", ft_strlen("PATH")) == 0)
			break;
		env = env->next;
	}
	path = ft_split(env->value, ':');
	int i = 0;
	while (path[i])
	{
		cmd_with_path = ft_strjoin(path[i], cmd_name, '/');
		if (access(cmd_with_path, X_OK) == 0)
			break;
		i++;
	}
	if (path[i] == 0)
		exit(1);
	p->cmd = ft_calloc(1, sizeof(t_cmd));
	p->cmd->argv = ft_calloc(3, sizeof(char *));
	p->cmd->argv[0] = cmd_name;
	p->cmd->path = cmd_with_path;
	*token = (*token)->next;
	if (!(*token)->special)
	{
		p->cmd->argv[1] = (*token)->value;
		*token = (*token)->next;
	}
}

bool single_command(t_pipex *p, t_token *token_head, t_env *env_head)
{
	t_token	*token;

	token = token_head->next;
	while (token)
		{
			if (token->special && ft_strncmp(token->special, "|", 1) == 0)
				return (false);
			token = token->next;
		}
	token = token_head->next;
	if (token->special || token->single_quotes || token->double_quotes)
		;
	else if (is_builtin_cmd(p, token))
		;
	else
		cmd_and_argument(p, &token, env_head);
	return (true);
}

t_pipex	*syntax_analyzer(t_token	*token_head, t_env *env)
{
	t_token	*token;
	t_pipex *p_head;
	
	token = token_head->next;
	p_head = ft_calloc(1, sizeof(t_pipex));
	p_head->next = ft_calloc(1, sizeof(t_pipex));
	if (single_command(p_head->next, token_head, env))
		return (p_head);
	return (p_head);
}