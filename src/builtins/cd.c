/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 14:35:30 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/22 00:24:02 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*choose_path(int ac, char **av, char ***env)
{
	char	*path;

	if (ac == 1 || (ac == 2 && !ft_strcmp("~", av[1])))
		path = env_get("HOME", *env);
	else if (ac == 2 && !ft_strcmp("-", av[1]))
		path = env_get("OLDPWD", *env);
	else if (ac != 2)
	{
		ft_putstr_fd("shell: cd: wrong number of arguments\n", 2);
		return (NULL);
	}
	else if (ft_strlen(av[1]) > 1 && !ft_strncmp(av[1], "~", 1))
	{
		path = env_get("HOME", *env);
		path = ft_realloc((void*)path, ft_strlen(path),
				ft_strlen(av[1]) + ft_strlen(path) - 1);
		path = ft_strncat(path, av[1] + 1,
				ft_strlen(av[1]) + ft_strlen(path) - 1);
	}
	else
		path = ft_strdup(av[1]);
	return (path);
}

static void		show_error(char *path)
{
	ft_putstr_fd("shell: cd:", 2);
	if (access(path, F_OK) == -1)
		ft_putstr_fd("no such file or directory: ", 2);
	else if (access(path, R_OK) == -1)
		ft_putstr_fd("no read permission: ", 2);
	else if (access(path, X_OK) == -1)
		ft_putstr_fd("no permission denied: ", 2);
	else
		ft_putstr_fd("not a directory: ", 2);
	ft_putendl_fd(path, 2);
	ft_strdel(&path);
}

void			minishell_cd(int argc, char **argv, char ***env)
{
	char	*path;
	char	*pwd;

	path = NULL;
	if ((path = choose_path(argc, argv, env)) == NULL)
		return ;
	pwd = ft_strnew(PATH_MAX);
	pwd = getcwd(pwd, PATH_MAX);
	if (chdir(path) == -1)
	{
		show_error(path);
		ft_strdel(&pwd);
		return ;
	}
	env_set("OLDPWD", pwd, env);
	ft_strdel(&pwd);
	pwd = ft_strnew(PATH_MAX);
	pwd = getcwd(pwd, PATH_MAX);
	env_set("PWD", pwd, env);
	ft_strdel(&pwd);
	ft_strdel(&path);
}
