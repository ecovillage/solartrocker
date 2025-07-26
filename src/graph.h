/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:50:58 by jweingar          #+#    #+#             */
/*   Updated: 2025/07/23 12:50:58 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_H
#define GRAPH_H

void draw_graph(float *graph, float b_min, float b_max);
void draw_background(char *text, int b_min, int b_max);
void plot_graph(float *graph, char *text);

#endif