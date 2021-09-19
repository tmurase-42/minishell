/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 23:48:06 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/19 12:30:28 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshl_data	*g_mshl_data;

static t_cmd	*run_commandline(char **command)
{
	extern t_mshl_data	*g_mshl_data;
	t_cmd				*cmd;
	t_token				*tokens;

	tokens = NULL;
	if (ft_validate_str(*command) == FALSE)
	{
		ft_error_display(NULL, "syntax error near unexpected token.", 2);
		return (NULL);
	}
	tokens = ft_lexer(*command);
	if (ft_validate_token(tokens) == FALSE)
	{
		ft_error_display(NULL, "syntax error near unexpected token.", 2);
		return (NULL);
	}
	cmd = ft_cmd_lstnew();
	ft_parser(tokens, cmd);
	ft_exec_commands(cmd);
	ft_token_free(tokens);
	return (cmd);
}

static void	update_shlvl(void)
{
	extern t_mshl_data	*g_mshl_data;
	t_env				*shlvl_env;
	char				*shlvl_str;
	char				shlvl_num;

	shlvl_num = 0;
	shlvl_str = NULL;
	shlvl_env = ft_env_get("SHLVL", g_mshl_data->envs);
	if (!shlvl_env)
		return ;
	shlvl_str = shlvl_env->value;
	shlvl_num = ft_atoi(shlvl_str);
	shlvl_num += 1;
	shlvl_str = ft_itoa(shlvl_num);
	if (!shlvl_str)
		return ;
	ft_env_update("SHLVL", shlvl_str);
	free(shlvl_str);
}

static void	exec_loop(t_mshl_data *g_mshl_data)
{
	char	*command;
	t_cmd	*cmd;

	while (1)
	{
		g_mshl_data->interrupted = FALSE;
		g_mshl_data->exit_status = EXIT_SUCCESS;
		ft_sigint_setter(ft_sigint_handler);
		if (g_mshl_data->command == NULL)
			command = readline("\e[36mminishell>\e[0m");
		else
			command = ft_strdup(g_mshl_data->command);
		g_mshl_data->command = NULL;
		if (command == NULL)
		{
			ft_mshl_data_destroy();
			ft_putstr_fd("exit\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		else if (ft_strlen(command) > 0)
		{
			add_history(command);
			cmd = run_commandline(&command);
			ft_wait_process(cmd);
			ft_cmd_destroy(cmd);
		}
		free(command);
	}
}

static void	exec_once(t_mshl_data *g_mshl_data)
{
	t_cmd	*cmd;

	cmd = NULL;
	add_history(g_mshl_data->argv[2]);
	cmd = run_commandline(&(g_mshl_data->argv[2]));
	ft_wait_process(cmd);
	ft_cmd_destroy(cmd);
}

int	main(int argc, char *argv[], char **environ)
{
	extern t_mshl_data	*g_mshl_data;
	t_env				*envs;

	(void)argc;
	envs = ft_env_init(environ);
	g_mshl_data = ft_mshl_data_init(envs, argv);
	update_shlvl();
	if (argc > 2 && ft_strncmp("-c", argv[1], 3) == 0)
		exec_once(g_mshl_data);
	else
		exec_loop(g_mshl_data);
	return (g_mshl_data->exit_status);
}
