/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 14:29:19 by vrybalko          #+#    #+#             */
/*   Updated: 2017/09/22 15:17:39 by vrybalko         ###   ########.fr       */
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
		ret[i] = ft_strsplit_quote(commands[i], ' ');
		ft_strdel(&(commands[i]));
	}
	ret[i] = NULL;
	ft_memdel((void*)&commands);
	return (ret);
}
