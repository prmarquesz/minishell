/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 07:49:51 by guferrei          #+#    #+#             */
/*   Updated: 2022/01/11 08:05:36 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_quote_size(char *str, t_var *env, t_var *local)
{
	char	quote;
	int		size;
	int		aux;

	quote = *str;
	aux = 1;
	size = 0;
	while (str[aux] && str[aux] != quote)
	{
		if (str[aux] == '$' && quote != '\'')
		{
			size += (get_var_size(str, env, local) - 1);
			aux += mv_ptr('$', (str + aux));
		}
		size++;
		aux++;
	}
	return (size + 2);
}

int	check_var(char *str, t_var *env, t_var *local)
{
	int	size;

	if (*str == '~')
		size = get_var_size("$HOME", env, local);
	else
		size = get_var_size(str, env, local);
	return (size);
}

int	get_string_size(char *str, t_var *env, t_var *local)
{
	int		size;
	int		aux;

	size = 0;
	aux = 0;
	while (str[aux])
	{
		if ((str[aux] == '\'' || str[aux] == '"')
			&& is_quotes((str + aux), str[aux]))
		{
			size += get_quote_size((str + aux), env, local);
			aux += (mv_ptr(str[aux], (str + aux)) - 1);
		}
		else if (str[aux] == ' ' && str[aux + 1] == ' ')
			aux += (mv_ptr(' ', (str + aux)) - 1);
		else if (str[aux] == '$' || str[aux] == '~')
		{
			size += (check_var((str + aux), env, local));
			aux += (mv_ptr('$', (str + aux)) - 1);
		}
		else
			size++;
		aux++;
	}
	return (size + 1);
}

void	string_parse_sub(t_parse *parse, t_var *env, t_var *local)
{
	while (parse->str[parse->idx1])
	{
		if (parse->str[parse->idx1] == '\\' )
			parse->idx1++;
		if ((parse->str[parse->idx1] == '\'' || parse->str[parse->idx1] == '"')
			&& is_quotes((parse->str + parse->idx1), parse->str[parse->idx1])
			&& parse->str[parse->idx1 - 1] != '\\')
			parse->quotes = parse->str[parse->idx1];
		else if (parse->str[parse->idx1] == parse->quotes)
			parse->quotes = 0;
		if (parse->str[parse->idx1] == ' '
			&& parse->str[parse->idx1 + 1] == ' ' && !parse->quotes)
			parse->idx1 += mv_ptr(' ', (parse->str + parse->idx1));
		else if ((parse->str[parse->idx1] == '$' && parse->quotes != '\'')
			|| (parse->str[parse->idx1] == '~' && !parse->quotes))
		{
			parse->idx2 += var_value_cpy((parse->parsed + parse->idx2),
					(parse->str + parse->idx1), env, local);
			parse->idx1 += mv_ptr(parse->str[parse->idx1],
					(parse->str + parse->idx1));
		}
		else
			parse->parsed[parse->idx2++] = parse->str[parse->idx1++];
	}
}

char	*string_parse(char *str, t_var *env, t_var *local)
{
	t_parse	parse;

	parse.idx1 = 0;
	parse.idx2 = 0;
	parse.str = str;
	parse.quotes = 0;
	parse.parsed = ft_calloc(get_string_size(str, env, local), sizeof(char));
	if (!parse.parsed)
		return (NULL);
	string_parse_sub(&parse, env, NULL);
	return (parse.parsed);
}
