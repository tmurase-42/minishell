/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:23:23 by tmurase           #+#    #+#             */
/*   Updated: 2021/08/28 20:32:58 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		exec_common(t_cmd *cmd, t_mshl_data *mshl_data)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	**args;
	char	**envs;
	char	*path;

	pid = fork();
	if (pid < 0)
		ft_error("resources runnout.", cmd->args->data, 0);
	if (pid == 0) // 子プロセスの処理
	{
		args = ft_token_array(cmd->args, 0, cmd->argc);
		envs = ft_env_array(mshl_data->envs);
		path = ft_cmd_path(args[0], mshl_data);
		// printf("\ncmd->argc: %d\n", cmd->argc);
		// printf("args: %s\n", *args);
		// printf("cmd->args->data: %s\n", cmd->args->data);
		if (execve(path, args, envs) == -1)
			ft_error("do not work exec", cmd->args->data, EXIT_FAILURE);
		ft_safe_free_split(&envs);
	}
	else // 親プロセスの処理
	{
		//while (!WIFEXITED(status) && !WIFSIGNALED(status))
		if (pid > 0)
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

static int	exec_builtin(t_cmd *cmd, t_mshl_data *mshl_data)
{
	if (ft_strncmp(cmd->args->data, "echo",ft_strlen("echo")) == 0)
		return (ft_echo(cmd));
	if (ft_strncmp(cmd->args->data, "exit", ft_strlen("exit")) == 0)
		return (ft_exit(cmd));
	if (ft_strncmp(cmd->args->data, "env", ft_strlen("env")) == 0)
		return (ft_env(mshl_data));
	if (ft_strncmp(cmd->args->data, "export", ft_strlen("export")) == 0)
		return (ft_export(cmd, mshl_data));
	if (ft_strncmp(cmd->args->data, "unset", ft_strlen("unset")) == 0)
		return (ft_unset(cmd, mshl_data));
	if (ft_strncmp(cmd->args->data, "pwd", ft_strlen("pwd")) == 0)
		return (ft_pwd(mshl_data));
	if (ft_strncmp(cmd->args->data, "cd", ft_strlen("cd")) == 0)
		return (ft_cd(cmd, mshl_data));
	if (ft_strncmp(cmd->args->data, "history", ft_strlen("history")) == 0)
		return (ft_history(mshl_data));
	return (EXIT_FAILURE);
}

static t_bool	is_builin_command(char *str)
{
	const char *commands[] = {"exit", "cd", "env", "unset", "export", "echo", "pwd", "history", NULL};
	int		i;

	i = 0;
	if (str == NULL)
		return (FALSE);
	while (commands[i])
	{
		if (ft_strncmp(str, commands[i], ft_strlen(commands[i])) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int				ft_execute_command(t_cmd *cmd, t_mshl_data *mshl_data)
{
	if (cmd->argc == 0 || !cmd->args || cmd->args->data == '\0')
		return (EXIT_FAILURE);
	if (is_builin_command(cmd->args->data) == TRUE)
		return (exec_builtin(cmd, mshl_data));
	else
		return (exec_common(cmd, mshl_data));
	return (EXIT_FAILURE);
}
