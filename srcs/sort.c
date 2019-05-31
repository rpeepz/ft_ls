/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 04:39:11 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/30 17:59:59 by rpapagna         ###   ########.fr       */
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

void			t_file_mergesort(t_file **apath, char flags)
{
	;
}
