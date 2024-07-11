/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:45:39 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/11 12:32:57 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_H
# define UTILS_H

# include "../1_libft/libft.h"
# include "../2_structs/structs.h"


void	perror_exit(char *msg);
void	my_perror(char *msg);
void	*my_malloc(size_t size);
void	*my_calloc(size_t count, size_t size);
int		is_reserved(char c);
int		is_reserved_all(char c);
int		is_quote(char c);

#endif
