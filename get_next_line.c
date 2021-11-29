#include <unistd.h>
#include <fcntl.h>
#include "../42-libft/libft.h"

# define BUFFER_SIZE 100

int	ftstrlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *get_next_line(int fd)
{
	char	*buffer;
	int read_return;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	read_return = read(fd, buffer, BUFFER_SIZE);
	buffer[read_return] = '\0';
	return (buffer);
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
