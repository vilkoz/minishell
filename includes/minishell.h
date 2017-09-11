#ifndef __MINISHEL_H
# define __MINISHEL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

# define BUF_SIZE 2048

char	**parse_line(char *line);
char	*read_line(int fd);
void	run_command(char **command, char **envp);

#endif
