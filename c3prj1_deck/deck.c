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

// course 4

/*
 * Add the particular card to the given deck,
 * involve reallocing the array of cards
 */
void add_card_to(deck_t *deck, card_t c) {
  card_t ** new_cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(card_t *));
  if (new_cards == NULL) {
    perror("realloc error");
    exit(EXIT_FAILURE);
  }
  deck->cards = new_cards;

  // copy c to new allocated block
  card_t * new_card = malloc(sizeof(*new_card));
  if (new_card == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  // card_t do not has pointer type, so there is no problem of shallow copy
  /* new_card->suit = c.suit; */
  /* new_card->value = c.value; */
  *new_card = c;
  deck->cards[deck->n_cards] = new_card;
  deck->n_cards++;
}

/*
 * Add a card whose value and suit are both 0,
 * return a pointer to it in the deck.
 * Add an invalid card to use as a placeholder for unknown card
 */
card_t * add_empty_card(deck_t * deck) {
  // add_card_to function use type card_t not pointer,
  // and it allocates memory for card_t inside.
  // So we do not need to allocate memory more

  /* card_t * unknown_card = malloc(sizeof(*unknown_card)); */
  /* unknown_card->suit = 0; */
  /* unknown_card->value = 0; */
  /* add_card_to(deck, *unknown_card); */

  card_t card;
  card.suit = 0;
  card.value = 0;
  add_card_to(deck, card);
  return (deck->cards)[deck->n_cards-1];
}

/*
 * Create a deck that is full expect for all cards that appear in excluded_cards
 */

// because we can re-use add_card_to to simply the function
// I abort this function.
deck_t * make_deck_exclude_aborted(deck_t * excluded_cards) {
  deck_t * full_deck = malloc(sizeof(*full_deck));
  full_deck->cards = malloc(52 * sizeof(*full_deck));
  // alias for full_deck->cards
  card_t ** cards = full_deck->cards;
  full_deck->n_cards = 0;

  for (int i = 0; i < 52; i++) {
    card_t card = card_from_num(i);
    // if card is not in excluded_cards
    if (deck_contains(excluded_cards, card) == 0) {
      card_t *malloc_card_p = malloc(sizeof(card_t));
      malloc_card_p->suit = card.suit;
      malloc_card_p->value = card.suit;
      cards[full_deck->n_cards] = malloc_card_p;
      full_deck->n_cards++;
    }
  }
  return full_deck;
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * deck = malloc(sizeof(*deck));
  if (deck == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  deck->cards = NULL;
  deck->n_cards = 0;

  for (unsigned int i = 0; i < 52; i++) {
    card_t card = card_from_num(i);
    if(!deck_contains(excluded_cards, card)) {
      add_card_to(deck, card);
    }
  }

  return deck;
}

/*
 * Takes an array of hands. Then builds full deck of cards that exclude them
 */

// For the same reason, can simply the process of building excluded_cards
deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * excluded_cards = malloc(sizeof(*excluded_cards));
  if (excluded_cards == NULL) {
    perror("malloc error");
    exit(EXIT_FAILURE);
  }
  excluded_cards->n_cards = 0;
  excluded_cards->cards = NULL;

  //  int index = 0;
  for (size_t i = 0; i < n_hands; i++) {
    deck_t * hand = hands[i];

    /* excluded_cards->n_cards += hand->n_cards; */
    /* excluded_cards->cards = realloc(excluded_cards->cards, */
    /*                                excluded_cards->n_cards * sizeof(card_t *)); */
    /* // add cards in hand to excluded_cards */
    /* for (int j = 0; j < hand->n_cards; j++) { */
    /*   excluded_cards->cards[index] = hand->cards[j]; */
    /*   index++; */
    /* } */

    for (size_t j = 0; j < hand->n_cards; j++) {
      card_t * card = hand->cards[j];
      // check if there is duplication
      if (!deck_contains(excluded_cards, *card)) {
        add_card_to(excluded_cards, *card);
      }
    }
  }
  deck_t * remaining_deck = make_deck_exclude(excluded_cards);
  // free excluded_cards
  // watch out ! we have given the function prototype in the .h file
  // so the compiler know this function.
  free_deck(excluded_cards);
  return remaining_deck;
}

void free_deck(deck_t *deck) {
  if (deck == NULL) {
    return;
  }
  for (size_t i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
