/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:55:35 by ktoivola          #+#    #+#             */
/*   Updated: 2024/01/15 11:28:05 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* awk '{count++} END {print count}' */

static int	ft_count_args(char *cmds)
{
	int	arg_count;
	int	i;
	char c; //4 debug

	i = 0;
	arg_count = 0;
	while (cmds[i])
	{
		if (cmds[i] == ' ')
			arg_count++;
		else if (cmds[i] == '\"' || cmds[i] == '\'')
		{
			arg_count++;
			i++;
			while (cmds[i] && (cmds[i] != '\"' && cmds[i] != '\''))
			{
				c = cmds[i]; //4 debug
				i++;
			}
		}
		i++;
	}
	if (cmds[i - 1] != '\"' && cmds[i -1] != '\'')
		arg_count++;
	return (arg_count);
}

char	**ft_parse_commands(char *cmds)
{
	char **parsed_cmds;
	int	arg_count;
	int	i;
	int j;
	int k;

	char c = '0'; //4 debug
	
	arg_count = ft_count_args(cmds);
	parsed_cmds = malloc(sizeof(char *) * (arg_count + 1)); //protect
	k = ft_strlen(cmds); //4 debug
	i = 0;
	j = 0;
	k = 0;
	while (cmds[i + j] && k < arg_count)
	{
		if (cmds[i + j] == ' ')
		{
			while (cmds[i + j + 1] == ' ')
				i++;
			parsed_cmds[k] = ft_substr(cmds, j, i);
			printf("parsed cmds[%d] is -%s-\n", k, parsed_cmds[k]);
			k++;
			j = ++i; // skips the space
			i = 0;
		}
		if (cmds[j + i] == '\"' || cmds[j + i] == '\'')
		{
			i++;
			while (cmds[j + i] != '\"' && cmds[j + i] != '\'') //also check if string ends
			{
				c = cmds[j + i];
				i++;
			}
			parsed_cmds[k] = ft_substr(cmds, ++j, i - 1); //takes out the ''
			printf("parsed cmds[%d] is -%s-\n", k, parsed_cmds[k]);
			k++;
			j = i;
			i = 0;
		}
		i++;
	}
	if (k < arg_count) // if k < argcount
	{
		parsed_cmds[k] = ft_substr(cmds, j, i);
		printf("parsed cmds[%d] is -%s-\n", k, parsed_cmds[k]);
	}
	parsed_cmds[arg_count] = NULL;
	printf("parsed cmds[%d] is -%s-\n", k, parsed_cmds[k]);
	return (parsed_cmds);
}
