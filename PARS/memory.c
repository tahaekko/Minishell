/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:20:18 by idouni            #+#    #+#             */
/*   Updated: 2023/05/31 17:57:06 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*h_malloc(t_collector **collector_head, size_t s, void *p)
{
	t_collector	*tmp;
	t_collector	*new_node;

	new_node = malloc(sizeof(t_collector));
	p = malloc(s);
	if (!new_node || !p)
	{
		write (2, "\033[0;32mMALLOC_FAILED\033[0;37m\n", 29);
		// ft_collectorclear(collector_head);
		exit (1);
	}
	new_node->addr = p;
	if (!(*collector_head))
	{
		*collector_head = new_node;
		new_node->next = NULL;
	}
	else
	{
		tmp = *collector_head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->next = NULL;
	}
	return (p);
}

void	ft_collectorclear(t_collector **collector)
{
	t_collector	*node;
	t_collector	*n_node;

	if (!(*collector) || !collector)
		return ;
	node = *collector;
	while (node)
	{
		n_node = node->next;
		if (node->addr)
			free(node->addr);
		free(node);
		node = n_node;
	}
	*collector = NULL;
}

void	debug(void)
{
	printf("\x1B[32m");
	printf("\nDEBUG OK\n");
	printf("\x1B[0m");
}
