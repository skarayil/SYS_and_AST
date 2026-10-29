/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:03:58 by skarayil          #+#    #+#             */
/*   Updated: 2026/10/29 18:14:02 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VBC_H
# define VBC_H

# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_nodetype
{
	ADD,
	MULTI,
	VAL
}				t_nty;

typedef struct node
{
	t_nty		type;
	int			val;
	struct node	*l;
	struct node	*r;
}				node;

node			*new_node(t_nty type);
void			destroy_tree(node *n);

void			unexpected(char c);
int				accept(char **s, char c);
int				expect(char **s, char c);

node			*parse_expr(char **s);
node			*parse_term(char **s);
node			*parse_factor(char **s);
node			*parse_digit(char **s);

int				eval_tree(node *tree);

#endif