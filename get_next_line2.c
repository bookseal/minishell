/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:34:17 by gichlee           #+#    #+#             */
/*   Updated: 2023/07/23 17:21:47 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_strchr_i(char *s, int c)
{
	char	*ptr_s;
	int		idx;	

	ptr_s = (char *)s;
	idx = 0;
	while (1)
	{
		if (ptr_s[idx] == (unsigned char)c)
			return (idx);
		else if (ptr_s[idx] == '\0')
			return (-1);
		else
			idx++;
	}
	return (-1);
}

char	*gnl_strjoin_free(char *s1, char *s2)
{
	int		len_total;
	char	*res;
	int		i;
	int		j;

	len_total = ft_strlen(s1) + ft_strlen(s2);
	res = calloc(sizeof(char), (len_total + 1));
	if (!res || !s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i] != 0)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		res[i + j] = s2[j];
		j++;
	}
	res[len_total] = '\0';
	free(s1);
	return (res);
}
