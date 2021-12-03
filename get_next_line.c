#include <unistd.h>
#include <fcntl.h>
#include "../42-libft/libft.h"
#include <stdlib.h>

# define BUFFER_SIZE 1

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

//int stock_after_newline()

char *join_all(int fd)
{
	char buffer[BUFFER_SIZE];
	char *new_line;
	char *tmp;
	static char *stock_after_newline = NULL;
	int read_return;

	if (stock_after_newline != NULL)
		tmp = stock_after_newline;
	else
		tmp = "";
	while ((read_return = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_return] = '\0';
		tmp = ft_strjoin(tmp, buffer);
		if (there_is_newline(tmp))
		{
			break ;
		}
	}
	//								STR		DEBUT 					SIZE TOTAL A COPIER
	stock_after_newline = ft_substr(tmp, there_is_newline(tmp) + 1, ftstrlen(tmp) - (there_is_newline(tmp) + 1));
	new_line = ft_substr(tmp, 0, there_is_newline(tmp) + 1);
	return (new_line);
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
	printf("%s", join_all(fd));
	printf("%s", join_all(fd));
	printf("%s", join_all(fd));
	printf("%s", join_all(fd));
	printf("%s", join_all(fd));
	
	return (0);
}

