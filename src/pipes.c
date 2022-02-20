/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 01:13:00 by vnazioze          #+#    #+#             */
/*   Updated: 2022/02/19 02:28:43 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	pipes(t_data *data, char *argv[], char **envp)
{
	if (pipe(data->fd) == -1)
	{
		msg_error(data);
		return (WEXITSTATUS(data->exit_status));
	}
	if (first_command(data, argv, envp) == 1)
		return (WEXITSTATUS(data->exit_status));
	waitpid(data->pid1, &data->exit_status, 0);
	close(data->fd[1]);
	if (second_command(data, argv, envp) == 1)
		return (WEXITSTATUS(data->exit_status));
	waitpid(data->pid2, &data->exit_status, 0);
	return (WEXITSTATUS(data->exit_status));
}

int	first_command(t_data *data, char *argv[], char **envp)
{
	data->pid1 = fork();
	if (data->pid1 == -1)
	{
		msg_error(data);
		return (EXIT_FAILURE);
	}
	if (data->pid1 == 0)
	{
		dup_close(data, data->files.in_fd, STDIN_FILENO);
		dup_close(data, data->fd[1], STDOUT_FILENO);
		exec_cmd(data, argv[2], envp);
	}
	return (EXIT_SUCCESS);
}

int	second_command(t_data *data, char *argv[], char **envp)
{
	data->pid2 = fork();
	if (data->pid2 == -1)
	{
		msg_error(data);
		return (EXIT_FAILURE);
	}
	if (data->pid2 == 0)
	{
		dup_close(data, data->fd[0], STDIN_FILENO);
		dup_close(data, data->files.out_fd, STDOUT_FILENO);
		exec_cmd(data, argv[3], envp);
	}
	return (EXIT_SUCCESS);
}

void	dup_close(t_data *data, int fd, int std)
{
	int	check;

	check = dup2(fd, std);
	close(fd);
	if (check == -1)
		msg_error(data);
}
