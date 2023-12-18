#include <iostream>
#include <vector>

using namespace std;

void PrintSubsetSum(int i, int n, const vector<int>& set, int targetSum, vector<int>& subset, bool& flag) {
    if (targetSum == 0) {
        flag = true;
        cout << "[ ";
        for (int i = 0; i < subset.size(); i++) {
            cout << subset[i] << " ";
        }
        cout << "]" << endl;
        return;
    }

    if (i == n) {
        return;
    }

    // Exclude the current element
    PrintSubsetSum(i + 1, n, set, targetSum, subset, flag);

    // Include the current element if it is less than or equal to the target sum
    if (set[i] <= targetSum) {
        subset.push_back(set[i]);
        PrintSubsetSum(i + 1, n, set, targetSum - set[i], subset, flag);
        subset.pop_back();
    }
}

int main() {
    int n;

    // Input validation for the number of elements in the set
    cout << "Enter the number of elements in the set: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid input. The number of elements should be greater than 0." << endl;
        return 1;  // Return an error code
    }

    vector<int> set(n);

    // Input validation for the elements of the set
    cout << "Enter the elements of the set: ";
    for (int i = 0; i < n; i++) {
        cin >> set[i];
    }

    int sum;

    // Input validation for the target sum
    cout << "Enter the target sum: ";
    cin >> sum;

    // Target sum should be non-negative
    if (sum < 0) {
        cout << "Invalid input. The target sum should be non-negative." << endl;
        return 1;  // Return an error code
    }

    vector<int> subset;
    bool flag = false;

    PrintSubsetSum(0, n, set, sum, subset, flag);

    if (!flag) {
        cout << "There is no subset with the target sum." << endl;
    }

    return 0;
}
