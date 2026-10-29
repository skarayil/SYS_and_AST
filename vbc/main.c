/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:04:05 by skarayil          #+#    #+#             */
/*   Updated: 2026/10/29 18:14:11 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

int	main(int argc, char **argv)
{
	char *s;
	node *tree;
	int result;

	if (argc != 2)
		return (1);
	s = argv[1];
	tree = parse_expr(&s);
	if (!tree)
		return (1);
	if (*s)
	{
		unexpected(*s);
		destroy_tree(tree);
		return (1);
	}
	result = eval_tree(tree);
	printf("%d\n", result);
	destroy_tree(tree);
	return (0);
}