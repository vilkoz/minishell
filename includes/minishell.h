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
int		run_builtin(char **command, char **envp);

/*
** Builtins
*/

void	minishell_echo(int argc, char **argv, char ***env);
void	minishell_cd(int argc, char **argv, char ***env);
void	minishell_exit(int argc, char **argv, char ***env);
void	minishell_env(int argc, char **argv, char ***env);
void	minishell_getenv(int argc, char **argv, char ***env);

#endif
