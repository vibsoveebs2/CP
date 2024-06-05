You have one chocolate bar that consists of some chunks. Each chunk has its own sweetness given by the array

You want to share the chocolate with your k friends so you start cutting the chocolate bar into k + 1
piece consists of some consecutive chunks.

Being generous, you will eat the piece with the minimum total sweetness and give the other pieces to your friends.

Find the maximum total sweetness of the piece you can get by cutting the chocolate bar optimally.

sweetness

pieces using k cuts, each

Example 1:

Input: sweetness = [1,2,3,4,5,6,7,8,9], k = 5
Output: 6
Explanation: You can divide the chocolate to [1,2,3], [4,5], [6], [7], [8], [9]

Example 2:

Input: sweetness = [5,6,7,8,9,1,2,3,4], k = 8
Output: 1
Explanation: There is only one way to cut the bar into 9 pieces.

Example 3:

Input: sweetness = [1,2,2,1,2,2,1,2,2], k = 2
Output: 5
Explanation: You can divide the chocolate to [1,2,2], [1,2,2], [1,2,2]

Constraints:

0 <= k < sweetness. length <= 104

1 <= sweetness [i] <= 105

.
https://leetcode.com/problems/divide-chocolate/editorial/

Given two strings

S

and

t

return

true

S

to get

S

t

to get

t

· Replace exactly one character of

if they are both one edit distance apart, otherwise return false

s is said to be one distance apart from a string t if you can:
A string

. Insert exactly one character into

. Delete exactly one character from

s with a different character to get

t

Example 1:

Input: s = "ab", t = "acb"
Output: true
Explanation: We can insert 'c' into s to get t.

Example 2:

Input: s = "", t = ""
Output: false
Explanation: We cannot get t from s by only one step.

Constraints:

. 0 <= s.length, t. length <= 104

. s and t consist of lowercase letters, uppercase le
ase letters, and digits.

https://leetcode.com/problems/one-edit-distance/editorial/

```
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int ns = s.size();
        int nt = t.size();

        // Ensure that s is shorter than t.
        if (ns > nt) return isOneEditDistance(t, s);

        // The strings are NOT one edit away distance
        // if the length diff is more than 1.
        if (nt - ns > 1) return false;

        for (int i = 0; i < ns; i++)
            if (s[i] != t[i])
                // if strings have the same length
                if (ns == nt) return s.substr(i + 1) == t.substr(i + 1);
                // If strings have different lengths
                else
                    return s.substr(i) == t.substr(i + 1);

        // If there are no diffs in ns distance
        // The strings are one edit away only if
        // t has one more character.
        return (ns + 1 == nt);
    }
};
```
There is a new alien language that uses the English alphabet. However, the order of the letters is unknown to you.

You are given a list of strings words from the alien language's dictionary. Now it is claimed that the strings in words are sorted lexicographically by the
rules of this new language.

If this claim is incorrect, and the given arrangement of string in words cannot correspond to any order of letters, return

Otherwise, return a string of the unique letters in the new alien language sorted in lexicographically increasing order by the new language's rules. If there are
multiple solutions, return any of them.

Example 1:

Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"

Example 2:

Input: words = ["z","x"]
Output: "zx"

Example 3:

Input: words = ["Z","x","z"]
Output: ""
Explanation: The order is invalid, so return

Constraints:

.

.

1 <= words.length <= 100

1 <= words[i].length <= 100

words [i] consists of only lowercase English letters.

https://leetcode.com/problems/alien-dictionary/solutions/157298/c-java-bfs-and-topoligical-sort-with-explanation/
```
class Solution {
public:
    string alienOrder(vector<string>& words) {
        if (words.size() == 0) return "";
        unordered_map<char, int> indegree;
        unordered_map<char, unordered_set<char>> graph;
        
        // initialize
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].size(); j++) {
                char c = words[i][j];
                indegree[c] = 0; 
            }
        }
        
        // build graph and record indegree
        for (int i = 0; i < words.size() - 1; i++) {
            string cur = words[i];
            string nex = words[i + 1];
            if (cur.size() > nex.size() && cur.compare(0, nex.length(), nex) == 0) {
                return "";
            }
            int len = min(cur.size(), nex.size());
            for (int j = 0; j < len; j++) {
                if (cur[j] != nex[j]) {
                    unordered_set<char> set = graph[cur[j]];
                    if (set.find(nex[j]) == set.end()) {
                        graph[cur[j]].insert(nex[j]); // build graph
                        indegree[nex[j]]++; // add indegree
                    }
                    break;                        
                }
            }
        }
        
        // topoligical sort
        string ans;
        queue<char> q;
        for (auto& e : indegree) {
            if (e.second == 0) {
                q.push(e.first);
            }
        }
        while(!q.empty()) {
            char cur = q.front();
            q.pop();
            ans += cur;
            
            if (graph[cur].size() != 0) {
                for (auto& e : graph[cur]) {
                    indegree[e]--;
                    if (indegree[e] == 0) {
                        q.push(e);
                    }
                }
            }            
        }
        
        // tell if it is cyclic
        return ans.length() == indegree.size() ? ans : "";
    }
};
```
Given the root of a binary search tree and a target value, return the value in the BST that is closest to the target. If there are multiple answers, print the
smallest.
Input: root = [4,2,5,1,3], target = 3.714286
Output: 4

Example 2:

Input: root = [1], target = 4.428571
Output: 1

Constraints:

. The number of nodes in the tree is in the range [1, 104]

0 <= Node.val <= 109

-109 <= target <= 109

.
https://leetcode.com/problems/closest-binary-search-tree-value/solutions/3978526/c-easy-approach/

```
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        if (!root) return -1;
        int left = closestValue(root->left, target);
        int right = closestValue(root->right, target);
        int childrenClosest = closerValue(left, right, target);
        return closerValue(childrenClosest, root->val, target);
    }

    int closerValue(int firstVal, int secondVal, double target) {
        if (firstVal == -1) {
            return secondVal;
        } else if (secondVal == -1) {
            return firstVal;
        }

        if (abs(firstVal - target) < abs(secondVal - target) || secondVal == -1) {
            return firstVal;
        } else if (abs(firstVal - target) > abs(secondVal - target) || firstVal == -1) {
            return secondVal;
        } else {
            return firstVal < secondVal ? firstVal : secondVal;
        }
    }

};
```
