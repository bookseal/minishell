#include "main.h"

int	token_redirection_out(t_pipex *p, t_token **t)
{
	t_token *token;
	tags	tag;

	token = *t;
	tag = token->tag;
	token = token->next;
	if (!token || token->tag || token->value)
		return (-1);
	p->outfile = ft_strdup(token->value);
	if (tag == APPEND_OUT)
		p->is_outfile_append = true;
	if (!p->outfile)
		return (-2);
	token = token->next;
	return (0);
}

int	token_redirection_in(t_pipex *p, t_token **t)
{
	t_token *token;
	tags	tag;

	token = *t;
	tag = token->tag;
	token = token->next;
	if (!token || token->tag || token->value)
		return (-1);
	if (tag == REDIRECT_IN)
	{
		p->infile = ft_strdup(token->value);
	}
	else if (tag == HEREDOC)
		heredoc(p, t);
	if (!p->infile)
		return (-2);
	token = token->next;
	return (0);
}

int	token_to_redirection(t_pipex *p, t_token **t)
{
	t_token	*token;
	int		idx;

	token = *t;

	if (token->tag <= 1)
		return (0);
	else if (token->tag == REDIRECT_IN || token->tag == HEREDOC)
		return (token_redirection_in(p, t));
	else if (token->tag == REDIRECT_OUT || token->tag == APPEND_OUT)
		return (token_redirection_out(p, t));
	return (-3);
}