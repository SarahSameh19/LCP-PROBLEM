#include <iostream>
#include <string>
#include <vector>
#include<algorithm>
using namespace std;

class DivideandConquer {
public:
    string getMinString(string a, string b) {
        if (a.length() >= b.length()) {
            return b;
        }
        return a;
    }

    string commonPrefix(string str1, string str2) {
        string result;
        string minimum = getMinString(str1, str2);

        for (int i = 0; i < minimum.length(); i++) {
            if (str1[i] != str2[i])
                break;
            result.push_back(str1[i]);
        }
        return result;
    }

    string commonPrefixDivide(string arr[], int low, int high) {
        if (low == high)
            return arr[low];

        if (high > low) {
            int mid = (low + high) / 2;

            string str1 = commonPrefixDivide(arr, low, mid);
            string str2 = commonPrefixDivide(arr, mid + 1, high);

            return commonPrefix(str1, str2);
        }
        return "";
    }
};

class BruteForce {
public:
    int findMinLength(int n, vector<string>& strs) {
        int minLen = strs[0].length();

        for (int i = 1; i < n; i++) {
            if (strs[i].length() < minLen) {
                minLen = strs[i].length();
            }
        }
        return minLen;
    }

    string longestCommonPrefix(int n, vector<string>& strs) {
        string ans = "";

        int minLen = findMinLength(n, strs);

        for (int i = 0; i < minLen; i++) {
            char ch = strs[0][i];
            for (int j = 1; j < n; j++) {
                if (ch != strs[j][i]) {
                    return ans;
                }
            }
            ans.push_back(ch);
        }
        return ans;
    }
};
class DynamicProgramming {
public:
    string longestCommonPrefixdp(string s1, string s2) {

        /*  if (s1.empty() || s2.empty()) {
              return "";
          }*/

        int m = s1.length();
        int n = s2.length();

        //initializes a 2D vector dp with (m+1) rows and (n+1) columns
       //each element is initialized to 0.
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        // Initialize the first row
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;  // Set values from 1 to n //1,2,3,4
        }

        // Initialize the first column
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i; // Set values from 1 to m //1,2,3,4
        }

        string longestPrefix = "";

        // Compute the DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = min({ dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 2 });
                }
                //stopping condition
                if (dp[i][j] < 1) {
                    longestPrefix = s1.substr(0, i);
                }
            }
        }
        return longestPrefix;
    }
};

int main() {
    cout << "Choose an approach to solve the Longest Common Prefix:\n";
    cout << "\n";
    cout << "1. Divide and conquer\n";
    cout << "2. Brute force\n";
    cout << "3. Dynamic programming\n";

    int num;
    cin >> num;

    switch (num) {
    case 1: {
        cout << "Divide and conquer\n";
        DivideandConquer solution;

        string arr[] = { "application", "app", "append", "approach" };
        int n = sizeof(arr) / sizeof(arr[0]);

        cout << "Strings entered:" << endl;
        for (int i = 0; i < n; i++) {
            cout << arr[i] << endl;
        }

        string ans = solution.commonPrefixDivide(arr, 0, n - 1);

        if (!ans.empty()) {
            cout << "\033[36m" << "The longest common prefix is:" << ans << "\033[0m" << endl;
        }
        else {
            cout << "\033[36m" << "There is no Longest Common Prefix\033[0m" << endl;
        }
        break;
    }
    case 2: {
        cout << "Brute force\n";
        BruteForce bruteForce;

        int n2;
        cout << "Enter the number of Strings: ";
        cin >> n2;
        if (n2 == 0)
        {
            cout << "\033[36m" << "No Number entered\033[0m" << endl;
        }
        else {
            cout << "Enter the Strings:" << endl;
            vector<string> strs(n2);

            for (int i = 0; i < n2; i++)
                cin >> strs[i];

            string ans = bruteForce.longestCommonPrefix(n2, strs);

            if (!ans.empty()) {
                cout << "\033[36m" << "The longest common prefix is: " << ans << "\033[0m" << endl;
            }
            else {
                cout << "\033[36m" << "There is no Longest Common Prefix\033[0m" << endl;
            }
        }
        break;
    }
    case 3: {
        cout << "Dynamic programming\n";
        DynamicProgramming dp;
        string s1 = "flow";
        string s2 = "flew";
        string longestPrefix = dp.longestCommonPrefixdp(s1, s2);
        if (!longestPrefix.empty()) {
            cout << "\033[36m" << "The longest common prefix is: " << longestPrefix << "\033[0m" << endl;
        }
        else {
            cout << "\033[36m" << "There is no common prefix\033[0m" << endl;
        }
        break;
    }
    default:
        cout << "\033[36m" << "Invalid choice\033[0m" << endl;
    }
    return 0;
}