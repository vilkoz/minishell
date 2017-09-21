#include "minishell.h"

char	*read_line(int fd)
{
	char	*buf;
	int		i;
	size_t	cur_byte;
	size_t	current_buf_size;

	if (fd < 0)
		return (NULL);
	current_buf_size = BUF_SIZE;
	buf = (char*)malloc(sizeof(char) * BUF_SIZE);
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
	if (i == 0)
		ft_putendl_fd("\nto exit type \"exit\"", 2);
	ft_strdel(&buf);
	return (NULL);
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
