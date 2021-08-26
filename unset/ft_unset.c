/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:38:04 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/26 21:08:24 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	is_identifier(char *name)
{
	size_t	i;

	i = 0;
	if (name[i] != '_' && !ft_isalpha(name[i]))
		return (FALSE);
	i++;
	while (name[i])
	{
		if (name[i] != '_' && !ft_isalnum(name[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int				ft_unset(t_cmd *cmd, t_mshl_data *mshl_data)
{
	int		ret;
	t_token	*token;

	ret = EXIT_SUCCESS;
	token = cmd->args->next;
	if (!token) {
		ret = EXIT_FAILURE;
		ft_error_identifier("unset", "not enough arguments");
	}
	while (token)
	{
		if (is_identifier(token->data) == TRUE)
		{
			ft_env_delete(token->data, mshl_data->envs);
		}
		else
		{
			// -bash: unset: `.jfe': not a valid identifier
			ft_error(token->data, "unset", 0);
			ret = EXIT_FAILURE;
		}
		token = token->next;
	}
	return (ret);
}
