/*
Author: Dan Billmann
GitHub: duck-bongos

Euchre, like all card games is a repeated comparison game. 
The goal is to compare favorably with your partner against 
another set of two partners.
*/
/* What do you need?
Deck
24 Cards
4 Players
*/

/* Mechanisms for 

Comparison of cards
iterating through players
declaring trump
X setting left bauer value

playing cards into a "hand"
Translating between human readable and computational 


? How do I incorporate "states" 
- going alone
X changing trump
*/

/*
? How to I declare "
If this suit WERE trump, this is how good my hand would be."
*/
#include <array>
#include <assert.h>
#include <iostream>
#include <random>
#include <stdio.h>
#include <vector>
#include "core/card.h"
#include "core/deck.h"
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/bulk_write_exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#ifndef STRUCTS_H
#define STRUCTS_H

// define the Mongo CXX client
mongocxx::instance instance{};
mongocxx::uri uri("mongodb://localhost:27017");
mongocxx::client client{uri};

auto EUCHRE_DB = client["euchre"];

// commonly referred to as 'collection'
auto GAMES = EUCHRE_DB["games"];

// Define BSON
using bsoncxx::builder::basic::document;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

using namespace std;


bsoncxx::document::value recordCard(Card * c) {
    int s = c->suit;
    int v = c->value;
    auto record = make_document(kvp("suit", s), kvp("value", v));
    return record;
}

bsoncxx::array::value makeTrick(vector<Card*> played) {
    vector<bsoncxx::document::value> trick;
    for (int i = 0; i < played.size(); i++) {
        bsoncxx::document::value d = recordCard(played[i]);
        trick.push_back(d);
    }

    // loner
    if (played.size() < 4) {
        return make_array(trick[0], trick[1], trick[2]);
    }
    // normal
    else {
        return make_array(trick[0], trick[1], trick[2], trick[3]);
    }
}

bsoncxx::document::value recordScore(Score s) {
    return make_document(
        kvp("evens", s.evens),
        kvp("odds", s.odds)
    );
}

// compare hand - basically an argmax algorithm
template <typename T, int N>
int whoWins(array<int, N> * a, int n) {
    // a = player array
    return max_element(*a->begin(), *a->end());
}

int whoWins(vector<Card*>trick) {
    int winner = 0;
    for (int i = 0; i < trick.size(); i++) {
        if (trick[winner]->value < trick[i]->value) {
            winner = i;
        }
    }
    cout << "The best card is " << *(trick[winner]) << endl;
    return winner;
}

void showHands(Player * players[]) {
    for (int i = 0; i < 4; i++) {
        Player p = *players[i];
        cout << p << endl;
    }
}

void showHand(Player * p) {
    cout << *(p) << endl;
}

void showTrick(vector<Card*>trick) {
    for (int i = 0; i < trick.size(); i++) {
        Card cc = *trick[i];
        cout << cc << endl;
    }
}



Score tallyScore(Score score, Score tricks, int whoCalledTrump, int whoCalledAlone) {
    // multiplier for going alone, defaults to -1
    int loner = (whoCalledAlone > -1) ? 2 : 1;
    if (tricks.odds == 3 || tricks.odds == 4) {
        if (whoCalledTrump == 1) {
            // Regular
            score.odds += 1;
        }
        else {
            // Euchred
            score.evens += 2;
        }
    }
    else if (tricks.evens == 3 || tricks.evens == 4) {
        if (whoCalledTrump == 0) {
            // Regular
            score.evens += 1;
        }
        else {
            // Euchred
            score.odds += 2;
        }
    }
    else if (tricks.odds == 5 && whoCalledTrump == 1) {
        // Declare trump, Win all tricks
        score.odds += 2 * loner;
    }
    else if (tricks.evens == 5 && whoCalledTrump == 0) {
        // Declare trump, Win all tricks
        score.evens += 2 * loner;
    }
    else if (tricks.odds == 5 && whoCalledTrump == 0) {
        // Declare trump, Lose all tricks
        score.odds += 2;
    }
    else if (tricks.evens == 5 && whoCalledTrump == 1) {
        // Declare trump, Lose all tricks
        score.evens += 2;
    }
    
    return score;
};


void play(int gameID) {
    srand(time(NULL));
    Deck deck = Deck();
    // deck.printAll();
    int dealer = deck.pickDealer();
    int leader = (dealer + 1) % 4;
    int r = rand() % 1000;
    // cout << "Player " << dealer << "'s hand: " << endl;
    Player one = Player();
    one.name = "Player One";
    Player two = Player();
    two.name = "Player Two";
    Player three = Player();
    three.name = "Player Three";
    Player four = Player();
    four.name = "Player Four";

    Score score = Score();
    Score tricks = Score();

    // cout << one << endl;
    // cout << "Preferred Suit: " << suits.at(one.preferredSuit()) << endl;

    // Set order and teams
    Player* order[4] = {&one, &two, &three, &four};
    for (int i = 0; i < 4; i++) {
        if (i % 2 == 1) {
            order[i]->team = 1;
        }
    }

    int timesThrough = 0;

    int w = 1;

    while ( score.evens < 10 && score.odds < 10 ) {
        // deal the cards
        cout << score << endl;
        Card* topCard = deck.dealCards(dealer, &one, &two, &three, &four);
        cout << "Dealer: " << order[dealer]->name << endl;
        cout << "Leader: " << order[leader]->name << endl;

        Trump trump = {};
        trump.suit = -1;
        trump.alone = 0;

        int whoCalledTrump = -1;
        tricks.evens = 0;
        tricks.odds = 0;
        // -------
        // BIDDING
        // --------
        // first round of bidding
        int lonerIdx = -1;
        int skipPartner = -1;
        for (int i = 0; i < 4; i++) {
            int bidderIdx = (leader + i) % 4;
            trump = order[bidderIdx]->callTrump(topCard, 1);
            if (trump.suit >= 0) {
                whoCalledTrump = order[bidderIdx]->team;
                cout << "Team " << whoCalledTrump << " picked up the " << *topCard << "!" << endl;
                if (trump.alone > 0) {
                    skipPartner = ((bidderIdx + 2) % 4);
                }
                break;
            }
        }
        
        // second round of bidding
        if (trump.suit < 0) {
            for (int i = 0; i < 4; i++) {
                int bidderIdx = (leader + i) % 4;
                trump = order[bidderIdx]->callTrump(topCard, 2);
                if (trump.suit >= 0) {
                    whoCalledTrump = order[bidderIdx]->team;
                    if (trump.alone > 0) {
                        skipPartner = ((bidderIdx + 2) % 4);
                    }
                    break;
                }

                // SCREW THE DEALER
                if (trump.suit < 0 && i == 3) {
                    trump = order[bidderIdx]->callTrump(topCard, 3);
                    whoCalledTrump = order[bidderIdx]->team;
                    if (trump.alone > 0) {
                        skipPartner = ((bidderIdx + 2) % 4);
                    }
                    assert (trump.suit >= 0);
                }
            }   
        }
        /* 
        +++++++++++++++
        +++ PLAYING +++
        +++++++++++++++
        */
        // five cards per hand
        cout << "Hand number: " << w << endl;
        showHands(order);

        int f = 1;
        for (int i = 0; i < 5; i++) {
            int leadSuit = -1;
            vector<Card*> played;

            // play one trick
            for (int i = 0; i < 4; i++) {
                if (i == skipPartner) {
                    // Going alone!!
                    cout << "Loner in progress! Skipping partner ID " << skipPartner << endl;
                    continue;
                }
                else {
                    int playerIdx = (leader + i) % 4;
                    int partnerIdx = (playerIdx + 2) % 4;
                    Player* p = order[playerIdx];
                    Card* c = p->playCard(leadSuit, trump, played, tricks);
                    if (i == 0) {
                        leadSuit = c->suit;
                    }
                    cout << "Player Idx " << playerIdx << ", name " << p->name << " played " << *c << endl;
                    played.push_back(c);
                    // c->discard();
                }
            }
            
            // showTrick(played);

            int winnerIdx = whoWins(played);
            cout << order[winnerIdx]->name << " wins the trick!\n" << endl;
            leader = winnerIdx;
            int team = order[winnerIdx]->team;
            if(team % 2 == 1) {
                tricks.odds += 1;
            }
            else {
                tricks.evens += 1;
            }

            // Write game record to database            
            bsoncxx::document::value s = recordScore(score);
            bsoncxx::document::value t = recordScore(tricks);
            bsoncxx::array::value haaa = makeTrick(played);
            
            auto db_response = GAMES.insert_one(make_document(
                kvp("game", gameID),
                kvp("handNo", f),
                kvp("dealerId", dealer),
                kvp("leaderId", leader),
                kvp("leadSuit", leadSuit),
                kvp("trump", trump.suit),
                kvp("topCard", recordCard(topCard)), 
                kvp("played", haaa),
                kvp("tricks", t),
                kvp("score", s)
            ));
            assert(db_response);

            // now discard so you don't repeat
            for (int i = 0; i < played.size(); i++) {
                played[i]->discard();
                order[i]->discard();
            }

            // no point in playing the last card
            if ((tricks.odds == 3 && tricks.evens == 1) || (tricks.odds == 1 && tricks.evens == 3)) {
                continue;
            }

            showHands(order);

            // Increase hand number
            f++;
        
        }

        // score the tricks
        int a = 0;
        if (lonerIdx > 0) {
            a = order[lonerIdx]->team;
        }

        score = tallyScore(score, tricks, whoCalledTrump, a);

        // Move to next dealer
        dealer++;
        dealer = dealer % 4;
        cout << "Next dealer name: " << order[dealer]->name << endl;

        leader = (dealer + 1) % 4;
        cout << "Next leader name: " << order[leader]->name << endl;


        // Rebuild the deck since all values are set to NULL
        deck.buildDeck();
        // deck.printAll();
        cout << "\n" << endl;
        timesThrough++;
    }

    cout << score << endl;
    if (score.evens > score.odds) {
        cout << "Evens win!" << endl;
    }
    else {
        cout << "Odds win!" << endl;
    }

}


int main() {
    int gameID = 0;
    while (gameID < 1) {
        play(gameID);
        gameID++;
    }

    return 0;
}

#endif