/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 19:22:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 02:27:04 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				ft_ls(t_file *paths, char flags)
{
	DIR				*dir;
	struct dirent	*entry;

	while (paths)
	{
		if (!(dir = opendir(paths->name)))
		{
			ft_printf("ft_ls: %s: %s\n", paths->name, strerror(errno));
		}
		else
		{
			while ((entry = readdir(dir)))
				ft_printf("%s\n", entry->d_name);
			closedir(dir);
		}
		ft_putchar('\n');
		if (paths->next)
			paths = paths->next;
		else
			break ;
	}
	return (flags);
}