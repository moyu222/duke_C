#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include "cards.h"
void print_hand(deck_t * hand){
  size_t n = hand->n_cards;
  card_t ** cards = hand->cards;
  for (size_t i = 0; i < n; i++) {
    print_card(*cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  size_t n = d->n_cards;
  card_t ** cards = d->cards;
  for (size_t i = 0; i < n; i++) {
    if (cards[i]->suit == c.suit && cards[i]->value == c.value) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  size_t d_size = d->n_cards;
  for (size_t i = 0; i < d_size - 1; i++) {
    size_t j = i + rand() / (RAND_MAX / (d_size - i) - 1);
    card_t * temp = d->cards[i];
    d->cards[i] = d->cards[j];
    d->cards[j] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  for (size_t i = 0; i < d->n_cards - 1; i++) {
    deck_t rest_d;
    rest_d.cards = d->cards + 1 + i;
    rest_d.n_cards = d->n_cards -i -1;
    assert(!deck_contains(&rest_d, *(d->cards[i])));
  }
}
