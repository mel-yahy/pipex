#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include "str_utils.h"

# define IN_FD 0
# define OUT_FD 1

# define NOT_FOUND 127

void	create_fork(int *id);
void	create_pipe(int *pipefd);
int		wait_for_children(int child_1, int child_2);

void	execute_cmd(char *cmd_string, char **envp);
void	run_cmd1(int *fds, int *pipefd, char *cmd_string, char **envp);
void	run_cmd2(int *fds, int *pipefd, char *cmd_string, char **envp);

void	open_files(char *infile, char *outfile, int *fds);
char	*find_cmd_path(char *cmd, char **envp);
void	free_tab(char **tab);

#endif // !PIPEX_H
