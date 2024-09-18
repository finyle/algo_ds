/*
 * innovative business： n个元素，每对元素间的大小关系确定，关系不具有传递性，将n个元素拍成一行，使得每个元素都小于它右边的相邻元素
 * 元素的大小关系是n个点与 n(n-1)/2条有向边构成任意的有向图
 * 交互式题目：这些关系不能一次性得知，必须通过不超过10000次提问，每次提问只能了解某两个元素之间的关系，把这n个元素排成一行，使得每个元素都小于右边与它相邻的元素
 */

// Forward declaration of specialSort API.
// bool specialSort(int a, int b);
// return bool means whether a is less than b.


#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include<iomanip>
#include <cmath>
#include<fstream>
using namespace std;


class Solution {
public:
    vector<int> specialSort(int N) { // sort函数，完成排序
        vector<int> a;
        for(int i=0;i<N;i++){
            a.push_back(i+1);
        }
        for (int i=1;i<N;i++){
            int temp = a[i];
            int left = 0;
            int right = i - 1;
            int mid = 0;
            while (left <= right) { // 二分完成排序
                mid = (left + right) / 2;
                if (compare(temp,a[mid])) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            for (int j = i - 1; j >= left; j--) {
                a[j + 1] = a[j];
            }
            if (left != i) {
                a[left] = temp;
            }
        }
        return a;
    }
};

class PrepareForSolution {
public:

    void trimLeftTrailingSpaces(string &input) {
        input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
            return !isspace(ch);
        }));
    }

    void trimRightTrailingSpaces(string &input) {
        input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
            return !isspace(ch);
        }).base(), input.end());
    }

    void trim(string &input) {
        trimLeftTrailingSpaces(input);
        trimRightTrailingSpaces(input);
    }


    int stringToInteger(string input) {
        trim(input);
        return stoi(input);
    }
    vector<int> stringToIntegerArray(string input) {
        vector<int> output;
        trim(input);
        input = input.substr(1, input.length() - 2);
        trim(input);
        stringstream ss(input);
        string item;
        char delim = ',';
        while (getline(ss, item, delim)) {
            output.push_back(stringToInteger(item));
        }
        return output;
    }

    vector<vector <int>> stringTo2dIntegerArray(string input) {
        vector<vector<int>> output;
        trim(input);
        input = input.substr(1, input.length() - 2);
        trim(input);
        size_t i = 0;
        while (i < input.size()) {
            size_t j = i;
            while (j < input.size() && input[j] != ']') j++;
            j++;
            output.push_back(stringToIntegerArray(input.substr(i, j - i)));
            while (j < input.size() && input[j] != ',') j++;
            i = j + 1;
        }
        return output;
    }

};

int main() {
    auto prepare = PrepareForSolution();
    string line;
    getline(cin, line);
    auto nums = prepare.stringTo2dIntegerArray(line);
    int N = nums.size();
    ifstream fin("user_output");
    string user_ret;
    getline(fin, user_ret);
    vector<int> ans = prepare.stringToIntegerArray(user_ret);
    vector<int> ans2 = prepare.stringToIntegerArray(user_ret);
    sort(ans2.begin(), ans2.end());
    if (ans2.size() != N)
        return 1;
    for (int i = 0; i < N; i++)
        if (ans2[i] != i + 1)
            return 1;
    for (int i = 0; i < N - 1; i++)
        if (!nums[ans[i] - 1][ans[i + 1] - 1])
            return 1;
    return 0;
}


/*
 * input:
[[0, 1, 0], [0, 0, 0], [1, 1, 0]]
 * output:
[3, 1, 2]
 */