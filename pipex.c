/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:26:52 by ktoivola          #+#    #+#             */
/*   Updated: 2024/01/09 14:20:40 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_execute(char *cmds_path, char **env_paths, char **envp)
{
	char **cmds;
	char *exec_path;
	
	cmds = ft_split(cmds_path, ' '); //malloc protect
	while (*env_paths)
	{
		exec_path = ft_strjoin(*env_paths, "/");
		exec_path = ft_strjoin(exec_path, cmds[0]);
		printf("exec path %s\n", exec_path);
		if (access(exec_path, F_OK & X_OK) < 0)
			env_paths++;
		else
		{
			if (execve(exec_path, cmds, envp) < 0)
				perror("execve faliled"); //error here
		}
	}
}

static void	child_process(t_pipex *pipex_args, int	cmd_num, char **envp)
{
	printf("child process\n");
	dup2(pipex_args->pipe[0], STDIN_FILENO);
	dup2(pipex_args->pipe[1], STDOUT_FILENO);
	close(pipex_args->pipe[0]);
	close(pipex_args->pipe[1]);
	ft_execute(pipex_args->cmd_args[cmd_num], pipex_args->env_paths, envp);
	exit(1);
}

static void	parent_process(t_pipex *pipex_args, char **envp)
{
	int	cmd_num;
	printf("command count is %i\n", (pipex_args->cmd_count));
	printf("command to execute is %i\n", pipex_args->cmd_count + 2);
	cmd_num = pipex_args->cmd_count + 1;
	dup2(pipex_args->pipe[1], STDOUT_FILENO);
	dup2(pipex_args->pipe[0], STDIN_FILENO);
	close(pipex_args->pipe[1]);
	ft_execute(pipex_args->cmd_args[cmd_num], pipex_args->env_paths, envp); //or second to last one 
	close(pipex_args->pipe[0]);
}

static void	ft_pipex(t_pipex *pipex_args, char **envp)
{
	pid_t	pid;
	int		i;
	
	i = 0;
	while (++i < pipex_args->cmd_count)
	{
		fflush(stdout);
		if (pipe(pipex_args->pipe) < 0)
			exit(EXIT_PIPE_ERROR);
		pid = fork(); 
		if (pid < 0)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			child_process(pipex_args, i, envp);
		else
		{
			wait(NULL);
			parent_process(pipex_args, envp);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	
	t_pipex *pipex_args;
	int	i = 0;

	while (envp[i])
	{
		printf("env variable %d is %s\n", i, envp[i]);
		i++;
	}
	if (argc < 4)
		return (-1); //return error about invalid arguments
	pipex_args = malloc(sizeof(t_pipex));
	if (pipex_args == NULL)
		return (-1); //add error
	ft_init_pipex(pipex_args, argc); // set default values
	ft_check_args(pipex_args, argv, envp); //opens files and sets fds to pipex args
	if (pipex_args->env_paths == NULL)
		return (-1); //error no environment paths
	ft_pipex(pipex_args, envp);
	ft_clear_all(pipex_args);
	return (0);
}