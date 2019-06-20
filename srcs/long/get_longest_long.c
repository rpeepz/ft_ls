/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_longest_long.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:37:19 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/20 03:41:09 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static void	init_for_int(int **arr)
{
	(*arr)[0] = 0;
	(*arr)[1] = 0;
	(*arr)[2] = 0;
	(*arr)[3] = 2;
}

int			*get_longest_file(t_file *paths)
{
	int				*arr;
	int				tmp[4];
	struct passwd	*user;
	struct group	*group;

	arr = malloc(sizeof(int) * 4);
	init_for_int(&arr);
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

static int	get_size_major_minor(t_file *paths)
{
	int		minor;
	int		major;

	if (!paths->info.st_size && (get_type(paths->info.st_mode) == 'c' ||
								get_type(paths->info.st_mode) == 'b'))
	{
		major = ft_intlen((int)major(paths->info.st_rdev));
		if ((minor = ft_intlen((int)minor(paths->info.st_rdev))) > 3)
			minor = 3;
		return (major + minor + 3);
	}
	return (ft_intlen(paths->info.st_size));
}

int			*get_longest_any(t_file *paths, char flags, uint64_t block)
{
	int				*arr;
	int				tmp[4];
	struct passwd	*user;
	struct group	*group;

	arr = malloc(sizeof(int) * 4);
	init_for_int(&arr);
	while (paths && (user = getpwuid(paths->info.st_uid)))
	{
		IF_THEN_CONTINUE(!(flags & 0x4) && paths->name[0] == '.',
			paths = paths->next);
		block += paths->info.st_blocks;
		group = getgrgid(paths->info.st_gid);
		tmp[0] = ft_intlen(paths->info.st_nlink);
		tmp[1] = ft_strlen(user->pw_name);
		tmp[2] = ft_strlen(group->gr_name);
		tmp[3] = get_size_major_minor(paths);
		IF_THEN(tmp[0] > arr[0], (arr[0] = tmp[0]));
		IF_THEN(tmp[1] > arr[1], (arr[1] = tmp[1]));
		IF_THEN(tmp[2] > arr[2], (arr[2] = tmp[2]));
		IF_THEN(tmp[3] > arr[3], (arr[3] = tmp[3]));
		paths = paths->next;
	}
	IF_THEN(block, ft_printf("total %llu\n", block));
	return (arr);
}
