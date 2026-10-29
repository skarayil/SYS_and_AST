/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:15:13 by skarayil          #+#    #+#             */
/*   Updated: 2026/10/29 18:15:18 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

node	*parse_digit(char **s)
{
	node	*n;

	if (!isdigit((unsigned char)**s))
	{
		unexpected(**s);
		return (NULL);
	}
	n = new_node(VAL);
	if (!n)
		return (NULL);
	n->val = **s - '0';
	(*s)++;
	return (n);
}

node	*parse_factor(char **s)
{
	node	*n;

	if (accept(s, '('))
	{
		n = parse_expr(s);
		if (!n)
			return (NULL);
		if (!expect(s, ')'))
		{
			destroy_tree(n);
			return (NULL);
		}
		return (n);
	}
	return (parse_digit(s));
}

node	*parse_term(char **s)
{
	node	*left;
	node	*right;
	node	*parent;

	left = parse_factor(s);
	if (!left)
		return (NULL);
	while (accept(s, '*'))
	{
		right = parse_factor(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		parent = new_node(MULTI);
		if (!parent)
		{
			destroy_tree(left);
			destroy_tree(right);
			return (NULL);
		}
		parent->l = left;
		parent->r = right;
		left = parent;
	}
	return (left);
}

node	*parse_expr(char **s)
{
	node	*left;
	node	*right;
	node	*parent;

	left = parse_term(s);
	if (!left)
		return (NULL);
	while (accept(s, '+'))
	{
		right = parse_term(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		parent = new_node(ADD);
		if (!parent)
		{
			destroy_tree(left);
			destroy_tree(right);
			return (NULL);
		}
		parent->l = left;
		parent->r = right;
		left = parent;
	}
	return (left);
}
