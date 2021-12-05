#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

# define BUFFER_SIZE 4

size_t ftstrlen(char const *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ftsubstr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new_str;

	if (!s)
		return (NULL);
	if ((size_t)start > ftstrlen(s))
	{
		new_str = malloc(sizeof(char) * 1);
		if (!new_str)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = s[start];
		start++;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ftstrdup(const char *src)

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

char	*ftstrjoin(char const *s1, char const *s2)
{
	int		y;
	int		i;
	size_t	total_size;
	char	*join;

	
	if (!s1)
		s1 = ftstrdup("");
	total_size = ftstrlen(s1) + ftstrlen(s2);
	join = malloc(sizeof(char const) * total_size + 1);
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
	//free((char *)s1);
	return (join);
}

// fonction qui check si il y a un '\n' dans le buffer
int	there_is_newline(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (0);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*new_line;
	char 		*test;
	static char *tmp = NULL;
	size_t	read_return;

	if (!tmp)
		tmp = ftstrdup("");
	read_return = BUFFER_SIZE;
	if (read(fd, buffer, 0) < 0 || fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (there_is_newline(tmp) == 0 && read_return > 0) 
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		buffer[read_return] = '\0';
		test = tmp;
		tmp = ftstrjoin(test, buffer);
		free(test);
	}
	if (there_is_newline(tmp))
	{
		new_line = ftsubstr(tmp, 0, there_is_newline(tmp) + 1);
		tmp = ftsubstr(tmp, there_is_newline(tmp) + 1, ftstrlen(tmp) - (there_is_newline(tmp) + 1));
	}
	else
		new_line = ftsubstr(tmp, 0, ftstrlen(tmp));
	if (!read_return)
	{
		free(tmp);			
		tmp = NULL;
		if (new_line[0] == '\0')
		{
			free(new_line);
			return (NULL);
		}
	}
	return (new_line);
}

#include <stdio.h>
/*int main()
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
	free(get_next_line(fd));
	return (0);
}*/
int    main()
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
}
