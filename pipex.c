/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:26:52 by ktoivola          #+#    #+#             */
/*   Updated: 2024/01/12 11:37:53 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_execute(t_pipex *pipex_args, int cmd_n)
{
	char **cmds;
	char *exec_path;
	
	cmds = ft_split(pipex_args->cmd_args[cmd_n], ' '); //malloc protect
	exec_path = ft_get_env_paths(pipex_args, cmd_n);
	if (exec_path == NULL)
		perror("No exec path fund for command");
	if (execve(exec_path, cmds, pipex_args->env_paths) < 0)
	{		
		free(exec_path);
		ft_free_on_error(cmds);
		perror("execve faliled");
		exit(EXIT_EXEC_ERROR);
	}
}

static void	child_process(t_pipex *pipex_args, int	cmd_num)
{
	close(pipex_args->fd_IO[1]);
	close(pipex_args->pipe[0]); // this one (read end of pipe) is NOT USED IN CHILD PROCESS!
	dup2(pipex_args->fd_IO[0], STDIN_FILENO); // has to be from fd where is read from
	dup2(pipex_args->pipe[1], STDOUT_FILENO); // fd where to write
	ft_execute(pipex_args, cmd_num);
}

static void	parent_process(t_pipex *pipex_args)
{
	close(pipex_args->fd_IO[0]); //close the input file
	close(pipex_args->pipe[1]); // this one (write end of pipe) is NOT USED IN CHILD PROCESS!
	dup2(pipex_args->pipe[0], STDIN_FILENO); //where to read from
	dup2(pipex_args->fd_IO[1], STDOUT_FILENO); //where to write to
	ft_execute(pipex_args, pipex_args->cmd_count + 1); //or second to last one 
}

static void	ft_pipex(t_pipex *pipex_args)
{
	pid_t	pid;
	int		i;
	
	i = 0;
	if (pipe(pipex_args->pipe) < 0)
		exit(EXIT_PIPE_ERROR);
	pid = fork(); 
	if (pid < 0)
	{
		perror("Fork failed");
		exit(EXIT_FORK_ERROR);
	}
	if (pid == 0)
		child_process(pipex_args, 2);
	else
	{
		wait(&pid);
		parent_process(pipex_args);
	}
}

int	main(int argc, char **argv, char **envp)
{
	
	t_pipex *pipex_args;

	if (argc != 5)
		perror("invalid no of parameters given"); //return error about invalid arguments
	pipex_args = malloc(sizeof(t_pipex));
	if (pipex_args == NULL)
		return (-1); //add error
	ft_init_pipex(pipex_args, argc); // set default values
	ft_check_args(pipex_args, argv, envp); //opens files and sets fds to pipex args
	ft_pipex(pipex_args);
	ft_close_all(pipex_args);
	return (0);
}
