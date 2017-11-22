/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 22:17:22 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/22 23:50:37 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*expand_tilde(char *line, char *pos)
{
	char	*head;
	char	*home;
	size_t	len;

	home = env_get("HOME", *g_env);
	if (home == NULL)
		home = ft_strdup(" ");
	head = ft_strsub(line, 0, pos - line);
	pos[0] = '\0';
	len = ft_strlen(head) + ft_strlen(home);
	head = ft_realloc((void*)head, ft_strlen(head), len);
	head = ft_strncat(head, home, len);
	pos++;
	len = ft_strlen(head) + ft_strlen(pos);
	head = ft_realloc((void*)head, ft_strlen(head), len);
	head = ft_strncat(head, pos, len);
	ft_strdel(&line);
	return (head);
}

char			**expand_single_tilde(char **arg)
{
	int		i;

	i = -1;
	while (arg[++i])
	{
		if (!ft_strcmp(arg[i], "~"))
		{
			ft_memdel((void**)&(arg[i]));
			arg[i] = env_get("HOME", *g_env);
			if (arg[i] == NULL)
				arg[i] = ft_strdup(" ");
		}
	}
	return (arg);
}

char			*expand_tildas(char *line)
{
	char	*pos;

	while ((pos = ft_strstr(line, " ~/")))
		line = expand_tilde(line, pos + 1);
	while ((pos = ft_strstr(line, "\t~/")))
		line = expand_tilde(line, pos + 1);
	return (line);
}
