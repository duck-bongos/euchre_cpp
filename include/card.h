#include <map>
#include <string.h>
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
    string color;   // e.g. "red"
    int colorValue; // red = 0, black = 1

    // Constructor
    Card(string suitName, string valueName)
    {
        _createNameToValueMap();

        Suit suit = Suit(suitName);
        int suitValue = suit.getSuitValue(suitName);

        value = cardNameToValue[valueName];

        if ("diamond".compare(suit.name) || strcmp(suitName, "heart"))
        {
            color = "red";
            colorValue = 0;
        }
        else
        {
            color = "black";
            colorValue = 1;
        }
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