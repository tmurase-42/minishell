/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_path_search_binary.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:41:27 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 02:50:17 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	is_executable(const char *path)
{
	t_stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (FALSE);
	if ((path_stat.st_mode & S_IXUSR) != S_IXUSR)
		return (FALSE);
	if ((path_stat.st_mode & S_IRUSR) != S_IRUSR)
		return (FALSE);
	return (TRUE);
}

static t_bool	is_command_exist(const char *path, char **res)
{
	t_stat	buf;

	if (!path)
		return (FALSE);
	if (lstat(path, &buf) == -1)
		return (FALSE);
	if (S_ISDIR(buf.st_mode))
		return (FALSE);
	ft_free_char(res);
	*res = ft_strdup(path);
	if (*res == NULL)
		ft_error(NULL, NULL, EXIT_FAILURE);
	return (TRUE);
}

static t_bool	is_directory(const char *path)
{
	t_stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (FALSE);
	if (S_ISDIR(path_stat.st_mode))
		return (TRUE);
	return (FALSE);
}

static void	try_search_command(char **split_path, char **res, const char *cmd)
{
	int		index;
	char	*path;

	index = 0;
	path = NULL;
	while (split_path[index])
	{
		ft_free_char(&path);
		path = ft_join_path(split_path[index], cmd);
		if (is_command_exist(path, res) && !is_directory(path)
			&& is_executable(path))
			break ;
		index++;
	}
	ft_free_char(&path);
}

char	*ft_cmd_path_search_binary(const char *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	char				**split_path;
	char				*res;
	t_env				*env;

	res = NULL;
	env = ft_env_get("PATH", g_mshl_data->envs);
	if (ft_strncmp(env->value, "", ft_strlen(env->value)) == 0)
	{
		res = ft_strdup(cmd);
		if (res == NULL)
			ft_error(NULL, NULL, EXIT_FAILURE);
		return (res);
	}
	split_path = ft_cmd_path_get_colon(env->value, ".");
	if (split_path == NULL)
		ft_error(NULL, NULL, EXIT_FAILURE);
	try_search_command(split_path, &res, cmd);
	ft_safe_free_split(&split_path);
	return (res);
}
