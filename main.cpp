// Main file for Euchre gameplay
#include "card.h"
#include "deck.h"

int main()
{
    // gameplay
    // start with a deck of 24 cards
    Deck d = Deck();
    vector<Card> deck = d.deck;

    // cards are shuffled
    deck.shuffle();

    // cards are dealt
    // need a dealer

    // then one card is flipped up

    // then first round of bidding "is done"
    // ?? how to evaluate bidding?

    // then second round of bidding "is done"
    // ?? how to evaluate bidding?
    return 0;
}