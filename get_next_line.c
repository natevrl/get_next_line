/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:41:26 by nbenhado          #+#    #+#             */
/*   Updated: 2021/12/07 16:50:51 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	there_is_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '\n')
		return (1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*before_newline(char *str)
{
	int		i;
	char	*new_str;

	if (!str)
		return (NULL);
	if (str[0] == '\n')
		return (ftstrdup("\n"));
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	new_str = malloc(sizeof(char) * (i + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
		if (i > 0 && str[i - 1] == '\n')
			break ;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*after_newline(char *str)
{
	int		i;
	int		y;
	char	*new_str;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	new_str = malloc(sizeof(char) * (ftstrlen(str) - i + 1));
	if (!new_str)
		return (NULL);
	y = 0;
	while (str && str[i])
		new_str[y++] = str[++i];
	new_str[y] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*new_line;
	static char	*tmp = NULL;
	int			read_return;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE < 1)
		return (free_and_return(buffer, NULL));
	read_return = 1;
	while (!there_is_newline(tmp) && read_return > 0)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (read_return == -1)
			return (free_and_return(buffer, NULL));
		buffer[read_return] = '\0';
		tmp = ftstrjoin(tmp, buffer);
	}
	free(buffer);
	new_line = before_newline(tmp);
	tmp = after_newline(tmp);
	if (!read_return && ftstrlen(tmp) == 0 && ftstrlen(new_line) == 0)
		return (freee(&tmp, &new_line));
	return (new_line);
}
