#include "../../include/pipex_bonus.h"

void	open_files(int argc, char **argv, int *fds, int here_doc)
{
	if (here_doc)
	{
		fds[IN_FD] = ft_here_doc(argv[2]);
		fds[OUT_FD] = open(argv[argc - 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	else
	{
		fds[IN_FD] = open(argv[1], O_RDONLY);
		if (fds[IN_FD] < 0)
			perror(argv[1]);
		fds[OUT_FD] = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	if (fds[OUT_FD] < 0)
		perror(argv[argc - 1]);
}

void	close_fds(int fds[2])
{
	close(fds[IN_FD]);
	close(fds[OUT_FD]);
}
