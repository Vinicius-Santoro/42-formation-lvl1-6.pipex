/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 01:12:56 by vnazioze          #+#    #+#             */
/*   Updated: 2022/02/19 01:12:58 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_data	data;

	if (argc != 5)
		return (EXIT_FAILURE);
	else if (argc == 5)
	{
		init_values(&data, argc, argv, envp);
		if (open_files(&data) == 1)
			return (EXIT_FAILURE);
		return (pipes(&data, argv, envp));
	}
	return (EXIT_SUCCESS);
}

void	init_values(t_data *data, int argc, char *argv[], char **envp)
{
	data->files.infile = argv[1];
	data->files.outfile = argv[4];
	data->envp = envp;
	data->cmd_qnt = argc - 3;
}

int	open_files(t_data *data)
{
	data->files.in_fd = open(data->files.infile, O_RDONLY);
	data->files.out_fd = open(data->files.outfile, O_WRONLY | O_CREAT \
		| O_TRUNC, 0777);
	if (data->files.in_fd == -1 || data->files.out_fd == -1)
	{
		msg_error(data);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	close_files(t_data *data)
{
	close(data->files.in_fd);
	close(data->files.out_fd);
}

void	msg_error(t_data *data)
{
	close_files(data);
	perror("ERROR");
}
