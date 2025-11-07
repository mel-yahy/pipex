#include "../../../include/pipex_bonus.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif /* ifndef BUFFER_SIZE */

static char	*extract_line(char **left_over, char *nl_pos)
{
	char	*line;
	char	*tmp;

	if (*left_over == NULL || (*left_over)[0] == '\0')
		return (NULL);
	if (nl_pos != NULL)
	{
		line = ft_substr(*left_over, 0, nl_pos - *left_over + 1);
		tmp = *left_over;
		*left_over = strdup(nl_pos + 1);
		if ((*left_over)[0] == '\0')
		{
			free(*left_over);
			*left_over = NULL;
		}
		free(tmp);
	}
	else
	{
		line = strdup(*left_over);
		free(*left_over);
		*left_over = NULL;
	}
	return (line);
}

static int	read_into_buf(int fd, char *buf, char **left_over)
{
	int	bytes;

	bytes = read(fd, buf, BUFFER_SIZE);
	if (bytes < 0)
	{
		free(*left_over);
		*left_over = NULL;
		return (-1);
	}
	buf[bytes] = '\0';
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*left_over = NULL;
	char		*buf;
	char		*nl_pos;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	nl_pos = ft_strchr(left_over, '\n');
	while (nl_pos == NULL && read_into_buf(fd, buf, &left_over) > 0)
	{
		if (left_over == NULL)
			left_over = strdup(buf);
		else
		{
			tmp = left_over;
			left_over = ft_strjoin(left_over, buf);
			free(tmp);
		}
		nl_pos = ft_strchr(left_over, '\n');
	}
	free(buf);
	return (extract_line(&left_over, nl_pos));
}
