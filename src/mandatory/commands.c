#include "../../include/pipex.h"

void	run_cmd1(int *fds, int *pipefd, char *cmd_string, char **envp)
{
	if (fds[IN_FD] == -1)
		exit(EXIT_FAILURE);
	close(fds[OUT_FD]);
	close(pipefd[0]);
	dup2(fds[IN_FD], STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(fds[IN_FD]);
	close(pipefd[1]);
	execute_cmd(cmd_string, envp);
}

void	run_cmd2(int *fds, int *pipefd, char *cmd_string, char **envp)
{
	if (fds[OUT_FD] == -1)
		exit(EXIT_FAILURE);
	close(fds[IN_FD]);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fds[OUT_FD], STDOUT_FILENO);
	close(fds[OUT_FD]);
	close(pipefd[0]);
	execute_cmd(cmd_string, envp);
}
