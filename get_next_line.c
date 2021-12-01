#include <unistd.h>
#include <fcntl.h>
#include "../42-libft/libft.h"
#include <stdlib.h>

# define BUFFER_SIZE 6

int	ftstrlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/* idee fonctions : 
 * read_one_buffer : contients le read() qui lit le buffer et lenvoie a new_line_tchecker
 * new_line_checker : tcheck tout les caracteres du buffer pour trouver une newline
 * deux possibilites :
 * ====================> 1 : le buffer contiens une newline
 * --> memoriser lindex de cette newline et le renvoyer, 
 * --> malloc lindex + 1 pour '\0'
 * --> get_next_line renvoie la ligne
 * -->
 * ====================> 2 : le buffer ne contient pas de newline
 * */

// fonction qui check si il y a un '\n' dans le buffer
int new_line_checker(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (0);
}

char *join_all(int fd)
{
	char buffer[BUFFER_SIZE];
	char *tmp;
	char *str;
	int i = 0;
	int read_return;

	tmp = "";
	while ((read_return = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_return] = '\0';
		printf("%c\n", buffer[read_return - 1]);
		//printf("%d\n", read_return);
		tmp = ft_strjoin(tmp, buffer);
	}
	//printf("%c\n", tmp[0]);
	str = malloc(sizeof(char) * ft_strlen(tmp) + 1);
	if (!str)
	{
		printf("alloc echouer ptain\n");
		return (NULL);
	}
	while (tmp[i])
	{
		str[i] = tmp[i];
		i++;
	}
	str[i] = '\0';
	free(tmp);
	return (str);
}

char *get_next_line(int fd)
{
	char	*the_line;
	char *str;
	int i = 0;
	int y = 0;

	y += i;
	str = join_all(fd);
	//printf("str ; %s\n", str);
	while (str[i] != '\n' && str[i] != '\0')
	{
		i++;
		printf("ca rentre");
	}

	printf("i = %d\n", i);
	the_line = ft_substr(str, y, i);
	i++;
	//free(str);
	return (the_line);
}

int test()
{
	static int i = 0;
	char str[] = "test1test1test1qqq";
	while (str[i] != '1' && str[i])
		i++;
	i++;
	printf("test111");
	return i;
}

int main()
{
	int fd;
	char *str;
	//char *gnl;
	//char *gnl2;
	//char *gnl3;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("open() error", 1);
		return (0);
	}
	str = join_all(fd);
	printf("%s", str);
	free(str);
	//printf("%d\n", test());
	
	return (0);
}
