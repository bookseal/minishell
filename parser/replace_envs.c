#include "../main.h"

char	*replace_envs(char *start, t_env *env_head)
{
	char  *str;
	char	*new_str;
	char	*env_name;
	int	len_env_name;
	int i;
	t_env	*env;
	
	str = ft_strdup(start);
	while (ft_strchr(str, '$'))
	{	
		env_name = ft_strchr(str, '$') + 1;
		len_env_name = 0;
		while (env_name[len_env_name] != ' ' && env_name[len_env_name] != '\"' && env_name[len_env_name] != 0)
				len_env_name++;
		env = env_head->next;
		while (env)
			{
				if (!ft_strncmp(env_name, env->key, len_env_name))
					break;
				env = env->next;
			}
		new_str = (char *)malloc(sizeof(char) * (ft_strlen(env->value) + ft_strlen(str) + 1));
		ft_strlcat(new_str, str, env_name - str);
		ft_strlcat(new_str, env->value, ft_strlen(new_str) + ft_strlen(env->value) + 1);
		ft_strlcat(new_str, &env_name[len_env_name], ft_strlen(new_str) + ft_strlen(str) + 1);
		free(str);
		str = new_str;
	}
	return (str);
}