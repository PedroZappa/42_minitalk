/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:00:21 by passunca          #+#    #+#             */
/*   Updated: 2024/02/22 15:45:14 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

//=============================================================================/
//								Variables                                      /
//=============================================================================/

# define PAUSE  100 // for usleep()

//=============================================================================/
//								Librariy Headers                               /
//=============================================================================/

# include <signal.h>							// sigaction()

# include "../inc/libft/libft/libft.h"			// libft ibrary
# include "../inc/libft/ft_printf/ft_printf.h"

//=============================================================================/
//                               Structures                                    /
//=============================================================================/

/*	Handles the minitalk client-server protocol data.
 *		bits		: number of bits received
 *		data		: character/number received
 *		received	: 1 when message len received,
 *		msg			: message received
 *	*/
typedef struct s_protocol
{
	int		bits;
	int		data;
	int		received;
	char	*msg;
}				t_protocol;

//=============================================================================/
//							Function Prototypes                                /
//=============================================================================/

/* ft_sigaction.c */
void	ft_set_sigaction(struct sigaction *sa);

/* ft_send.c */
void	ft_send_bit(pid_t pid, char bit, char pause_flag);
void	ft_send_int(pid_t pid, int num);
void	ft_send_char(pid_t pid, char c);

#endif
