/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:56:32 by nbenhado          #+#    #+#             */
/*   Updated: 2021/12/08 14:54:05 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ftstrlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ftstrdup(char *src)

{
	int		i;
	int		max;
	char	*dest;

	i = 0;
	max = 0;
	while (src[max])
		max++;
	dest = (char *)malloc(sizeof(char) * max + 1);
	if (!dest)
		return (NULL);
	while (i < max)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ftstrjoin(char *s1, char *s2)
{
	int		y;
	int		i;
	size_t	total_size;
	char	*join;

	if (!s1)
		s1 = ftstrdup("");
	total_size = ftstrlen(s1) + ftstrlen(s2);
	join = malloc(sizeof(char) * total_size + 1);
	if (join == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	y = 0;
	while (s2[y])
		join[i++] = s2[y++];
	join[i] = '\0';
	free(s1);
	return (join);
}

void	*free_and_return(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (NULL);
}

void	*freee(char **tmp, char **new_line)
{
	free(*tmp);
	*tmp = NULL;
	free(*new_line);
	return (NULL);
}
