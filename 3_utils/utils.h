/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:45:39 by msoriano          #+#    #+#             */
/*   Updated: 2024/07/18 15:39:14 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../1_libft/libft.h"
# include "../2_structs/structs.h"

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

void	my_perror_exit(char *msg);
void	my_perror(char *msg);
void	*my_malloc(size_t size);
void	*my_calloc(size_t count, size_t size);
int		is_reserved(char c);
int		is_reserved_all(char c);
int		is_quote(char c);
void	debug(char *msg);
void	debug_int(char *fdname, int fdint);
void	debug_str(char *name_desc, char* str);

#endif