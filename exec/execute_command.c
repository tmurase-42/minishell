/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:23:23 by tmurase           #+#    #+#             */
/*   Updated: 2021/06/06 16:35:36 by tmurase          ###   ########.fr       */
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

static	t_bool	ft_exec_builtin(t_command *command_info)
{
	if (ft_strncmp(command_info->argv[0], "echo",ft_strlen("echo")) == 0)
		return (FALSE);
	if (ft_strncmp(command_info->argv[0], "exit", ft_strlen("exit")) == 0)
		return (ft_exit(command_info));
	if (ft_strncmp(command_info->argv[0], "env", ft_strlen("env")) == 0)
		return (ft_env(command_info));
	if (ft_strncmp(command_info->argv[0], "export", ft_strlen("export")) == 0)
		return (ft_export(command_info));
	if (ft_strncmp(command_info->argv[0], "unset", ft_strlen("unset")) == 0)
		return (ft_unset(command_info));
	if (ft_strncmp(command_info->argv[0], "pwd", ft_strlen("pwd")) == 0)
		return (ft_pwd(command_info));
	if (ft_strncmp(command_info->argv[0], "cd", ft_strlen("cd")) == 0)
		return (ft_cd(command_info));
	return (FALSE);
}

static	t_bool	ft_is_command(char **args)
{
	const char *commands[] = {"exit", "cd", "env", "unset", "export", "echo", "pwd", NULL};
	int		i;

	i = 0;
	if (args[0] == NULL)
		return (FALSE);
	while (commands[i])
	{
		if (ft_strncmp(args[0], commands[i], ft_strlen(commands[i])) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	execute_command(t_command *command_info)
{
	if (command_info->argc == 0 || ft_strncmp(command_info->argv[0], "", 1) == 0)
		return (1);
	if (ft_is_command(command_info->argv) == TRUE)
	{
		if (ft_exec_builtin(command_info) != TRUE)
			ft_error("error!\n", command_info->argv[0]);
	}
	else	
		return (launch(command_info));
	return (0);
}
