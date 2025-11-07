#include "../../include/pipex_bonus.h"

int	ft_here_doc(char *limiter)
{
	int		pipefd[2];
	char	*line;
	int		line_len;
	int		limiter_len;

	create_pipe(pipefd);
	limiter_len = strlen(limiter);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		line_len = strlen(line);
		if (limiter_len == line_len - 1
			&& strncmp(limiter, line, limiter_len) == 0)
			break ;
		write(pipefd[1], line, line_len);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (line != NULL)
		free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}
