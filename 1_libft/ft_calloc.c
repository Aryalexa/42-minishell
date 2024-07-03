/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:29:07 by macastro          #+#    #+#             */
/*   Updated: 2023/09/15 18:29:09 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	The malloc(), calloc(), valloc(), realloc(), and reallocf() functions
	allocate memory. The free() function frees allocations that were created 
	via the preceding allocation functions.

	The malloc() function allocates size bytes of memory and returns a
    pointer to the allocated memory.
	
	The calloc() function contiguously allocates enough space for _count_
	objects that are _size_ bytes of memory each and returns a pointer to the
	allocated memory.  The allocated memory is filled with bytes of value
	zero.

	RETURN VALUES
	If successful, calloc(), malloc(), realloc(), reallocf(), valloc(), and
	aligned_alloc() functions return a pointer to allocated memory.  If there
	is an error, they return a NULL pointer and set errno to ENOMEM.
	// (SIZE_MAX / count) < size
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, count * size);
	return (ptr);
}
