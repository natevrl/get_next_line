#include <unistd.h>
#include <fcntl.h>
#include "../42-libft/libft.h"
#include <stdlib.h>

# define BUFFER_SIZE 8

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

	tmp = "";
	read(fd, buffer, BUFFER_SIZE);
	tmp = ft_strjoin(tmp, buffer);
	if (!(str = malloc(sizeof(char) * ft_strlen(tmp) + 1)))
		return (NULL);
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
	static char	*buffer;
	char *str;
	int i = 0;

	str = join_all(fd);

	while (str[i] != '\n' && str[i])
		i++;
	buffer = ft_substr(str, 0, i);
	
	return buffer;
}



int main()
{
	int fd;
	//char buf[BUF_SIZE + 1];
	//int ret;
	//int i = 0;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("open() error", 1);
		return (0);
	}
	printf("%s\n", get_next_line(fd));
	//printf("%s\n", join_all(fd));
	
	/*ret = read(fd, buf, BUF_SIZE);
	buf[ret] = '\0';
	while (buf[i] != '\n')
	{
		write(1, &buf[i], 1);
		i++;
	}
	ft_putnbr_fd(ret, 1);
	write(1, "\n", 1);*/
	return (0);
}
