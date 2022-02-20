/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 01:13:15 by vnazioze          #+#    #+#             */
/*   Updated: 2022/02/19 02:40:24 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*path_bin(t_data *data)
{
	int		i;
	int		check;
	char	*path;
	char	*cmd;

	i = 0;
	while (data->bin[i])
	{
		path = ft_strjoin(data->bin[i], "/");
		cmd = ft_strjoin(path, data->cmd[0]);
		check = access(cmd, F_OK);
		if (check == 0)
		{
			free(path);
			return (cmd);
		}
		free(path);
		free(cmd);
		i++;
	}
	return (NULL);
}

void	parse_env(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", ft_strlen("PATH")))
		{
			data->path = ft_strchr(envp[i], '/');
			break ;
		}
		i++;
	}
	data->bin = ft_split(data->path, ':');
}

void	parse_args(t_data *data, char *argv)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (ft_strchr(argv, SINGLE_QUOTE))
	{
		while (argv[j])
		{
			if (argv[j] == SINGLE_QUOTE)
				i++;
			j++;
		}
		if (i != 1)
			treat_space(data, argv);
		else
			data->cmd = ft_split(argv, SPACE);
	}
	else
		data->cmd = ft_split(argv, SPACE);
}

void	exec_cmd(t_data *data, char *argv, char **envp)
{
	char	*cmd;

	parse_env(data, envp);
	parse_args(data, argv);
	cmd = path_bin(data);
	if (!cmd)
	{
		errno = 22;
		perror(data->cmd[0]);
		free_all(data);
		free(cmd);
		exit(127);
	}
	if (execve(cmd, data->cmd, envp) == -1)
	{
		free_all(data);
		free(cmd);
		exit(1);
	}
}
