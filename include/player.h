#include "card.h"
#include <vector>

class Player;
class Player
{
public:
    // based on loner status
    bool playing = true;
    bool dealer = false;  // whether the player is dealing or not
    
    // Singly linked list structure
    Player* next;
    
    // constructor
    Player();

    // destructor
    ~Player();

    vector<Card> cards;
    

    void addCardToHand(Card c)
    {
        hand->push_back(c);
    }

    void addCardToHand(Card *c)
    {
        hand->push_back(*c);
    }

    void addThree(vector<Card> cards[3])
    {
        for (auto c = cards->begin(); c != cards->end(); c++)
        {
            addCardToHand(*c);
        }
    }

    void addTwo(vector<Card> cards[2])
    {
        for (auto c = cards->begin(); c != cards->end(); c++)
        {
            addCardToHand(*c);
        }
    }

    // TODO need to figure out a way to sort based on "best" or choose based on best
    Card playCard()
    {
        return hand->front();
    }

private:
    vector<Card> hand[5];
};