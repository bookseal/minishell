#include "main.h"

void	init_lexical(t_lexical *l, char *input, t_env *env_head)
{
	l->in_single_quotes = false;
	l->in_double_quotes = false;
	l->single_quotes = false;
	l->double_quotes = false;
	l->tag = 0;
	l->start = input;
	l->env_head = env_head;
}

bool	is_token_when_quotes(char *input, t_lexical *l)
{
	if (*input != '\'' && *input != '\"')
		return (false);
	if (*input == '\'')
	{
		l->in_single_quotes = !l->in_single_quotes;
		l->single_quotes = true;
	}
	else if (*input == '\"')
	{
		l->in_double_quotes = !l->in_double_quotes;
		l->double_quotes = true;
	}
	if (l->in_single_quotes || l->in_double_quotes)
	{
		l->start = input + 1;
		return (false);
	}
	else
		return (true);
}

bool is_space(char *input, t_lexical *l)
{
	if (!(*input == ' ' || *input == '\t'))
		return (false);
	if (l->in_single_quotes || l->in_double_quotes)
		return (false);
	if (input - l->start <= 1)
	{
		l->start++;
		return (false);
	}
	return (true);
}

bool is_special(char *input, t_lexical *l)
{
	const char	*tags[7] = {"", "|", "<", "<<", ">", ">>", 0};
	int			idx;

	idx = 1;
	while (tags[idx])
	{
		if (ft_strncmp(input, tags[idx], ft_strlen(tags[idx])) == 0)
		{
			l->tag = idx;
			return (true);
		}
		idx++;
	}
	return (false);
}

t_token	*token_new(char **input, t_lexical *l)
{
	t_token	*token;
	
	token = ft_calloc(1, sizeof(t_token));
	token->single_quotes = l->single_quotes;
	token->double_quotes = l->double_quotes;
	token->tag = l->tag;
	**input = 0;
	token->value = ft_strdup(l->start);
	if (!l->single_quotes)
		token->value = replace_envs(token->value, l->env_head);
	if (!l->single_quotes || !l->double_quotes)
		token->value = ft_strtrim(token->value, " ");
	l->single_quotes = false;
	l->double_quotes = false;
	l->start = *input + 1;
	return (token);
}

t_token	*token_new_special(char **input, t_lexical *l)
{
	t_token	*token;
	
	token = ft_calloc(1, sizeof(t_token));
	token->single_quotes = l->single_quotes;
	token->double_quotes = l->double_quotes;
	token->tag = l->tag;
	l->start++;
	if (l->tag == HEREDOC || l->tag == APPEND_OUT)
	{
		(*input)++;
		l->start++;
	}
	l->tag = 0;
	return (token);
}

t_token *lexical_analyzer(char *input, t_env *env_head)
{
	t_token		*token_head;
	t_token		*token;
	t_lexical	l;

	init_lexical(&l, input, env_head);
	token_head = ft_calloc(1, sizeof(t_token));
	token = token_head;
	while (*input != 0)
	{
		if (is_token_when_quotes(input, &l))
		{
			token->next = token_new(&input, &l);
			token = token->next;
			if ((*(l.start) == ' ' || *(l.start) == '\t') && l.start++ && input++)
				;
		}
		else if (is_space(input, &l))
		{
			token->next = token_new(&input, &l);
			token = token->next;
		}
		else if (is_special(input, &l))
		{
			if (input != l.start)
			{
				token->next = token_new(&input, &l);
				token = token->next;
			}
			token->next = token_new_special(&input, &l);
			token = token->next;
		}
		input++;
	}
	if (l.in_single_quotes || l.in_double_quotes)
		exit(1);
	if (l.start != input)
		token->next = token_new(&input, &l);
	return (token_head);
}