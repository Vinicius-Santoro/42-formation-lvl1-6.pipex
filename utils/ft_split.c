/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 01:13:25 by vnazioze          #+#    #+#             */
/*   Updated: 2022/02/19 01:13:28 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	ft_wordcount(char const *s, char c)
{
	unsigned int	i;
	unsigned int	wordcount;

	i = 0;
	wordcount = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] && s[i] != c)
				i++;
			wordcount++;
		}
	}
	return (wordcount);
}

static size_t	ft_wordlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	size_t	i;
	size_t	k;
	char	**tables;

	words = ft_wordcount(s, c);
	tables = ft_calloc(words + 1, sizeof(char *));
	if (tables == NULL)
		return (NULL);
	k = 0;
	while (*s)
	{
		if (*s != c)
		{
			i = ft_wordlen(s, c);
			tables[k] = ft_substr(s, 0, i);
			if (tables[k] == NULL)
				return (NULL);
			s += i;
			k++;
		}
		while (*s == c && *s)
			s++;
	}
	return (tables);
}
