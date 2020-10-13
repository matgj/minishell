/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:49:19 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/13 18:21:51 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		syntax_err2(char *line, int i, char c)
{
	if (i > 2 && line[i - 2] == '<' && (line[i - 1] == '<'
	|| line[i - 1] == ' ') && line[i] == '<')
		return (0);
	if (i > 2 && line[i - 2] == '>' && (line[i - 1] == '>'
	|| line[i - 1] == ' ') && line[i] == '>')
		return (0);
	if ((c == ';' || c == '|') && (line[i] == ';' || line[i] == '|'))
		return (0);
	if ((c == '>' && line[i] == '<') || (c == '<' && line[i] == '>'))
		return (0);
	return (1);
}

int		syntax_error(char *line)
{
	int		i;
	char	c;

	i = 0;
	if (line[0] == ';' || line[0] == '|')
		return (0);
	while (line[i])
	{
		if (!syntax_err2(line, i, c))
			return (0);
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' &&
		line[i] != '\f' && line[i] != '\r' && line[i] != '\v')
			c = line[i];
		i++;
	}
	if (c == '>' || c == '<' || c == '|')
		return (0);
	if (i > 1 && line[i - 1] == '|' && line[i - 2] != '\\')
		return (0);
	return (1);
}

char	*join_splits(char **lines)
{
	char	*result;
	int		l;
	int		new_len;
	int		c;

	l = -1;
	new_len = 0;
	while (lines[++l])
	{
		c = -1;
		while (lines[l][++c])
			new_len++;
	}
	if (!(result = ft_calloc(new_len + 1, sizeof(char))))
		return (NULL);
	l = -1;
	new_len = 0;
	while (lines[++l])
	{
		c = -1;
		while (lines[l][++c])
			result[new_len++] = lines[l][c];
	}
	return (result);
}

char	*replace_quotes(char *line)
{
	char	**new;
	char	*clean;
	int		i;

	i = 0;
	new = ft_split(line, REPLACED);
	free(line);
	clean = join_splits(new);
	free_split(new);
	return (clean);
}

void	parse_token(char ***token, char *cmds_pipe)
{
	int i;

	i = 0;
	*token = ft_split(cmds_pipe, ' ');
	free(cmds_pipe);
	while ((*token)[i])
	{
		(*token)[i] = replace_quotes((*token)[i]);
		i++;
	}
}
