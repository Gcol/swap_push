/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:05:31 by gcollett          #+#    #+#             */
/*   Updated: 2017/09/07 15:07:09 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include <libft.h>

int		launch_instruction(char *str, long ***tab);
long	***parser_swap(char **argv, int argc);
int		str_is_valid(char **format, char *str, char *first_carac);

#endif
