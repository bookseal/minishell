#include "main.h"

void	perror_and_exit(char *message)
{
	perror(message);
	exit(1);
}

void	exec_cmd_0(t_pipex	*p)
{
	execve(p->cmd->path, p->cmd->argv, NULL);
	perror("execve");
	exit(1);
}

int executor(t_pipex *p_head)
{
	int		pid;
	t_pipex	*p;

	p = p_head->next;
	pid = fork();
	if (pid < 0)
		perror_and_exit("fork");
	else if (pid == 0)
		exec_cmd_0(p);
	else
	{
		waitpid(pid, NULL, 0);
	}
	free(p_head);
	// TODO: clear_all()
	return (0);
}