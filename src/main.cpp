/*
Author: Dan Billmann
GitHub: duck-bongos

Euchre, like all card games is a repeated comparison game. The goal is to compare favorably with your partner against another set of two partners.
*/

// Main file for Euchre gameplay
#include <card.h>
#include <deck.h>
#include <player.h>

// declare global variables
Player dealer;

enum Players
{
    sphinx,
    phoenix,
    leviathan,
    pegasus
};

int main()
{
    // gameplay
    // start with a deck of 24 cards
    Deck d = Deck();

    // cards are shuffled
    d.shuffle();

    // cards are dealt to 4 players
    Player sphinx = Player();
    Player phoenix = Player();
    Player leviathan = Player();
    Player pegasus = Player();

    // give person control of

    // need a dealer

    // then one card is flipped up

    // then first round of bidding "is done"
    // ?? how to evaluate bidding?

    // then second round of bidding "is done"
    // ?? how to evaluate bidding?
    return 0;
}