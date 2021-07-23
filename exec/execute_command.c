/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:23:23 by tmurase           #+#    #+#             */
/*   Updated: 2021/07/23 14:32:29 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int		launch(t_cmd *cmd)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	**str;

	pid = fork();
	if (pid == 0)
	{
		str = ft_token_array(cmd->args, 0, cmd->argc);
		if (execvp(cmd->args->data, str) == -1)
			ft_error("error:25", cmd->args->data);
		free(str);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		ft_error("error:30", cmd->args->data);
	}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

static	t_bool	ft_exec_builtin(t_cmd *cmd, t_mshl_data *mshl_data)
{
	if (ft_strncmp(cmd->args->data, "echo",ft_strlen("echo")) == 0)
		return (FALSE);
	if (ft_strncmp(cmd->args->data, "exit", ft_strlen("exit")) == 0)
		return (ft_exit(cmd));
	if (ft_strncmp(cmd->args->data, "env", ft_strlen("env")) == 0)
		return (ft_env(mshl_data));
	if (ft_strncmp(cmd->args->data, "export", ft_strlen("export")) == 0)
		return (ft_export(cmd, mshl_data));
	if (ft_strncmp(cmd->args->data, "unset", ft_strlen("unset")) == 0)
		return (ft_unset(cmd, mshl_data));
	if (ft_strncmp(cmd->args->data, "pwd", ft_strlen("pwd")) == 0)
		return (ft_pwd());
	if (ft_strncmp(cmd->args->data, "cd", ft_strlen("cd")) == 0)
		return (ft_cd(cmd, mshl_data));
	return (FALSE);
}

static	t_bool	ft_is_command(char *str)
{
	const char *commands[] = {"exit", "cd", "env", "unset", "export", "echo", "pwd", NULL};
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
	if (cmd->argc == 0) //|| ft_strncmp(cmd->args->data, "", 1) == 0)
		return (1);
	if (ft_is_command(cmd->args->data) == TRUE)
	{
		if (ft_exec_builtin(cmd, mshl_data) != TRUE)
			ft_error("error!\n", cmd->args->data);
	}
	else
		return (launch(cmd));
	return (0);
}
