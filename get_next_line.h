#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

char	*get_next_line(int fd);

size_t	ftstrlen(const char *str);
char	*ftstrdup(const char *s1);
char	*ftstrdup(char const *src);
char	*ftstrjoin(char const *s1, char const *s2);
char	*ftsubstr(char const *s, unsigned int start, size_t len);
int there_is_newline(char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

#endif

