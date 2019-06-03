/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 19:22:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/02 20:20:04 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				ft_ls(t_file *paths, char flags)
{
//	DIR				*dir;
//	t_file			*entry;

	if (N_DIR(paths))
		print_first_files(&paths, flags, get_longest(paths));
	else if (flags ^ 0x2 && paths->index == 0)
		print_contents(paths)
	ft_printf("index: %d\n", paths->index);
//	while (paths)
//	{
//		dir = opendir(paths->name);
//		if (!dir)
//		{
//			ft_printf("ft_ls: %s: %s\n", paths->name, strerror(errno));
//		}
//		else
//		{
//			while ((entry = readdir(dir)))
//				ft_printf("%s\n", entry->d_name);
//			closedir(dir);
//		}
//		if (paths->next)
//			paths = paths->next;
//		else
//			break ;
//		ft_putchar('\n');
//	}
	return (0);
}
