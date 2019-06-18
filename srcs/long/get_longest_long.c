/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_longest_long.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:37:19 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/17 20:50:13 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

int			*get_longest_file(t_file *paths)
{
	int				*arr;
	int				tmp[4];
	struct passwd	*user;
	struct group	*group;

	arr = malloc(sizeof(int) * 4);
	arr[0] = 2;
	arr[1] = 0;
	arr[2] = 0;
	arr[3] = 2;
	while (paths && N_DIR(paths))
	{
		user = getpwuid(paths->info.st_uid);
		group = getgrgid(paths->info.st_gid);
		tmp[0] = ft_intlen(paths->info.st_nlink);
		tmp[1] = ft_strlen(user->pw_name);
		tmp[2] = ft_strlen(group->gr_name);
		tmp[3] = ft_intlen(paths->info.st_size);
		IF_THEN(tmp[0] > arr[0], (arr[0] = tmp[0]));
		IF_THEN(tmp[1] > arr[1], (arr[1] = tmp[1]));
		IF_THEN(tmp[2] > arr[2], (arr[2] = tmp[2]));
		IF_THEN(tmp[3] > arr[3], (arr[3] = tmp[3]));
		paths = paths->next;
	}
	return (arr);
}

static void	block_size(t_file *paths, char flags)
{
	uint64_t	blocks;

	blocks = 0;
	while (paths)
	{
		IF_THEN_CONTINUE(!(flags & 0x4) && paths->name[0] == '.',
			paths = paths->next);
		blocks += paths->info.st_blocks;
		paths = paths->next;
	}
	if (blocks)
		ft_printf("total %llu\n", blocks);
}

int			*get_longest_any(t_file *paths, char flags)
{
	int				*arr;
	int				tmp[4];
	struct passwd	*user;
	struct group	*group;

	arr = malloc(sizeof(int) * 5);
	arr[0] = 2;
	arr[1] = 0;
	arr[2] = 0;
	arr[3] = 2;
	block_size(paths, flags);
	while (paths && (user = getpwuid(paths->info.st_uid)))
	{
		group = getgrgid(paths->info.st_gid);
		tmp[0] = ft_intlen(paths->info.st_nlink);
		tmp[1] = ft_strlen(user->pw_name);
		tmp[2] = ft_strlen(group->gr_name);
		tmp[3] = ft_intlen(paths->info.st_size);
		IF_THEN(tmp[0] > arr[0], (arr[0] = tmp[0]));
		IF_THEN(tmp[1] > arr[1], (arr[1] = tmp[1]));
		IF_THEN(tmp[2] > arr[2], (arr[2] = tmp[2]));
		IF_THEN(tmp[3] > arr[3], (arr[3] = tmp[3]));
		paths = paths->next;
	}
	return (arr);
}
