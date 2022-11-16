#include <map>
#include <string>
#include <unordered_map>

using namespace std;

class Suit
{
public:
    // constructor
    Suit(string suitName)
    {
        unordered_map<string, int> suits;
        suits.insert(pair<const string, int>("clubs", 1));
        suits.insert(pair<const string, int>("club", 1));
        suits.insert(pair<const string, int>("diamonds", 2));
        suits.insert(pair<const string, int>("diamond", 2));
        suits.insert({"spades", 3});
        suits.insert({"spade", 3});
        suits.insert({"hearts", 4});
        suits.insert({"heart", 4});
    };
    int suitValue;
    string name;

    ~Suit(); // This is a destructor

    int getSuitValue(string str)
    {
        unordered_map<string, int>::const_iterator found = suits.find(str);
        int retVal;
        if (found == suits.end())
        {
            retVal = -1;
        }
        else
        {
            retVal = suits[str];
        }
        return retVal;
    };

private:
    unordered_map<string, int> suits;
};
