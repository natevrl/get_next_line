#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

char	*get_next_line(int fd);

size_t	ftstrlen(char *str);
char	*ftstrdup(char *src);
char	*ftstrjoin(char *s1, char *s2);
char	*after_newline(char *str);
int there_is_newline(char *str);
char	*before_newline(char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

#endif

