#include "get_next_line.h"

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
	{
		join[i] = s2[y];
		i++;
		y++;
	}
	join[i] = '\0';
	free(s1);
	return (join);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*new_line;
	static char	*tmp = NULL;
	int			read_return;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE < 1)
	{
		free(buffer);
		return (NULL);
	}
	read_return = 1;	
	while (!there_is_newline(tmp) && read_return > 0)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (read_return == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_return] = '\0';
		tmp = ftstrjoin(tmp, buffer);
	}
	free(buffer);
	new_line = before_newline(tmp);
	tmp = after_newline(tmp);
	if (!read_return && ftstrlen(tmp) == 0 && ftstrlen(new_line) == 0)
	{
		free(tmp);
		tmp = NULL;
		free(new_line);
		return (NULL); // faire la start ou tu retourne un fonction qui retourne NULL
	}
	return (new_line);
}

#include <stdio.h>
#include "../42-libft/libft.h"
int main()
{
	int fd;
	//char str[] = "qwer\ntyyy\nxxxx";

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("open() error", 1);
		return (0);
	}
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	free(get_next_line(fd));
	return (0);
}
/*int    main()
{
    int        i;
    int        fd;
    char    *str;

    i = 1;
    fd = open("test.txt", O_RDONLY);
    if (!fd)
    {
        printf("fd opening error\n");
        return (-1);
    }
    str = get_next_line(fd);
    while (str)
    {
        printf("Line %d = %s", i, str);
	  free(str);
        str = get_next_line(fd);
        i++;
    }
    free(str);
    close(fd);
    return (0);
}*/
