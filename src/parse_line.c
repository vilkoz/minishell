/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 14:29:19 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/22 23:47:40 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_cycle(int fd, char *buf, size_t current_buf_size)
{
	int		i;
	size_t	cur_byte;

	cur_byte = 0;
	while ((i = read(fd, (void*)(buf + cur_byte), 1)) > 0)
	{
		if (buf[cur_byte] == '\n')
		{
			buf[cur_byte] = '\0';
			return (buf);
		}
		cur_byte += i;
		if (cur_byte >= current_buf_size)
		{
			buf = ft_realloc(buf, sizeof(char) * current_buf_size,
				sizeof(char) * (current_buf_size + BUF_SIZE));
			current_buf_size += BUF_SIZE;
		}
	}
	ft_strdel(&buf);
	return (NULL);
}

char	*expand_variable(char *line, char *pos, size_t end, char *value)
{
	char		*tail;

	pos[0] = '\0';
	tail = ft_strdup(pos + end);
	end = ft_strlen(tail) + ft_strlen(value);
	value = ft_realloc((void*)value, ft_strlen(value), end + 1);
	value = ft_strncat(value, tail, end);
	ft_strdel(&tail);
	line = ft_realloc((void*)line, ft_strlen(line), ft_strlen(line) + end + 1);
	line = ft_strncat(line, value, ft_strlen(line) + end);
	ft_strdel(&value);
	return (line);
}

char	*expand_env(char *line)
{
	size_t	end;
	char	*pos;
	char	*search;
	char	*value;

	while ((pos = ft_strrchr(line, '$')))
	{
		end = 1;
		while (pos[end] && (ft_isalnum(pos[end]) || pos[end] == '_'))
			end++;
		pos[0] = ' ';
		if (end == 1 && pos[end] == '\0')
			continue ;
		search = ft_strsub(pos + 1, 0, end - 1);
		if (!(value = env_get(search, *g_env)))
			value = ft_strnew(0);
		ft_strdel(&search);
		line = expand_variable(line, pos, end, value);
	}
	return (line);
}

char	*read_line(int fd)
{
	char	*buf;

	if (fd < 0)
		return (NULL);
	buf = (char*)malloc(sizeof(char) * BUF_SIZE);
	if ((buf = read_cycle(fd, buf, BUF_SIZE)) == NULL)
		ft_putendl_fd("\nto exit type \"exit\"", 2);
	return (buf);
}

char	***parse_line(char *line)
{
	char	**commands;
	char	***ret;
	int		i;

	commands = ft_strsplit_quote(line, ';');
	ret = (char***)malloc(sizeof(char**) *
		(get_array_size((const char**)commands) + 1));
	i = -1;
	while (commands[++i])
	{
		commands[i] = expand_env(commands[i]);
		commands[i] = expand_tildas(commands[i]);
		ret[i] = ft_strsplit_arr_quote(commands[i], " \t");
		ret[i] = expand_single_tilde(ret[i]);
		ft_strdel(&(commands[i]));
	}
	ret[i] = NULL;
	ft_memdel((void*)&commands);
	return (ret);
}
