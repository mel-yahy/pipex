#include "../../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fds[2];
	int	pipefd[2];
	int	child_1;
	int	child_2;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	open_files(argv[1], argv[argc - 1], fds);
	create_pipe(pipefd);
	create_fork(&child_1);
	if (child_1 == 0)
		run_cmd1(fds, pipefd, argv[2], envp);
	create_fork(&child_2);
	if (child_2 == 0)
		run_cmd2(fds, pipefd, argv[3], envp);
	close(pipefd[0]);
	close(pipefd[1]);
	close(fds[IN_FD]);
	close(fds[OUT_FD]);
	return (wait_for_children(child_1, child_2));
}
