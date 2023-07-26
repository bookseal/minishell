#include "main.h"

t_token *init_lexical(t_lexical *l, char *input, t_env *env_head)
{
	l->in_single_quotes = false;
	l->in_double_quotes = false;
	l->single_quotes = false;
	l->double_quotes = false;
	l->tag = 0;
	l->input_c = input;
	l->env_head = env_head;
	return (ft_calloc(1, sizeof(t_token)));
}

bool	is_token_when_quotes(char *input, t_lexical *l)
{
	// input is not both of them
	if (*input != '\'' && *input != '\"')
		return (false);
	// single quote
	if (*input == '\'')
	{
		l->in_single_quotes = !l->in_single_quotes;
		l->single_quotes = true;
	}
	// double quote
	else if (*input == '\"')
	{
		l->in_double_quotes = !l->in_double_quotes;
		l->double_quotes = true;
	}
	if (l->in_single_quotes || l->in_double_quotes)
	{
		l->input_c = input + 1;
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
	if (input - l->input_c <= 1)
	{
		l->input_c++;
		return (false);
	}
	return (true);
}

bool is_tag(char *input, t_lexical *l)
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
	t_token	*t;
	
	t = ft_calloc(1, sizeof(t_token));
	t->single_quotes = l->single_quotes;
	t->double_quotes = l->double_quotes;
	t->tag = l->tag;
	**input = 0;
	t->value = ft_strdup(l->input_c);
	if (!l->single_quotes)
		t->value = replace_envs(t->value, l->env_head);
	if (!l->single_quotes || !l->double_quotes)
		t->value = ft_strtrim(t->value, " ");
	l->single_quotes = false;
	l->double_quotes = false;
	l->input_c = *input + 1;
	return (t);
}

t_token	*token_new_special(char **input, t_lexical *l)
{
	t_token	*token;
	
	token = ft_calloc(1, sizeof(t_token));
	token->single_quotes = l->single_quotes;
	token->double_quotes = l->double_quotes;
	token->tag = l->tag;
	l->input_c++;
	if (l->tag == HEREDOC || l->tag == APPEND_OUT)
	{
		(*input)++;
		l->input_c++;
	}
	l->tag = 0;
	return (token);
}

t_token *lexical_analyzer(char *input, t_env *env_head)
{
	t_token		*t_head;
	t_token		*t;
	t_lexical	l;

	t_head = init_lexical(&l, input, env_head);
	t = t_head;
	while (*input != 0)
	{
		// quotes
		if (is_token_when_quotes(input, &l))
		{
			t->next = token_new(&input, &l);
			t = t->next;
			if ((*(l.input_c) == ' ' || *(l.input_c) == '\t') && l.input_c++ && input++)
				;
		}
		// space
		else if (is_space(input, &l))
		{
			t->next = token_new(&input, &l);
			t = t->next;
		}
		// tag 
		else if (is_tag(input, &l))
		{
			if (input != l.input_c)
			{
				t->next = token_new(&input, &l);
				t = t->next;
			}
			t->next = token_new_special(&input, &l);
			t = t->next;
		}
		input++;
	}
	// not finish quotes
	if (l.in_single_quotes || l.in_double_quotes)
		return (0);
	// rest of input
	if (l.input_c != input)
		t->next = token_new(&input, &l);
	return (t_head);
}