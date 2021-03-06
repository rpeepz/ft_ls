/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archived.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 19:24:08 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/02 00:13:11 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			sort_paths(t_file **paths)
{
	t_file			*tmp;
	DIR				*dir;
	struct stat		info;

	tmp = *paths;
	while (tmp)
	{
		dir = opendir(tmp->path);
		if (!(dir))
		{
			if ((lstat(tmp->path, &info)) == 0 && !S_ISDIR(info.st_mode))
				tmp = t_filepushfront(paths, tmp->index);
			else
			{
				ft_printf("ft_ls: %s: %s\n", tmp->path, strerror(errno));
				t_filedelone(paths, tmp->index);
			}
		}
		else
			closedir(dir);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
}

t_file			*t_filepushfront(t_file **apath, int index)
{
	t_file		*tmp;
	t_file		*prev;

	tmp = *apath;
	IF_RETURN(tmp->index == index, tmp);
	while (tmp && tmp->index != index)
	{
		prev = tmp;
		IF_THEN_CONTINUE(tmp->next, tmp = tmp->next);
		IF_BREAK(!tmp->next);
	}
	prev->next = tmp->next;
	tmp->next = *apath;
	*apath = tmp;
	return (prev);
}
