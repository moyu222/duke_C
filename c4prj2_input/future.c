#include "future.h"
#include "deck.h"
#include <stdlib.h>
#include <stdio.h>

void add_future_card(future_cards_t *fc, size_t index, card_t *ptr) {
  // check if fc deck num can handle the index
  // reallocate if required
  if (fc->n_decks < (index + 1)) {
    fc->n_decks = index+1;
    fc->decks = realloc(fc->decks, fc->n_decks * sizeof(*fc->decks));
    if (fc->decks == NULL) {
      perror("realloc error");
      exit(EXIT_FAILURE);
    }
    fc->decks[index].cards = NULL;
    fc->decks[index].n_cards = 0;
  }

  // append the cards in the fc->decks[index] deck_t
  deck_t * deck = &(fc->decks[index]);
  deck->n_cards += 1;
  deck->cards = realloc(deck->cards, deck->n_cards * sizeof(card_t *));
  if (deck->cards == NULL) {
    perror("realloc error");
    exit(EXIT_FAILURE);
  }
  deck->cards[deck->n_cards - 1] = ptr;
}

void future_cards_from_deck(deck_t *deck, future_cards_t *fc) {
  if (deck->n_cards < fc->n_decks) {
    fprintf(stderr, "deck card number is wrong\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < fc->n_decks; i++) {
    card_t * real_card = deck->cards[i];
    deck_t * deck = &(fc->decks[i]);
    for (size_t j = 0; j < deck->n_cards; j++) {
      // copy real_card to deck->cards[j]
      *deck->cards[j] = *real_card;
    }
  }
}
