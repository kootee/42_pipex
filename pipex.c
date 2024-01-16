/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:26:52 by ktoivola          #+#    #+#             */
/*   Updated: 2024/01/15 15:29:58 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_execute(t_pipex *pipex_args, int cmd_n, char **env)
{
	char **cmds;
	char *exec_path;
	
	cmds = ft_parse_commands(pipex_args->cmd_args[cmd_n]);
	/*
	int	i = 0;
 	while (cmds[i])
		printf("cmds are %s\n", cmds[i++]); 
	*/
	if (cmds == NULL)
		exit(0);
	exec_path = ft_get_env_paths(pipex_args, cmds);
	if (exec_path == NULL)
	{
		exit(EXIT_FAILURE);
	}
	if (execve(exec_path, cmds, env) == -1)
	{		
		perror("execve failed");
		free(exec_path);
		ft_free_strs(cmds);
		exit(EXIT_FAILURE);
	}
}

static void	child_process(t_pipex *pipex_args, char **env)
{
	dup2(pipex_args->fd_IO[0], STDIN_FILENO); // has to be from fd where is read from
	dup2(pipex_args->pipe[1], STDOUT_FILENO); // fd where to write
	close(pipex_args->pipe[0]); // this one (read end of pipe) is NOT USED IN CHILD PROCESS!
	close(pipex_args->fd_IO[1]);
	ft_execute(pipex_args, 2, env);
}

static void	parent_process(t_pipex *pipex_args, char **env)
{
	dup2(pipex_args->pipe[0], STDIN_FILENO); //where to read from
	dup2(pipex_args->fd_IO[1], STDOUT_FILENO); //where to write to
	close(pipex_args->pipe[1]); // this one (write end of pipe) is NOT USED IN CHILD PROCESS!
	close(pipex_args->fd_IO[0]); //close the input file
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
		exit(EXIT_FAILURE);
	}
	pid = fork(); 
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
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
/* 
	int	i = 0;
	while (argv[i])
	{
		printf("command is [%d] %s\n", i, argv[i]);
		i++;
	}
	
	char **cmds = ft_split(argv[2], ' ');
	char **cmds2 = ft_split(argv[3], ' ');
	i = 0;
	while (cmds[i])
	{
		printf("-->command with split is [%d] %s\n", i, cmds[i]);
		i++;
	}
	i = 0;
	while (cmds2[i])
	{
		printf("-->command with split is [%d] %s\n", i, cmds2[i]);
		i++;
	}
	fflush(stdout);
 */
	if (argc != 5)
	{
		perror("invalid no of parameters given"); //return error about invalid arguments
		exit(EXIT_FAILURE);
	}
	pipex_args = malloc(sizeof(t_pipex));
	if (pipex_args == NULL)
		exit(EXIT_FAILURE);
	ft_init_pipex(pipex_args, argc); // set default values
	ft_check_args(pipex_args, argv); //opens files and sets fds to pipex args
	pipex_args->cmd_args = argv;
	pipex_args->env_paths = envp;
	ft_pipex(pipex_args, envp);
	//ft_close_all(pipex_args);
	//return (0);
}
