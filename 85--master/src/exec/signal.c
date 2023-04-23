/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mla-rosa <mla-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 21:45:55 by mla-rosa          #+#    #+#             */
/*   Updated: 2023/04/22 00:49:18 by mla-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/include.h"

void sig_handler(int sig) {
    if (sig == SIGINT){
         printf("\nCTRL+C détecté. Sortie.\n");
         rl_on_new_line();
         rl_replace_line("", 0);
         rl_redisplay();
         return;
    }
}

void sig_quit(int sig)
{
   if (sig == SIGQUIT) {
      printf("CTRL+D détecté. Sortie.\n");
      exit(0);
   }
}
