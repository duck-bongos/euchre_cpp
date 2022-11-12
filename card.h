#include <map>
#include <string>
#include "suit.h"

using namespace std;

class Card
{
public:
    string suit;      // e.g. "hearts"
    int suitValue;    // used to help with sorting and gameplay rules.
    string valueName; // e.g. "jack"
    int value;        // used to help with sorting and gameplay rules.
    unordered_map<string, int> cardNameToValue;
    unordered_map<string, int> cardValueToName;

    // Constructor
    Card(string suitName, string valueName)
    {
        _createNameToValueMap();

        Suit suit = Suit(suitName);
        int suitValue = suit.getSuitValue(suitName);

        value = cardNameToValue[valueName];
    };

    ~Card(); // Destructor

private:
    void _createNameToValueMap()
    {
        cardNameToValue.insert(pair<const string, int>("nine", 9));
        cardNameToValue.insert(pair<const string, int>("ten", 10));
        cardNameToValue.insert(pair<const string, int>("jack", 11));
        cardNameToValue.insert(pair<const string, int>("queen", 12));
        cardNameToValue.insert(pair<const string, int>("king", 13));
        cardNameToValue.insert(pair<const string, int>("ace", 14));
    }
};