
#include<bits/stdc++.h>
using namespace std;

class KnapsackSolver {
public:
    int findMax(int a, int b) {
        return (a > b) ? a : b;
    }

    int knapsack01DP(vector<pair<int, pair<int, int>>> &items, int num, int capacity) {
        vector<vector<int>> dp(num + 1, vector<int>(capacity + 1, 0));

        for (int i = 1; i <= num; i++) {
            for (int j = 1; j <= capacity; j++) {
                if (items[i - 1].second.second <= j) {
                    dp[i][j] = findMax(dp[i - 1][j], items[i - 1].second.first + dp[i - 1][j - items[i - 1].second.second]);
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        // Print the entire table
        cout << "Dynamic Programming Table:\n";
        for (int i = 0; i <= num; i++) {
            for (int j = 0; j <= capacity; j++) {
                cout << setw(4) << dp[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "---------------------------------------------\n";

        cout << "Selected Items are:\n";
        cout << "---------------------------------------------\n";
        cout << left << setw(10) << "ITEM" << left << setw(10) << "PROFIT" << left << setw(10) << "WEIGHT" << left << setw(10) << "\n";

        int i = num, j = capacity;
        while (i > 0 && j > 0) {
            if (dp[i][j] != dp[i - 1][j]) {
                cout << "---------------------------------------------\n";
                cout << left << setw(10) << items[i - 1].first << left << setw(10) << items[i - 1].second.first << left << setw(10) << items[i - 1].second.second << left << setw(10) << "\n";
                j = j - items[i - 1].second.second;
            }
            i--;
        }
        cout << "=============================================\n";

        return dp[num][capacity];
    }
};

int main() {
    int num, capacity;
    cout << "Enter the number of items: ";
    cin >> num;
    cout << "Enter the capacity of the sack: ";
    cin >> capacity;

    vector<pair<int, pair<int, int>>> items;
    pair<int, pair<int, int>> tempVar;

    for (int i = 0; i < num; i++) {
        tempVar.first = i + 1;
        cout << "Enter the profit of item number " << i + 1 << ": ";
        cin >> tempVar.second.first;
        cout << "Enter the weight of item number " << i + 1 << ": ";
        cin >> tempVar.second.second;
        items.push_back(tempVar);
    }

    KnapsackSolver solver;
    int maxProfit = solver.knapsack01DP(items, num, capacity);

    cout << "Maximum Profit: " << maxProfit << "\n";

    return 0;
}
