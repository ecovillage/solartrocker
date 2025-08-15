/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 08:34:39 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/15 08:34:39 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENUE_H
#define MENUE_H

struct MenuItem {
  const char* label;
  void (*action)();  // Funktionszeiger auf eine Funktion ohne Parameter und ohne Rückgabewert
};

void handleSelection(int index);
void drawMenu();
void show_menue();
void drawMenuItem(char *nb, char *entry, bool selected);
void change_luefter();
void change_klappen();
void set_selectedItem(int nb);

#endif