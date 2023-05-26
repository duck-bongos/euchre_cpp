#include <string>
#include <iostream>
#include "card.h"

struct Score {
    int odds = 0;
    int evens = 0;
};


ostream &operator<<( ostream &output, const Score &S ) {
        string line = "-----------------------------\n";
        output << "The current score is:\n" << line << "Evens: " << S.evens << " Odds: " << S.odds << "\n" << endl; 
        return output;
}

struct handScore {
    int score;
    double probability;
};

struct calcBest {
    Card * card;
    int idx;
};

struct Trump {
    int suit;
    int alone = 0;
};

ostream &operator<<( ostream &output, const Trump& t ) {
    output << "Suit: " << t.suit << " Alone: " << t.alone << endl;
    return output;
}