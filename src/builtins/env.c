/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 14:30:44 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/21 23:59:08 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**add_to_env(char ***env, char *key, char *value)
{
	int		size;
	int		i;
	char	*tmp_key;
	char	*tmp;

	size = -1;
	while ((*env)[++size])
		;
	*env = (char**)ft_realloc((void*)*env, sizeof(char*) * (size + 1),
			sizeof(char*) * (size + 2));
	i = -1;
	while (++i < size
		&& ft_strncmp(key, (*env)[i], ft_strlen_chr((*env)[i], "=")) > 0)
		;
	tmp = (*env)[i];
	tmp_key = ft_strjoin(key, "=");
	(*env)[i] = ft_strjoin(tmp_key, value);
	ft_strdel(&tmp_key);
	while (++i < size + 1)
	{
		tmp_key = (*env)[i];
		(*env)[i] = tmp;
		tmp = tmp_key;
	}
	return (*env);
}

void			minishell_setenv(int argc, char **argv, char ***env)
{
	char	*key;
	char	*value;

	if (argc != 3)
	{
		ft_putendl_fd("usage: setenv key value", 2);
		return ;
	}
	key = argv[1];
	value = argv[2];
	env_set(key, value, env);
}

void			minishell_getenv(int argc, char **argv, char ***env)
{
	char	*value;

	if (argc != 2)
	{
		ft_putendl_fd("usage: getenv key", 2);
		return ;
	}
	value = env_get(argv[1], *env);
	if (value == NULL)
	{
		ft_putendl_fd("no such key!", 2);
		return ;
	}
	ft_putendl(value);
	ft_strdel(&value);
}

void			env_set(char *key, char *value, char ***env)
{
	char	*tmp_line;
	char	*tmp_key;
	int		i;

	tmp_key = env_get(key, *env);
	if (tmp_key == NULL)
		*env = add_to_env(env, key, value);
	else
	{
		ft_strdel(&tmp_key);
		i = -1;
		while ((*env)[++i] != NULL)
			if (!ft_strncmp(key, (*env)[i], ft_strlen(key)))
			{
				tmp_line = (*env)[i];
				tmp_key = ft_strjoin(key, "=");
				(*env)[i] = ft_strjoin(tmp_key, value);
				ft_strdel(&tmp_key);
				ft_strdel(&tmp_line);
				break ;
			}
	}
}

char			*env_get(const char *name, char **env)
{
	int		i;
	char	*ret;
	char	*value;

	i = -1;
	while (env[++i] != NULL)
	{
		if (!ft_strncmp(name, env[i], ft_strlen(name)) &&
			(value = ft_strchr(env[i], '=')) != NULL)
		{
			ret = ft_strdup(value + 1);
			return (ret);
		}
	}
	return (NULL);
}
