/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 21:48:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/30 06:41:23 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		dispatch_ls_mode(t_file *paths, char flags)
{	
	if (flags ^ 0x62)
	{
		ft_ls(paths, flags);
		return (0);
	}
	else
		return (dash_onef(paths));
}

static void		sort_paths(t_file **paths)
{
	t_file			*tmp;
	DIR				*dir;
	struct stat		info;

	tmp = *paths;
	while (tmp)
	{
		if (!(dir = opendir(tmp->path)))
		{
			if ((lstat(tmp->path, &info)) == 0 && !S_ISDIR(info.st_mode))
				;//Push down list and add item to front
			else
			{
				ft_printf("ft_ls: %s: %s\n", tmp->path, strerror(errno));
				t_filedelone(paths, tmp->index);
			}
		}
		ft_printf("--------------------------\n");
		ft_printf("DIR: %s\n--------------------------\n", tmp->path);
		system("leaks ft_ls");
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
}

int				main(int ac, char **av)
{
	char			flags;
	t_file			*paths;

	flags = 0;
	if (ac > 1)
	{
		if ((flags = get_flags(av, 0, 0, 0)) == '~')
			IF_RETURN(write(1, "usage: ./ft_ls [-Ralrt] [file ...]\n", 35), 0);
		if (!(paths = get_dirs(av, 1, 0)))
			IF_RETURN(write(1, "malloc error, yo\n", 17), 0);
	}
	else
	{
		if (!(paths = t_fileinit(".")))
			t_filedel(paths);
	}
	if (!paths->next)
		paths->index = 0;
	else
		sort_paths(&paths);
	if (dispatch_ls_mode(paths, flags))
		write(1, "malloc error, yo\n", 17);
	t_filedel(paths);
	return (0);
}
