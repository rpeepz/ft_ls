/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 17:58:30 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/23 19:09:58 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file			*t_filedel(t_file *file)
{
	if (file->path != NULL)
		free(file->path);
	if (file->name != NULL)
		free(file->name);
	if (file->full_path != NULL)
		free(file->full_path);
	if (file->next != NULL)
		t_filedel(file->next);
	else
		free(file);
	return (NULL);
}

t_file			*t_fileinit(void)
{
	t_file	*file;

	if (!(file = ft_memalloc(sizeof(t_file))))
		return (NULL);
	file->next = NULL;
	if (!(file->path = (char *)ft_memalloc(sizeof(char) * 2)) ||
		!(file->name = (char *)ft_memalloc(sizeof(char) * 2)) ||
		!(file->full_path = (char *)ft_memalloc(sizeof(char) * 3)))
		return (t_filedel(file));
	file->index = 1;
	file->path = ft_strcpy(file->path, ".");
	file->name = ft_strcpy(file->name, ".");
	file->full_path = ft_strcpy(file->full_path, "./");
	return (file);
}
