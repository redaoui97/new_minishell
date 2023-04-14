/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 02:09:12 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/14 06:41:59 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_parts(char const *s, char c)
{
	int	count;
	int	i;
	int	sign;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	sign = 1;
	while (s[i])
	{
		if (sign && s[i] != c)
		{
			count++;
			sign = 0;
		}
		else if (s[i] == c)
			sign = 1;
		i++;
	}
	return (count);
}

static int	word_size(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
	{
		i++;
	}
	return (i);
}

static void	rollback(char **words, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(words[i]);
		words[i] = NULL;
		i++;
	}
	free(words);
	words = NULL;
}

static void	fill_words(char **words, const char *s, char c, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count && *s)
	{
		while (*s && *s == c)
			s++;
		j = word_size(s, c);
		words[i] = ft_substr_adjusted(s, 0, j);
		if (!words[i])
			rollback(words, count);
		s += j;
		i++;
	}
	words[i] = NULL;
}

char	**ft_split_adjusted(char const *s, char c)
{
	int		words_count;
	char	**words;

	words_count = count_parts(s, c);
	words = (char **)malloc(sizeof(char *) * (words_count + 1));
	if (!words)
		return (NULL);
	fill_words(words, s, c, words_count);
	return (words);
}
