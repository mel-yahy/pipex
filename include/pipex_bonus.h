#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include "str_utils.h"

# define IN_FD 0
# define OUT_FD 1

# define NOT_FOUND 127

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif // !BUFFER_SIZE

# define MAX_CMDS 1000

typedef struct s_pipeline
{
	int	fds[2];
	int	ids[MAX_CMDS];
	int	pipes[MAX_CMDS - 1][2];
	int	cmd_count;
}	t_pipeline;

char	*get_next_line(int fd);

void	init_pipeline(t_pipeline *pipeline, char **argv, int argc,
			int here_doc);
void	execute_cmds(t_pipeline *pipeline, char **argv, char **envp);

int		ft_here_doc(char *limiter);

void	create_fork(int *id);
void	create_pipe(int *pipefd);
void	create_pipes(int (*pipes)[2], int cmd_count);
void	close_pipes(int (*pipes)[2], int last_pipe);
int		wait_for_children(int *ids, int cmd_count);

void	execute_cmd(char *cmd_string, char **envp);

void	open_files(int argc, char **argv, int *fds, int here_doc);
void	close_fds(int fds[2]);

char	*find_cmd_path(char *cmd, char **envp);
void	free_tab(char **tab);

#endif // !PIPEX_BONUS_H
