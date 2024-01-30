/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:26:52 by ktoivola          #+#    #+#             */
/*   Updated: 2024/01/30 13:03:30 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_execute(t_pipex *pipex_args, int cmd_n, char **env)
{
	char **cmds;
	char *exec_path;
	
	cmds = ft_parse_commands(pipex_args->cmd_args[cmd_n]);
	if (cmds == NULL)
		exit(127);
	if (access(cmds[0], F_OK & X_OK) == 0)
		exec_path = cmds[0];
	else
		exec_path = ft_get_env_paths(pipex_args, cmds);
	if (execve(exec_path, cmds, env) == -1)
	{		
		free(exec_path);
		ft_free_strs(cmds);
		perror("execve failed");
		exit(127);
	}
}

static void	child_process(t_pipex *pipex_args, char **env)
{
	int	fd_in;

	fd_in = open(pipex_args->cmd_args[1], O_RDONLY);
	if (fd_in < 0)
	{
		perror("pipex: input");
		exit(78);
	}
	dup2(fd_in, STDIN_FILENO); // has to be from fd where is read from
	dup2(pipex_args->pipe[1], STDOUT_FILENO); // fd where to write
	close(pipex_args->pipe[0]); // this one (read end of pipe) is NOT USED IN CHILD PROCESS!
	//close(pipex_args->fd_IO[1]);
	ft_execute(pipex_args, 2, env);
}

static void	parent_process(t_pipex *pipex_args, char **env)
{
	int	fd_out;
	
	fd_out = open(pipex_args->cmd_args[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd_out < 0)
	{
		perror("pipex: output");
		exit(79);
	}
	dup2(fd_out, STDOUT_FILENO); //where to write to
	dup2(pipex_args->pipe[0], STDIN_FILENO); //where to read from
	close(pipex_args->pipe[1]); // this one (write end of pipe) is NOT USED IN CHILD PROCESS!
	//close(pipex_args->fd_IO[0]); //close the input file
	ft_execute(pipex_args, 3, env); //or second to last one 
}

static void	ft_pipex(t_pipex *pipex_args, char **env)
{
	pid_t	pid;
	int		i;
	
	i = 0;
	if (pipe(pipex_args->pipe) == -1)
	{
		perror("Pipe failed");
		exit(3);
	}
	pid = fork(); 
	if (pid == -1)
	{
		perror("Fork failed");
		exit(4);
	}
	if (pid == 0)
		child_process(pipex_args, env);
	else
	{
		//wait(&pid);
		parent_process(pipex_args, env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	
	t_pipex *pipex_args;
	//char *null_env[] = {NULL};

	if (argc != 5)
	{
		perror("invalid no of parameters given"); //return error about invalid arguments
		exit(5);
	}
	pipex_args = malloc(sizeof(t_pipex));
	if (pipex_args == NULL)
		exit(6);
	ft_init_pipex(pipex_args, argc); // set default values
	pipex_args->cmd_args = argv;
	pipex_args->env_paths = envp;
	//pipex_args->env_paths = null_env;
	ft_pipex(pipex_args, envp);
	//ft_close_all(pipex_args);
	//return (0);
}
