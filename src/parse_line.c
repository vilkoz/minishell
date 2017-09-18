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
	while ((i = read(fd, (void*)(buf + cur_byte), 1)) >= 0)
	{
		if (buf[cur_byte] == '\n' || i == 0)
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

char	**parse_line(char *line)
{
	char	**command;

	command = ft_strsplit_quote(line, ' ');
	return (command);
}
