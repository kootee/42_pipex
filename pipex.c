/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:26:52 by ktoivola          #+#    #+#             */
/*   Updated: 2024/01/06 15:54:21 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(char **cmds_path, char **env)
{
	char **cmds;
	char *path;
	
	cmds = ft_split(cmds_path, ' '); //malloc protect
	path = ft_get_path(env);
	if (path == NULL)
		return (-1); //error no environment path was found
	if (execve(path, cmds, env) < 0)
		return (-1); //error here
}

static void	child_process(t_pipex *pipex_args)
{
	dup2(pipex_args->pipe[0], STDIN_FILENO);
	dup2(pipex_args->pipe[1], STDOUT_FILENO);
	close(pipex_args->pipe[0]);
	ft_execute(pipex_args->cmd_args[2], pipex_args->env_path);
	close(pipex_args->pipe[1]);
	exit(EXIT_FAILURE);
}

static void	parent_process(t_pipex *pipex_args)
{
	dup2(pipex_args->pipe[1], STDOUT_FILENO);
	dup2(pipex_args->pipe[0], STDIN_FILENO);
	close(pipex_args->pipe[1]);
	//excve with cmd args [3]
	ft_execute(pipex_args->cmd_args[3], pipex_args->env_path); //or second to last one 
	close(pipex_args->pipe[0]);
	exit(EXIT_FAILURE);
}

static void	ft_pipex(t_pipex *pipex_args)
{
	/* add a while loop for bonus - needs to iterate al the commands of argv
	also for the pipes[index][0/1] */
	pid_t	pid;
	int		i;
	
	i = 0;
	while (++i < pipex_args->cmd_count)
	{
		if (pipe(pipex_args->pipe) < 0)
			return (-1); //add errorcode
		pid = fork(); 
		if (pid < 0)
			return (perror("Fork: "));
		if (pid == 0)
			child_process(pipex_args);
		else
			parent_process(pipex_args);
	}
	
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex *pipex_args;

	if (argc < 4)
		return (-1); //return error about invalid arguments
	pipex_args = malloc(sizeof(t_pipex));
	if (pipex_args == NULL)
		return (-1); //add error
	ft_init_pipex(pipex_args, argc); // set default values
	ft_check_args(pipex_args, argv, envp); //opens files and sets fds to pipex args
	ft_pipex(pipex_args);
	ft_clear_all(pipex_args);
	return (0);
}