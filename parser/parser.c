#include "../main.h"

t_pipex *parser(char *input, char *envp[])
{
	t_pipex *p_head;
	t_token *token_head;
	t_env		*env;
	
	env = envp_to_t_env(envp);
	token_head = lexical_analyzer(input, env);
	p_head = syntax_analyzer(token_head, env);
	p_head->env = env;

	free(token_head);
	return (p_head);
}