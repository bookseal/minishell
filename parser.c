#include "main.h"

t_pipex *parser(char *input, t_env *env)
{
	t_pipex *p_head;
	t_token *token_head;

	token_head = lexical_analyzer(input, env);
	if (!token_head)
		return (0);
	p_head = syntax_analyzer(token_head, env);
	if (!p_head)
		return (0);
	// p_head->env = env;
	// free(token_head);
	// return (p_head);
}