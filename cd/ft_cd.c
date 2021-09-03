/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:52:56 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/02 17:46:00 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_bool	ft_is_tilde(t_cmd *cmd)
{
	t_token *tmp;

	if (cmd->argc < 2)
		return (FALSE);
	tmp = cmd->args->next;
	if (ft_strncmp("~", tmp->data, 1) == 0)
		return (TRUE);
	return (FALSE);
}

static	t_bool	ft_isnot_path(t_mshl_data *g_mshl_data, char *pwd)
{
	t_env	*dir;

	dir = ft_env_get("HOME", g_mshl_data->envs);
	if (!dir)
		ft_error_display("minishell", "ft_env_get: unexpected error", 1);
	ft_env_update("PWD", dir->value, g_mshl_data->envs);
	ft_env_update("OLDPWD", pwd, g_mshl_data->envs);
	if (chdir(dir->value) != 0)
		ft_error_display("minishell", "chdir: unexpected error", 1);
	else
	{
		return (TRUE);
	}
	return (FALSE);
}


t_bool	ft_error_cd(char *file)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (FALSE);
}

static	void	ft_check_dup_str(char **split_path)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (split_path[count + 1])
		count++;
	while (split_path[i + 1])
	{
		if (ft_strncmp(split_path[i], split_path[i + 1],
												ft_strlen(split_path[i])) == 0)
		{
			i++;
			while (split_path[i + 1] != NULL)
			{
				free(split_path[i]);
				split_path[i] = ft_strdup(split_path[i + 1]);
				i++;
			}
			free(split_path[count]);
			split_path[count] = NULL;
			count--;
			i = 0;
			continue ;
		}
		i++;
	}


}

static	void ft_skip_dot(char **split_path, size_t i, size_t *dot_count, int flag)
{
	size_t	count;

	count = 0;
	while(split_path[count])
		count++;
	while (split_path[i] && i < count - 1)
	{
		free(split_path[i]);
		split_path[i] = ft_strdup(split_path[i + 1]);
		i++;
	}
	free(split_path[i]);
	split_path[i] = NULL;
	(void)flag;
	(*dot_count)++;
}

static	char **ft_skip_and_count_dot(char **split_path, size_t *dot_count,
														size_t *dot_dot_count)
{
	int	i;

	i = 0;
	while (split_path[i])
	{
		if (ft_strncmp("..", split_path[i], 2) == 0)
			ft_skip_dot(split_path, i, dot_dot_count, 0);
		else if (ft_strncmp(".", split_path[i], 1) == 0)
			ft_skip_dot(split_path, i, dot_count, 1);
		else
			i++;
	}
	if ((*dot_dot_count) > 0)
		ft_check_dup_str(split_path);

	return (split_path);

}

char	*ft_convert_path(char **split_path)
{
	char *tmp;
	int		i;

	i = 0;
	tmp = ft_strdup("/");
	while (split_path[i])
	{
		tmp = ft_strjoin(tmp, split_path[i]);
		free(split_path[i]);
		if (split_path[i + 1] != NULL)
			tmp = ft_strjoin(tmp, "/");
		i++;
	}
	return (tmp);
}

char *ft_get_dir_path_absolute(char *second_argv)
{
	char **split_path;
	char *path;
	size_t	dot_count;
	size_t	dot_dot_count;

	dot_count = 0;
	dot_dot_count = 0;
	if (ft_strncmp("//", second_argv, 2) == 0)
		return (second_argv);
	split_path = ft_split(second_argv, '/');
	split_path = ft_skip_and_count_dot(split_path, &dot_count, &dot_dot_count);
	path = ft_convert_path(split_path);
	return (path);
}

char	*ft_marge_path(char **split_current_dir, char **split_path, size_t *dot_dot_count)
{
	int		count;
	char	*argv_path;
	char	*current_path;

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
	current_path = ft_convert_path(split_current_dir);
	current_path = ft_strjoin(current_path, argv_path);
	return (current_path);
}

char *ft_get_dir_path_relative( char *current_dir,
															char *second_argv)
{

	char	*path;
	char	**split_path;
	size_t	dot_count;
	size_t	dot_dot_count;

	dot_count = 0;
	dot_dot_count = 0;
	current_dir = ft_strjoin(current_dir, "/");
	path = ft_strjoin(current_dir, second_argv);
	split_path = ft_split(second_argv, '/');
	split_path = ft_skip_and_count_dot(split_path, &dot_count, &dot_dot_count);
	path = ft_marge_path(ft_split(current_dir, '/'), split_path, &dot_dot_count);
	return (path);
}

t_bool	ft_cd(t_cmd *cmd)
{
	extern	t_mshl_data *g_mshl_data;
	char	current_dir[PATH_MAX];
	char	*second_argv;
	char	*path;

	if (!getcwd(current_dir, PATH_MAX))
		ft_error_display("minishell", "cd: unexpected error", 1);
	if (cmd->argc < 2 || ft_is_tilde(cmd))
		return (ft_isnot_path(g_mshl_data, current_dir));
	second_argv = cmd->args->next->data;
	if (chdir(second_argv) != 0)
		return (ft_error_cd(second_argv));
	if (ft_strncmp("/", &second_argv[0], 1) == 0)
		path = ft_get_dir_path_absolute(second_argv);
	else
		path = ft_get_dir_path_relative(current_dir, second_argv);
	if (chdir(path) != 0)
		return (ft_error_cd(path));
	ft_env_update("PWD", path, g_mshl_data->envs);
	ft_env_update("OLDPWD", current_dir, g_mshl_data->envs);
	return (TRUE);
}
