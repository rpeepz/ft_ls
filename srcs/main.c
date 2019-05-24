/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 21:48:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/23 22:13:56 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				main(int ac, char **av)
{
	char	flags;
	t_file	*paths;

	if (ac > 1)
	{
		flags = get_flags(av, 0, 0, 0);
		if (flags & 1UL << 6)
			if (write(1, "usage: ./ft_ls [-Ralrt] [file ...]\n", 35))
				return (0);
		if (!(paths = get_dirs(av, flags, 1, 0)))
			if (write(1, "malloc error, yo\n", 17))
				return (0);
	}
	else
	{
		flags = 0;
		if (!(paths = t_fileinit()))
			t_filedel(paths);
	}
//START TESTING
	system("leaks ft_ls");
	ft_printf("flag: [%#10.8b]\n", flags);
	while (paths)
	{
		ft_printf("indx: [%10d]\npath: [%*s]\nname: [%10s]\nfull: [%10s]\n\n",paths->index, 10, paths->path, paths->name, paths->full_path);
		if (paths->next)
			paths = paths->next;
		else
			break ;
	}
//END TESTING
//	ft_ls(paths);
	t_filedel(paths);
	return (0);
} 
