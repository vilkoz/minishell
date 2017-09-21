#ifndef __MINISHEL_H
# define __MINISHEL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

# define BUF_SIZE 2048
# ifndef PATH_MAX
#  define PATH_MAX 2048
# endif

char	***g_env;

char	**parse_line(char *line);
char	*read_line(int fd);
void	run_command(char **command, char ***envp);
int		run_builtin(char **command, char ***envp);

/*
** Builtins
*/

void	minishell_echo(int argc, char **argv, char ***env);
void	minishell_cd(int argc, char **argv, char ***env);
void	minishell_exit(int argc, char **argv, char ***env);
void	minishell_env(int argc, char **argv, char ***env);
void	minishell_getenv(int argc, char **argv, char ***env);
void	minishell_setenv(int argc, char **argv, char ***env);
void	minishell_unsetenv(int argc, char **argv, char ***env);

/*
** env.c
*/

char	*env_get(const char *name, char **env);
void	env_set(char *key, char *value, char ***env);

/*
** run_builtin.c
*/

int		get_array_size(const char **array);

#endif
