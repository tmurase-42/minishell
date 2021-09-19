/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:52:56 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/19 16:27:30 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_dir_path_absolute(char *second_argv)
{
	char	**split_path;
	char	*path;
	size_t	dot_count;
	size_t	dot_dot_count;

	dot_count = 0;
	dot_dot_count = 0;
	if (ft_strncmp("//", second_argv, 2) == 0)
		return (second_argv);
	split_path = ft_split(second_argv, '/');
	split_path = ft_skip_and_count_dot(split_path, &dot_count, &dot_dot_count);
	path = ft_convert_path(split_path);
	free(second_argv);
	return (path);
}

char	*ft_marge_path(char **split_current_dir, char **split_path,
														size_t *dot_dot_count)
{
	int		count;
	char	*argv_path;
	char	*current_path;
	char	*tmp_path;

	count = 0;
	while (split_current_dir[count + 1])
		count++;
	while ((*dot_dot_count) > 0)
	{
		free(split_current_dir[count]);
		split_current_dir[count] = NULL;
		(*dot_dot_count)--;
		count--;
	}
	argv_path = ft_convert_path(split_path);
	tmp_path = ft_convert_path(split_current_dir);
	current_path = ft_strjoin(tmp_path, argv_path);
	free(argv_path);
	free(tmp_path);
	return (current_path);
}

char	*ft_get_dir_path_relative(char *current_dir,
				char *second_argv, char *tmp)
{
	char	*path;
	char	**split_path;
	char	**current_path;
	size_t	dot_count;
	size_t	dot_dot_count;

	dot_count = 0;
	dot_dot_count = 0;
	tmp = ft_strjoin(current_dir, "/");
	current_path = ft_split(tmp, '/');
	split_path = ft_split(second_argv, '/');
	split_path = ft_skip_and_count_dot(split_path, &dot_count, &dot_dot_count);
	path = ft_marge_path(current_path, split_path, &dot_dot_count);
	free(tmp);
	free(second_argv);
	return (path);
}

static t_bool	get_path(char *second_argv, char *path, char *current_dir)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp("/", &second_argv[0], 1) == 0)
		path = ft_get_dir_path_absolute(second_argv);
	else
		path = ft_get_dir_path_relative(current_dir, second_argv, tmp);
	if (chdir(path) != 0)
		return (ft_error_cd(path));
	ft_env_update("PWD", path);
	ft_env_update("OLDPWD", current_dir);
	free(path);
	return (TRUE);
}

int	ft_cd(t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	char				current_dir[PATH_MAX];
	char				*second_argv;
	char				*path;

	path = NULL;
	if (!getcwd(current_dir, PATH_MAX))
		ft_error_display("minishell", "cd: unexpected error", 1);
	if (cmd->argc < 2 || ft_is_tilde(cmd))
		return (ft_isnot_path(g_mshl_data, current_dir));
	second_argv = ft_strdup(cmd->args->next->data);
	if (chdir(second_argv) != 0)
	{
		ft_error_display("cd", NULL, 1);
		return (g_mshl_data->exit_status);
	}
	if (get_path(second_argv, path, current_dir) == FALSE)
		return (FALSE);
	g_mshl_data->exit_status = 0;
	return (g_mshl_data->exit_status);
}
