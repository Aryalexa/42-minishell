/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:45:39 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/10 21:29:46 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ERROR_H
# define ERROR_H

# include "../1_libft/libft.h"


void	perror_exit(char *msg);
void	my_perror(char *msg);
void	*my_malloc(size_t size);
void	*my_calloc(size_t count, size_t size);

#endif