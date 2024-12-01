#include < iostream>
#include < vector>
#include < map>

using namespace std;

struct Item {
    string name;
    int cost;
};

vector< string> getItemsToBuy(int n, const vector< int>& tokens, const vector< int>& claim, int k, const vector< Item>& items) {
    vector result;

    int maxTokens = 0;
    int startIndex = 0;

    // Find the starting index for the bumper offer
    for (int i = 0; i < n - k + 1; ++i) {
        int currentTokens = 0;
        for (int j = i; j < i + k; ++j) {
            if (claim[j] == 0) {
                currentTokens += tokens[j];
            }
        }

        if (currentTokens > maxTokens) {
            maxTokens = currentTokens;
            startIndex = i;
        }
    }

    // Calculate the total tokens and find the item(s) to buy
    int totalTokens = 0;
    map availableItems;

    for (int i = startIndex; i < startIndex + k; ++i) {
        if (claim[i] == 0) {
            totalTokens += tokens[i];
        }
    }

    for (const auto& item : items) {
        if (item.cost <= totalTokens) {
            availableItems[item.name] = item.cost;
        }
    }

    // Find the minimal wastage and lexicographically smallest item(s)
    int minimalWastage = totalTokens;
    for (const auto& item : items) {
        if (availableItems.find(item.name) != availableItems.end()) {
            int wastage = totalTokens - availableItems[item.name];
            if (wastage < minimalWastage) {
                minimalWastage = wastage;
                result.clear();
                result.push_back(item.name);
            } else if (wastage == minimalWastage) {
                result.push_back(item.name);
            }
        }
    }

    return result;
}

int main() {
    int n, k;
    cin >> n;

    vector tokens(n);
    for (int i = 0; i < n; ++i) {
        cin >> tokens[i];
    }

    vector claim(n);
    for (int i = 0; i < n; ++i) {
        cin >> claim[i];
    }

    cin >> k;

    cin.ignore(); // Ignore the newline character
    string itemsInput;
    getline(cin, itemsInput);

    vector< Item> items;
    size_t pos = 0;
    while ((pos = itemsInput.find(':')) != string::npos) {
        string itemName = itemsInput.substr(0, pos);
        itemsInput.erase(0, pos + 1);
        int itemCost = stoi(itemsInput.substr(0, itemsInput.find(' ')));
        itemsInput.erase(0, itemsInput.find(' ') + 1);
        items.push_back({itemName, itemCost});
    }

    vector< string> result = getItemsToBuy(n, tokens, claim, k, items);

    for (const auto& item : result) {
        cout << item << endl;
    }

    return 0;
}
