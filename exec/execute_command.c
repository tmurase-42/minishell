/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:23:23 by tmurase           #+#    #+#             */
/*   Updated: 2021/05/07 18:48:41 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	launch(t_command *command_info)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(command_info->argv[0], command_info->argv) == -1)
			printf("error:25");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		printf("error:30");
	}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

static	t_bool	ft_check_command(t_command *command_info)
{
	if (ft_strncmp(command_info->argv[0], "echo",ft_strlen("echo")) == 0)
		return (FALSE);
	if (ft_strncmp(command_info->argv[0], "exit", ft_strlen("exit")) == 0)
		return (ft_exit(command_info));
	if (ft_strncmp(command_info->argv[0], "env", ft_strlen("env")) == 0)
		return (FALSE);
	if (ft_strncmp(command_info->argv[0], "export", ft_strlen("export")) == 0)
		return (FALSE);
	if (ft_strncmp(command_info->argv[0], "unset", ft_strlen("unset")) == 0)
		return (FALSE);
	if (ft_strncmp(command_info->argv[0], "pwd", ft_strlen("pwd")) == 0)
		return (FALSE);
	if (ft_strncmp(command_info->argv[0], "cd", ft_strlen("cd")) == 0)
		return (FALSE);
	return (FALSE);
}

int	execute_command(t_command *command_info)
{
	int	i;
	int	accept_command;

	if (command_info->argc == 0 || ft_strncmp(command_info->argv[0], "", 1) == 0)
		return (1);
	i = 0;
	accept_command = 0;
	accept_command = ft_check_command(command_info);
	if (accept_command == FALSE)
		ft_error("command error!コマンドを実装した場合はft_check_commandに処理を追加してください\n");
	return (launch(command_info));
}
