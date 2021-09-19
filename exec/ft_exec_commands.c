/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:23:23 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/20 00:32:25 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_tokens(t_cmd *cmd)
{
	char		*token_str;
	t_token		*tokens;

	tokens = NULL;
	token_str = NULL;
	ft_expand_cmd(cmd);
	if (ft_strncmp(cmd->args->data, "export", ft_strlen(cmd->args->data)) != 0)
	{
		token_str = ft_token_str(cmd->args, 0, cmd->argc);
		tokens = ft_lexer(token_str);
		ft_token_free(cmd->args);
		cmd->args = tokens;
		free(token_str);
	}
	if (ft_validate_token(cmd->args) == FALSE)
		ft_error_display(NULL, "syntax error near unexpected token.", 2);
}

void	ft_exec_commands(t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	int					old_pipe[2];

	if (g_mshl_data->pipe_state != WRITE_ONLY
		&& g_mshl_data->pipe_state != READ_WRITE)
	{
		if (pipe(old_pipe) < 0)
			ft_error(NULL, "cannot create a pipe.", EXIT_FAILURE);
		g_mshl_data->pipe_state = WRITE_ONLY;
	}
	if (cmd->next == NULL)
		g_mshl_data->pipe_state = NO_PIPE;
	while (cmd)
	{
		process_tokens(cmd);
		if (ft_exec_command(cmd, old_pipe) == FALSE)
			break ;
		cmd = cmd->next;
	}
}
