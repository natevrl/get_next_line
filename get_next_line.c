#include <unistd.h>
#include <fcntl.h>
#include "../42-libft/libft.h"
#include <stdlib.h>

# define BUFFER_SIZE 10

int	ft_strcmp(char	*s1, char	*s2)
{
	while (*s1 && *s2)
	{
		if (*s1 == *s2)
		{
			s1++;
			s2++;
		}
		else
			break ;
	}
	if (*s1 > *s2)
		return (1);
	else if (*s2 == *s1)
		return (0);
	else
		return (-1);
}

int	ftstrlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// fonction qui check si il y a un '\n' dans le buffer
int there_is_newline(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (0);
}

char *get_next_line(int fd)
{
	char buffer[BUFFER_SIZE];
	char *new_line;
	char *tmp;
	static char *stock_after_newline = NULL;
	int read_return;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	if (stock_after_newline[0] == "")
		return (NULL);
	if (stock_after_newline != NULL)
		tmp = stock_after_newline;
	else
		tmp = "";
	while ((read_return = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_return] = '\0';
		tmp = ft_strjoin(tmp, buffer);
		if (there_is_newline(tmp))
			break ;
	}
	if (there_is_newline(tmp))
	{
		//								STR		DEBUT 					SIZE TOTAL A COPIER
		stock_after_newline = ft_substr(tmp, there_is_newline(tmp) + 1, ftstrlen(tmp) - (there_is_newline(tmp) + 1));
		new_line = ft_substr(tmp, 0, there_is_newline(tmp) + 1);
	}
	else
		new_line = ft_substr(tmp, 0, ftstrlen(tmp));
	free(tmp);
	return (new_line);
}

#include <stdio.h>
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
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
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
