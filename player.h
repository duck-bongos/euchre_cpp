#include "card.h"
#include <vector>

class Player
{
public:
    // constructor
    Player();

    // destructor
    ~Player();

    void addCardToHand(Card c)
    {
        hand->push_back(c);
    }

    Card playCard()
    {
        return hand->front();
    }

private:
    vector<Card> hand[5];
};