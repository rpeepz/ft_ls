/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file_mergesort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 04:39:11 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/20 06:43:08 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		sort_args(t_file *a, t_file *b, char flags)
{
	if (flags & 0x8)
	{
		IF_RETURN(Y_DIR(a) && N_DIR(b), 0);
		return (1);
	}
	if (flags & 0x20)
	{
		if (N_DIR(a))
		{
			IF_RETURN(N_DIR(b), ft_strcmp(a->name, b->name) <= 0 ? 0 : 1);
			return (1);
		}
		if (Y_DIR(a))
			IF_RETURN(Y_DIR(b), ft_strcmp(a->name, b->name) <= 0 ? 0 : 1);
		return (0);
	}
	if (N_DIR(a))
	{
		IF_RETURN(N_DIR(b), ft_strcmp(a->name, b->name) <= 0 ? 1 : 0);
		return (1);
	}
	if (CURRENT_DIR(a->name) || PARENT_DIR(a->name))
		return (0);
	return (ft_strcmp(a->name, b->name) <= 0 ? 1 : 0);
}

static int		dispatch_sort(t_file *a, t_file *b, char flags, int type)
{
	long	equal;

	if (type == 1)
		return (sort_args(a, b, flags));
	if (flags & 0x8)
	{
		IF_RETURN(CURRENT_DIR(a->name) || PARENT_DIR(a->name) ||
				CURRENT_DIR(b->name) || PARENT_DIR(b->name),
				ft_strcmp(a->name, b->name) <= 0 ? 1 : 0);
		return (1);
	}
	if (flags & 0x40)
	{
		equal = a->info.st_mtimespec.tv_sec - b->info.st_mtimespec.tv_sec;
		if (!equal)
			equal = a->info.st_mtimespec.tv_nsec - b->info.st_mtimespec.tv_nsec;
		if (flags & 0x20)
			return (equal > 0 ? 0 : 1);
		return (equal > 0 ? 1 : 0);
	}
	if (flags & 0x20)
		return (ft_strcmp(a->name, b->name) <= 0 ? 0 : 1);
	return (ft_strcmp(a->name, b->name) <= 0 ? 1 : 0);
}

static t_file	*sorted_merge(t_file *a, t_file *b, char flags, int type)
{
	t_file	*result;

	result = NULL;
	if (!a)
		return (b);
	if (!b)
		return (a);
	if (dispatch_sort(a, b, flags, type))
	{
		result = a;
		result->next = sorted_merge(a->next, b, flags, type);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next, flags, type);
	}
	return (result);
}

static void		list_split(t_file *source, t_file **front, t_file **back)
{
	t_file	*fast;
	t_file	*slow;

	slow = source;
	fast = source->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = source;
	*back = slow->next;
	slow->next = NULL;
}

void			t_file_mergesort(t_file **apath, char flags, int type)
{
	t_file	*a;
	t_file	*b;
	t_file	*head;

	head = *apath;
	if (!head || !head->next)
		return ;
	list_split(head, &a, &b);
	t_file_mergesort(&a, flags, type);
	t_file_mergesort(&b, flags, type);
	*apath = sorted_merge(a, b, flags, type);
}

/*
**	Code for this merge sorting algorithm was inspired by this article
**	https://www.geeksforgeeks.org/merge-sort-for-linked-list/
**	and adapted by me to fit into my program
*/
