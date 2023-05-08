#include <array>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "card.h"
#include "structs.h"


class Player {
    public:
        int team = 0;  // if team == 0 - even ELSE odd
        string name = "Player Zero";
        int placeHolder = 0;
        vector<Card*> hand;
        int prefSuit = - 1;
        int nextDiscardIdx = -1;

        template<typename T, size_t N>
        void addCards(array<T, N> cards) {
            // cout << cards.size() << endl;
            for (int i = 0; i < cards.size(); i++) {
                // cout << "Card: " << cards[i]->value << " of " << cards[i]->suit << endl;
                hand.push_back(cards[i]);
            }
        }

        template<Card*, size_t N>
        Card* bestCard(array<Card*, N>a) {
            int top = -1;
            int x;
            for (int i=0; i < N; i++) {
                if (a[i]->value > top) {
                    x = i;
                }
            }
            return &a[x];
        }

        Card* bestCard(vector<Card*>a) {
            int top = -1;
            int x;
            for (int i=0; i < a.size(); i++) {
                if (a[i]->value > top) {
                    x = i;
                }
            }
            return a[x];
        }

        template<Card*, size_t N>
        int bestCardIdx(array<Card*, N>a) {
            int top = -1;
            int idx_ = -1;
            for (int i=0; i < N; i++) {
                if (a[i]->value > top) {
                    idx_ = i;
                }
            }
            return idx_;
        }

        int bestCardIdx(vector<Card*>a) {
            int top = -1;
            int idx_ = -1;
            for (int i=0; i < a.size(); i++) {
                if (a[i]->value > top) {
                    idx_ = i;
                }
            }
            return idx_;
        }

        calcBest calculate(vector<Card*> options, vector<Card*> played, Score tricks) {
            // Need to locate the best card for the moment
            int k = 0;
            for (int i = 0; i < options.size(); i++) {
                if (options[i] != nullptr) {
                    if (options[i]->value > options[k]->value) {
                        k = i;
                    }
                }
            }
            calcBest cb = {options[k], k};
            return cb;
        }

        Card* playCard(int leadSuit, int trump, vector<Card*> played, Score tricks)  {
            vector<Card*> options;
            calcBest best;
            
            // Can I follow suit?
            if (leadSuit >=0 ) {
                for (auto c: hand) {
                    if (c->suit == leadSuit) {
                        options.push_back(c);
                    }
                }
            }
            if (options.size() == 0) {
                options = hand;
            }
            best = calculate(options, played, tricks);
            
            // what's trump
            // what's the trick count
            // who has played what
            nextDiscardIdx = best.idx;
            return best.card;
        };


        void discard() {
            // Free the pointer
            if (nextDiscardIdx >= 0) {
                // swap nextDiscardIdx with the last idx
                int last = hand.size() - 1;
                swap(hand[nextDiscardIdx], hand[last]);
                hand.pop_back();
            }
            else {
                cout << "No pointer to free" << endl;
            }
        }

        handScore scoreHand(int trump) {
            int s = 0;
            double p = 0.0;
            for (auto c: hand) {
                c->set_trump(trump);
                s += c->value;
                c->unset_trump();
            }
            p = (s / 115.0) * 100.0;
            handScore hs = {s, p};
            return hs;
        }

        int preferredSuit(int topSuit, int bidRound) {
            int maxScore = -1;
            int maxIdxSuit = -1;
            for (int i=0; i < 4; i++) {
                if (i == topSuit && bidRound > 1) {
                    maxIdxSuit = -2;
                }
                else {
                    handScore hS = scoreHand(i);
                    if (hS.score > maxScore && (hS.probability > (rand() % 100))) {
                        // add some randomness to calling trump
                        maxIdxSuit = i;
                        maxScore = hS.score;
                    }
                }
            }
            return maxIdxSuit;
        }
        
        int callTrump(Card * topCard, int round) {
            int roundOneSuit = topCard->suit;
            int pSuit = preferredSuit(roundOneSuit, round);
            // "Screw the Dealer"
            // if (round == 3) {
            //     pSuit = preferredSuit(roundOneSuit, round);
            //     return pSuit;
            // }
            // else if (round == 1 && pSuit == roundOneSuit) {
            //     return pSuit;
            // }
            // else if (round == 2) {

            // }
            return pSuit;
        }

        friend ostream &operator<<( ostream &output, const Player &P ) { 
            vector<Card*> h = P.hand;
            for (auto c: h) {
                if (c != NULL) {
                    output << *c << endl;
                }
                else {
                    output << "NULL of NULL" << endl;
                }
            }
            return output;            
      }
};