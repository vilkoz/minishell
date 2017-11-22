/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 14:26:17 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/22 23:40:34 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINISHELL_H
# define __MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

# define BUF_SIZE 2048
# ifndef PATH_MAX
#  define PATH_MAX 2048
# endif

char	***g_env;

char	***parse_line(char *line);
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

/*
** main.c
*/

void	put_prompt(char **env);

/*
** signal.c
*/

void	sigint(int sig);

/*
** tilde.c
*/

char	**expand_single_tilde(char **arg);
char	*expand_tildas(char *line);

#endif
