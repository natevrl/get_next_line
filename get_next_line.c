#include <unistd.h>
#include <fcntl.h>
#include "../42-libft/libft.h"
#include <stdlib.h>

# define BUFFER_SIZE 1000000

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
	static char *tmp = "";
	size_t read_return;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	
	while (!there_is_newline(tmp) && (read_return = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[read_return] = '\0';
		tmp = ft_strjoin(tmp, buffer);
	}
	if (there_is_newline(tmp))
	{
		new_line = ft_substr(tmp, 0, there_is_newline(tmp) + 1);
		tmp = ft_substr(tmp, there_is_newline(tmp) + 1, ftstrlen(tmp) - (there_is_newline(tmp) + 1));
	}
	else
	{
		new_line = ft_substr(tmp, 0, ftstrlen(tmp));
	}
	if (!read_return)
	{
		free(tmp);			
		return NULL;
	}

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
