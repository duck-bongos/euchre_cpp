struct Score {
    int odds = 0;
    int evens = 0;
};


struct handScore {
    int score;
    double probability;
};

struct calcBest {
    Card * card;
    int idx;
};

ostream &operator<<( ostream &output, const Score &S ) {
        output << "The score is Evens: " << S.evens << " Odds: " << S.odds << endl; 
        return output;
}