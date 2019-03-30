/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:43:41 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/03/29 16:32:26 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	if_atoif_f(unsigned long int res, int sign)
{
	if (res == 2147483648 && sign < 0)
		return (-2147483648);
	else
		return (-1);
}

int			ft_atoi_true(const char *str)
{
	int					i;
	unsigned long long	res;
	int					sign;

	i = 0;
	res = 0;
	sign = 1;
	if (*str == '\0')
		return (0);
	while (str[i] == ' ' || str[i] == '\v' || str[i] == '\n' || \
		str[i] == '\f' || str[i] == '\t' || str[i] == '\r')
		++i;
	(str[i] == '-') ? sign *= -1 : sign;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - 48;
		++i;
	}
	if (res > 2147483647)
		return (if_atoif_f(res, sign));
	return ((int)res * sign);
}

void		print_node(t_ring **root)
{
	t_elem *current_node;

	current_node = (*root)->current;
	if ((*root)->current == NULL)
		return ;
	while (current_node->next != (*root)->current
	&& (*root)->current->next != NULL)
	{
		printf("%d ", current_node->num);
		current_node = current_node->next;
	}
	printf("%d ", current_node->num);
}

void		ft_swap_int(int *a, int *b)
{
	int c;

	c = *a;
	*a = *b;
	*b = c;
}

void		python_parser(t_ring *stack_a, t_ring *stack_b)
{
	t_elem	*ptr;
	int		size;

	ptr = stack_a->current;
	size = stack_a->size;
	while (--size >= 0)
	{
		ft_printf("%d ", ptr->num);
		ptr = ptr->next;
	}
	ft_printf("| ");
	ptr = stack_b->current;
	size = stack_b->size;
	if (size <= 0)
		return ;
	while (--size > 0)
	{
		if (size > 1)
			ft_printf("%d ", ptr->num);
		else
			ft_printf("%d", ptr->num);
		ptr = ptr->next;
	}
	ft_printf("\n");
}
