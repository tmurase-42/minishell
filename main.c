/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 23:48:06 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/10 16:36:41 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshl_data	*g_mshl_data;

static t_mshl_data	*mshl_data_init(t_env *envs)
{
	t_mshl_data	*mshl_data;

	mshl_data = malloc(sizeof(t_mshl_data));
	if (!mshl_data)
		return (NULL);
	mshl_data->argc = 0;
	mshl_data->argv = NULL;
	mshl_data->envs = envs;
	mshl_data->exit_status = 0;
	mshl_data->pipe_state = WRITE_ONLY;
	mshl_data->interrupted = FALSE;
	return (mshl_data);
}

static t_cmd	*run_commandline(char **command)
{
	extern t_mshl_data *g_mshl_data;
	t_cmd		*cmd;
	t_token		*tokens;

	tokens = NULL;

	// 文字列をトークンに分離する
	tokens = ft_lexer(*command);

	// 異常なトークンの検知とエラー吐き出し
	//if (ft_check_token_error(tokens) != TRUE)
	//	return NULL;

	// トークンをパースする
	cmd = ft_cmd_lstnew();
	ft_parser(tokens, cmd);

	// テストプリント
	//ft_token_print(cmd->args);

	// 実行
	ft_exec_commands(cmd);

	// 返却
	return cmd;
}

static void	update_shlvl()
{
	extern t_mshl_data	*g_mshl_data;
	t_env	*shlvl_env;
	char	*shlvl_str;
	char	shlvl_num;

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
}

int	main(int argc, char *argv[], char **environ)
{
	extern t_mshl_data	*g_mshl_data;
	char	*command;
	t_env	*envs;
	t_cmd	*cmd;


	(void)argv;
	(void)argc;
	command = NULL;
	envs = ft_env_init(environ);
	g_mshl_data = mshl_data_init(envs);
	update_shlvl();
	//ft_env_destroy("OLDPWD");

	if (argc > 2 && ft_strncmp("-c", argv[1], 3) == 0)
	{
		add_history(argv[2]);
		cmd = run_commandline(&argv[2]);
		ft_wait_process(cmd);
		return g_mshl_data->exit_status;
	}
	while (1)
	{
		//g_mshl_data->interrupted = FALSE;
		//g_mshl_data->exit_status = 0;
		ft_sigint_setter(ft_sigint_handler);
		command = readline("\e[36mminishell>\e[0m");
		if (command == NULL)
			exit(EXIT_FAILURE);
		else if (ft_strlen(command) > 0)
		{
			add_history(command);
			cmd = run_commandline(&command);
			ft_wait_process(cmd);
		}
	}
	return (g_mshl_data->exit_status);
}
