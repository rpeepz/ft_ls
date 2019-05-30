/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dash_onef.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 03:31:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/30 05:12:16 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		print_entires(t_file *entries, t_file *paths)
{
	char			buf[PAGESIZE];

	ft_bzero(buf, PAGESIZE);
	if (paths->index)
		ft_sprintf(buf, "%s:\n", paths->path);
	ft_sprintf(&buf[LEN(buf)], "%s", ".\n..\n");
	while (entries)
	{
		ft_sprintf(&buf[LEN(buf)], "%s\n", entries->name);
		if (entries->next)
			entries = entries->next;
		else
			break ;
	}
	if (paths->next)
		ft_sprintf(&buf[LEN(buf)], "\n");
	ft_printf("%s", buf);
}

static int		get_entries(DIR **dir, t_file *paths)
{
	struct dirent	*entry;
	t_file			*entries;

	entries = NULL;
	while ((entry = readdir(*dir)))
	{
		if ((PARENT_DIR(entry->d_name)) || (CURRENT_DIR(entry->d_name)))
			continue ;
		if (!entries)
		{
			if (!(entries = t_fileinit(entry->d_name)) &&
				(!t_filedel(entries)))
				return (1);
		}
		else
		{
			if (t_fileadd(&entries, entry->d_name))
				IF_RETURN(!t_filedel(entries), 1);
		}
	}
	closedir(*dir);
	print_entires(entries, paths);
	t_filedel(entries);
	return (0);
}

int				dash_onef(t_file *paths)
{
	DIR				*dir;
	struct stat		info;
	char			buf[PAGESIZE];

	while (paths)
	{
		if (!(dir = opendir(paths->path)))
		{
			if ((lstat(paths->path, &info)) == 0 && !S_ISDIR(info.st_mode))
				ft_sprintf(buf, "%s\n", paths->path);
			else
				ft_sprintf(buf,
							"ft_ls: %s: %s\n", paths->path, strerror(errno));
			ft_printf("%s", buf);
		}
		else
		{
			IF_RETURN(get_entries(&dir, paths), 1);
		}
		if (paths->next)
			paths = paths->next;
		else
			break ;
	}
	return (0);
}
