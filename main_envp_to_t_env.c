#include "main.h"

t_env	*envp_to_t_env(char	*envp[])
{
	t_env	*env_head;
	t_env *env;
	int		idx;
	char	*ch_ptr;

	env_head = ft_calloc(1, sizeof(t_env));
	env = env_head;
	idx = 0;
	while (envp[idx] != 0)
		{
			env->next = ft_calloc(1, sizeof(t_env));
			env = env->next;
			ch_ptr = envp[idx];
			while (*ch_ptr != '=')
				ch_ptr++;
			*ch_ptr = 0;
			env->key = ft_strdup(envp[idx]);
			env->value = ft_strdup(ch_ptr + 1);
			idx++;
		}
	env->next = 0;
	return (env_head);
}