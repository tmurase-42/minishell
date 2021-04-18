/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:23:23 by tmurase           #+#    #+#             */
/*   Updated: 2021/04/18 14:42:17 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


char *builtin_str[] = 
{
	//"cd",
	"exit"
};

int	mini_exit(char **argv)
{
	(void)argv;
	printf("exit:ただexitしてるだけなので処理として正しいかどうかは未検討\n");
	exit(0);
	return 0;
}

int	(*builtin_func[])(char **) =
{	
	//&cd,
	&mini_exit
};


int	num_builtins()
{
	//printf("sizeof(builtin_str) / sizeof(char *) = %lu\n", sizeof(builtin_str) / sizeof(char *));
	return sizeof(builtin_str) / sizeof(char *);
}


int	execute_command(t_command *command_info)
{
	int	i;
	int	accept_command;

	if (ft_strncmp(command_info->argv[0], "", 1) == 0)
		return (1);
	i = 0;
	accept_command = 0;
	while (i < num_builtins())
	{
		accept_command = ft_strncmp(command_info->argv[0],builtin_str[i],ft_strlen(builtin_str[i]));
		if (!accept_command)
		{
			return (*builtin_func[i])(command_info->argv);
		}
		i++;
	}
	return (launch(command_info));
}
