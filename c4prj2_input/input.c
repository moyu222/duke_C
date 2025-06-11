#include "input.h"
#include "deck.h"
#include "future.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** hands = NULL;
  *n_hands = 0;

  char * linep = NULL;
  size_t sz = 0;
  while(getline(&linep, &sz, f) > 0) {
    deck_t * hand = hand_from_string(linep, fc);
    if (hand->n_cards < 5) {
      fprintf(stderr, "a poker hand has at least 5 cards in it.\n");
      exit(EXIT_FAILURE);
    }

    *n_hands += 1;
    hands = realloc(hands, *n_hands * sizeof(*hand));
    if (hands == NULL) {
      perror("realloc error");
      exit(EXIT_FAILURE);
    }
    hands[*n_hands-1] = hand;
  }
  free(linep);
  return hands;
}

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * hand = malloc(sizeof(*hand));
  if (hand == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  hand->cards = NULL;
  hand->n_cards = 0;

  // use strtok to split each card, copy the str because of const
  char * line_copy = strdup(str);
  if (line_copy == NULL) {
    perror("strdup error");
    exit(EXIT_FAILURE);
  }

  char * token = strtok(line_copy, " \t\n");
  while (token != NULL) {
    if (token[0] == '?') {
      card_t * ptr = add_empty_card(hand);
      int index = atoi(token + 1);
      add_future_card(fc, index, ptr);
    } else {
      card_t card = card_from_letters(token[0], token[1]);
      add_card_to(hand, card);
    }
    token = strtok(NULL, " \t\n");
  }

  free(line_copy);
  return hand;
}
