/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 20:51:39 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/26 21:25:06 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool		is_executable(const char *path)
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

t_bool		is_command_exist(const char *path, char **res)
{
	t_stat buf;

	if (!path)
		return (FALSE);
	if (lstat(path, &buf) == -1)
		return (FALSE);
	if (S_ISDIR(buf.st_mode))
		return (FALSE);
	ft_free_char(res);
	if (!(*res = ft_strdup(path)))
		ft_error(NULL, NULL, 1);
	return (TRUE);
}

char	*join_path(const char *prev, const char *next)
{
	char	*tmp;
	char	*res;
	size_t	index;

	if (!prev || !next)
		return (NULL);
	tmp = NULL;
	res = NULL;
	if (!(tmp = ft_strjoin(prev, "/")))
		ft_error(NULL, NULL, 1);
	index = ft_strlen(tmp);
	if (index >= 2 && tmp[index - 2] == '/')
		tmp[index - 1] = '\0';
	if (!(res = ft_strjoin(tmp, next)))
		ft_error(NULL, NULL, 1);
	free(tmp);
	return (res);
}

t_bool	is_directory(const char *path)
{
	t_stat path_stat;

	if (stat(path, &path_stat) == -1)
		return (FALSE);
	if (S_ISDIR(path_stat.st_mode))
		return (TRUE);
	return (FALSE);
}

char	**allocate_colon_unit_parent(const char *str)
{
	size_t	index;
	size_t	colon_count;
	char	**res;

	index = 0;
	colon_count = 0;
	while (str[index])
	{
		if (str[index] == ':')
			colon_count++;
		index++;
	}
	if (!(res = malloc(sizeof(char *) * (colon_count + 2))))
		ft_error(NULL, NULL, 1);
	res[colon_count + 1] = NULL;
	return (res);
}

char	*strdup_colon_unit(char *unit, const char *default_value)
{
	char *res;

	if (!unit)
		return (NULL);
	if (ft_strlen(unit) == 0)
	{
		if (!(res = ft_strdup(default_value)))
			ft_error(NULL, NULL, 1);
	}
	else
	{
		if (!(res = ft_strdup(unit)))
			ft_error(NULL, NULL, 1);
	}
	return (res);
}

char	**get_colon_units(const char *str, const char *default_value)
{
	char	**res;
	size_t	index;
	char	*copied_str;
	char	*unit_start;
	char	*unit_end;

	index = 0;
	res = allocate_colon_unit_parent(str);
	if (!(copied_str = ft_strdup(str)))
		ft_error(NULL, NULL, 1);
	unit_start = copied_str;
	unit_end = ft_strchr(unit_start, ':');
	while (unit_end)
	{
		*unit_end = '\0';
		res[index] = strdup_colon_unit(unit_start, default_value);
		unit_start = unit_end + 1;
		unit_end = ft_strchr(unit_start, ':');
		index++;
	}
	res[index] = strdup_colon_unit(unit_start, default_value);
	ft_free_char(&copied_str);
	return (res);
}



t_cmd_type	judge_cmd_type(const char *str)
{
	if (*str == '/')
		return (ABSOLUTE);
	else if (ft_strchr(str, '/') != NULL)
		return (RELATIVE);
	else
		return (COMMAND);
}

void		try_search_command(char **split_path, char **res, const char *cmd)
{
	int		index;
	char	*path;

	index = 0;
	path = NULL;
	while (split_path[index])
	{
		ft_free_char(&path);
		path = join_path(split_path[index], cmd);
		if (is_command_exist(path, res) && !is_directory(path) &&
			is_executable(path))
			break ;
		index++;
	}
	ft_free_char(&path);
}

char		*search_command_binary(const char *cmd, t_mshl_data *mshl_data)
{
	char		**split_path;
	char		*res;
	t_env		*env;

	res = NULL;
	env = ft_env_get("PATH", mshl_data->envs);
	if (ft_strncmp(env->value, "", ft_strlen(env->value)) == 0)
	{
		if (!(res = ft_strdup(cmd)))
			ft_error(NULL, NULL, 1);
		return (res);
	}
	if (!(split_path = get_colon_units(env->value, ".")))
		ft_error(NULL, NULL, 1);
	try_search_command(split_path, &res, cmd);
	ft_safe_free_split(&split_path);
	return (res);
}

static void	check_cmd_path(const char *cmd, const char *path)
{
	if (path == NULL)
	{
		ft_error_identifier("command not found", (char *)cmd);
		exit(STATUS_CMD_NOT_FOUND);
	}
}

char		*ft_cmd_path(const char *cmd, t_mshl_data *mshl_data)
{
	t_cmd_type	type;
	char		*res;

	if (!cmd)
		return (NULL);
	type = judge_cmd_type(cmd);
	if (type == COMMAND)
	{
		res = search_command_binary(cmd, mshl_data);
	}
	else
	{
		if (!(res = ft_strdup(cmd)))
			ft_error(NULL, NULL, 1);
	}
	check_cmd_path(cmd, res);
	return (res);
}
