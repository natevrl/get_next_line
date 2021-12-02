#include <unistd.h>
#include <fcntl.h>
#include "../42-libft/libft.h"
#include <stdlib.h>

# define BUFFER_SIZE 10000000

int	ftstrlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *join_all(int fd)
{
	char buffer[BUFFER_SIZE];
	static char *tmp;
	int read_return;

	if (!tmp)
		tmp = "";
	while ((read_return = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_return] = '\0';
		tmp = ft_strjoin(tmp, buffer);
	}
	return (tmp);
}

char *get_next_line(int fd)
{
	char	*the_line;
	char *str;
	static int i = 0;
	int y = 0;
	
	str = join_all(fd);
	if (str[i] == '\n')
		i++;
	y = i;
	while (str[i] != '\n' && str[i])
		i++;

	the_line = ft_substr(str, y, i - y + 1);
	return (the_line);
}

char *test(char *str)
{
	char *new;
	static int i = 0;
	int y = 0;

	if (str[i] == '\n')
		i++;
	y = i;
	while (str[i] != '\n' && str[i])
		i++;
	new = ft_substr(str, y, i - y + 1);
	printf("%d\n", i);
	return new;
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
	//printf("%s", test(str));	
	//printf("%s", test(str));	
	//printf("%s", test(str));	
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	//free(get_next_line(fd));
	//printf("%s\n", join_all(fd));
	
	return (0);
}

