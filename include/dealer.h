#include "card.h"
#include <queue>
#include <vector>

using namespace std;

class Dealer
{
public:
    vector<Card> v;
    queue<Card> cards;
    bool three = true;

    Dealer(vector<Card> vec)
    {
        vector<Card> v = vec;
    }
    ~Dealer();

    queue<Card> prep_deck(vector<Card> vect)
    {
        template <typename Iter, typename Q>
        push_range(Q & q, Iter begin, Iter end)
        {
            // TODO not sure if this is how size() works
            for (int i = 0; i < 24; i++)
            {
                cards.push(vect[i]);
            }
        }
        return cards;
    }

    vector<Card> deal()
    {
        if (three == true)
        {
            vector<Card> cards[3];
            three = false;
        }
    };
};