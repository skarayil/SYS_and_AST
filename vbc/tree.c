/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:14:26 by skarayil          #+#    #+#             */
/*   Updated: 2026/10/29 18:14:28 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

node	*new_node(t_nty type)
{
	node	*ret;

	ret = calloc(1, sizeof(node));
	if (!ret)
		return (NULL);
	ret->type = type;
	return (ret);
}

void	destroy_tree(node *n)
{
	if (!n)
		return ;
	destroy_tree(n->l);
	destroy_tree(n->r);
	free(n);
}