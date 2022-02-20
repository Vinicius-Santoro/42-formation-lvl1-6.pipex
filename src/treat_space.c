/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 01:13:03 by vnazioze          #+#    #+#             */
/*   Updated: 2022/02/19 02:22:40 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static	int	ft_find_pos(char *cmd_dup, int index)
{
	while (cmd_dup[index] != SINGLE_QUOTE)
		index++;
	return (index);
}

void	treat_space(t_data *data, char *argv)
{
	char	*cmd_dup;
	int		pos1;
	int		pos2;
	char	*test;
	int		i;

	cmd_dup = ft_strdup(argv);
	pos1 = ft_find_pos(cmd_dup, 0);
	pos2 = ft_find_pos(cmd_dup, pos1 + 1);
	if (cmd_dup[pos2 + 1] == '\0')
		i = 2;
	else
		i = 1;
	test = ft_substr(cmd_dup, pos1 + 1, pos2 - pos1 - 1);
	while (pos1 <= pos2)
	{
		cmd_dup[pos1] = 1;
		pos1++;
	}
	data->cmd = ft_split(cmd_dup, SPACE);
	free(data->cmd[i]);
	data->cmd[i] = ft_strdup(test);
	free(cmd_dup);
	free(test);
}
