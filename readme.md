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

You are given an empty 2D binary grid grid of size m x n. The grid represents a map where 0's represent water and 1's represent land. Initially, all the
cells of grid are water cells (i.e., all the cells are 0's).

We may perform an add land operation which turns the water at position into a land. You are given an array positions
the position

Return an array of integers answer where answer[i]

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all
surrounded by water.

where positions [i] = [ri, Ci])

is

operation.

(ri, Ci) at which we should operate the ith

is the number of islands after turning the cell (ri, Ci) into a land.

https://leetcode.com/problems/number-of-islands-ii/solutions/3315075/solution/

```
class Solution {
public:
    int find(vector<int>& memo, int x){
        int rep = memo[x];
        if(rep == memo[rep]) return rep;
        while(rep != memo[rep]){
            rep = memo[rep];
        }
        int tmp;
        while(memo[x] != rep){
            tmp = x;
            x = memo[x];
            memo[tmp] = rep;
        }
        return rep;
    }
    int combine(vector<int>& memo, vector<int>& rank, int a, int b){
        if(find(memo, a) == find(memo, b)) return 0;
        if(rank[memo[a]] < rank[memo[b]]){
            rank[memo[b]] += rank[memo[a]];
            memo[memo[a]] = memo[b];
        }
        else{
            rank[memo[a]] += rank[memo[b]];
            memo[memo[b]] = memo[a];
        }
        return -1;
    }
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        vector<int> memo(m * n, -1);
        vector<int> rank(m * n, 0);
        vector<int> result(positions.size(), 0);
        result[0] = 1;
        int cell = positions[0][0] * n + positions[0][1];
        memo[cell] = cell;
        rank[cell] = 1;
        for(int i = 1; i < positions.size(); i++){
            cell = positions[i][0] * n + positions[i][1];
            if(memo[cell] != -1){
                result[i] = result[i - 1];
                continue;
            }
            int count = 1;
            memo[cell] = cell;
            rank[cell] = 1;
            if(cell >= n && memo[cell - n] != -1){
                count += combine(memo, rank, cell, cell - n);
            }
            if(cell < (m - 1) * n && memo[cell + n] != -1){
                count += combine(memo, rank, cell, cell + n);
            }
            if(cell % n > 0 && memo[cell - 1] != -1){
                count += combine(memo, rank, cell, cell - 1);
            }
            if(cell % n < n - 1 && memo[cell + 1] != -1){
                count += combine(memo, rank, cell, cell + 1);
            }
            result[i] = result[i - 1] + count;
        }
        return result;
    }
};
```


Given the root of a binary tree, return the vertical order traversal of its nodes' values. (i.e., from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

https://leetcode.com/problems/binary-tree-vertical-order-traversal/solutions/821324/c-easy-bfs-with-map/

```
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int>> res;
        
        if(!root) return res;
        
        map<int, vector<int>> map;
        
        queue<pair<TreeNode* , int>> q;
        
        q.push({root, 0});
        
        while(!q.empty()) {
            int size = q.size();
            
            for(int i = 0; i < size; i++) {
                TreeNode* curr = q.front().first;
                int dir = q.front().second;
                q.pop();
                map[dir].push_back(curr->val);
                if(curr->left) q.push({curr->left, dir - 1});
                if(curr->right) q.push({curr->right, dir + 1});
            }
        }
        
        for(auto i : map) {
            res.push_back(i.second);
        }
        return res;
    }
};
```

You are given an

. each 0 marks an empty land that you can pass by freely,

1 marks a building that you cannot pass through, and
. each

· each 2)
marks an obstacle that you cannot pass through.

You want to build a house on an empty land that reaches all buildings in the shortest total travel distance. You can only move up, down, left, and right.

Return the shortest travel distance for such a house. If it is not possible to build such a house according to the above rules, return

The total travel distance is the sum of the distances between the houses of the friends and the meeting point.

The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x -p1.x| + |p2.y - p1.y|.

m x n grid grid of values 0, 1, or 2, where:

-1

https://leetcode.com/problems/shortest-distance-from-all-buildings/editorial/

```
class Solution {
private:
    int bfs(vector<vector<int>>& grid, int row, int col, int totalHouses) {
        // Next four directions.
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        int rows = grid.size();
        int cols = grid[0].size();
        int distanceSum = 0;
        int housesReached = 0;

        // Queue to do a bfs, starting from (r,c) cell
        queue<pair<int, int>> q;
        q.push({ row, col });

        // Keep track of visited cells
        vector<vector<bool>> vis(rows, vector<bool> (cols, false));
        vis[row][col] = true;

        int steps = 0;

        while (!q.empty() && housesReached != totalHouses) {
            for (int i = q.size(); i > 0; --i) {
                auto curr = q.front();
                q.pop();

                row = curr.first;
                col = curr.second;

                // If this cell is a house, then add the distance from the source to this cell
                // and we go past from this cell.
                if (grid[row][col] == 1) {
                    distanceSum += steps;
                    housesReached++;
                    continue;
                }

                // This cell was an empty cell, hence traverse the next cells which is not a blockage.
                for (auto& dir : dirs) {
                    int nextRow = row + dir[0];
                    int nextCol = col + dir[1];

                    if (nextRow >= 0 && nextCol >= 0 && nextRow < rows && nextCol < cols) {
                        if (!vis[nextRow][nextCol] && grid[nextRow][nextCol] != 2) {
                            vis[nextRow][nextCol] = true;
                            q.push({nextRow, nextCol});
                        }
                    }
                }
            }
            
            // After traversing one level cells, increment the steps by 1 to reach to next level.
            steps++;
        }

        // If we did not reach all houses, then any cell visited also cannot reach all houses.
        // Set all cells visted to 2 so we do not check them again and return INT_MAX.
        if (housesReached != totalHouses) {
            for (row = 0; row < rows; row++) {
                for (col = 0; col < cols; col++) {
                    if (grid[row][col] == 0 && vis[row][col]) {
                        grid[row][col] = 2;
                    }
                }
            }
            return INT_MAX;
        }
        // If we have reached all houses then return the total distance calculated.
        return distanceSum;
    }

public:
    int shortestDistance(vector<vector<int>>& grid) {
        int minDistance = INT_MAX;
        int rows = grid.size();
        int cols = grid[0].size();
        int totalHouses = 0;

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (grid[row][col] == 1) { 
                    totalHouses++;
                }
            }
        }

        // Find the min distance sum for each empty cell.
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (grid[row][col] == 0) {
                    minDistance = min(minDistance, bfs(grid, row, col, totalHouses));
                }
            }
        }

        // If it is impossible to reach all houses from any empty cell, then return -1.
        if (minDistance == INT_MAX) {
            return -1;
        }
        return minDistance;
    }
};
```

'?'

Given a string expression representing arbitrarily nested ternary expressions, evaluate the expression, and return the result of it.

You can always assume that the given expression is valid and only contains digits,
numbers in the expression are one-digit numbers (i.e., in the range [0, 9]).

The conditional expressions group right-to-left (as usual in most languages), and the result of the expression will always evaluate to either a digit,
'F'

ידי

and

'F'

where

IT'

is true and

'F'

is false. All the

'T'

or

Example 1:

Input: expression = "T?2:3"
Output: "2"
Explanation: If true, then result is 2; otherwise result is 3.

Example 2:

Input: expression = "F?1:T?4:5"
Output: "4"
Explanation: The conditional expressions group right-to-left. Using parenthesis, it is read/evaluated as:
"(F ? 1 : (T ? 4 : 5) )" -- > "(F ? 1 : 4)" -- > "4"
or "(F ? 1 : (T ? 4 : 5) )" -- > "(T ? 4 : 5)" -- > "4"

Example 3:

Input: expression = "T?T?F:5:3"
Output: "F"
Explanation: The conditional expressions group right-to-left. Using parenthesis, it is read/evaluated as:
"(T ? (T ? F : 5) : 3)" -- > "(T ? F : 3)" -- > "F"
"(T ? (T ? F : 5) : 3)" -- > "(T ? F : 5)" -- > "F"

https://leetcode.com/problems/ternary-expression-parser/editorial/

```
class Solution {
public:
    string parseTernary(string expression) {
        
        // Checks if the string s is a valid atomic expression
        auto isValidAtomic = [](string s) {
            return (s[0] == 'T' || s[0] == 'F') && s[1] == '?' && ((s[2] >= '0' && s[2] <= '9') || s[2] == 'T' || s[2] == 'F') && s[3] == ':' && ((s[4] >= '0' && s[4] <= '9') || s[4] == 'T' || s[4] == 'F'); 
        };
        
        // Returns the value of the atomic expression
        auto solveAtomic = [](string s) {
            return s[0] == 'T' ? s[2] : s[4];
        };
        
        // Reduce expression until we are left with a single character
        while (expression.size() != 1) {
            int j = expression.size() - 1;
            while (!isValidAtomic(expression.substr(j-4, 5))) {
                j--;
            }
            expression = expression.substr(0, j-4) + solveAtomic(expression.substr(j-4, 5)) + expression.substr(j+1);
        }
        
        // Return the final character
        return expression;
    }
};
```

return the minimal possible abbreviations for every word.

"a4f". Then, a sequence of operations would

["ab3f",'ab3f"]

Given an array of distinct strings words

The following are the rules for a string abbreviation:

1. The initial abbreviation for each word is: the first character, then the number of characters in between, followed by the last character.

2. If more than one word shares the same abbreviation, then perform the following operation:
. Increase the prefix (characters in the first part) of each of their abbreviations by 1.
. For example, say you start with the words ["abcdef", "abndef"] both initially abbreviated as
be ["a4f","a4f"] ->

· This operation is repeated until every abbreviation is unique.

3. At the end, if an abbreviation did not make a word shorter, then keep it as the original word.

->

["abc2f","abn2f"]

Example 1:

Input: words = ["like", "god","internal", "me","internet", "interval","intension","face","intrusion"]
Output: ["12e", "god", "internal", "me", "i6t", "interval","inte4n","f2e","intr4n"]

Example 2:

Input: words = ["aa", "aaa"]
Output: ["aa"."aaa"1

https://leetcode.com/problems/word-abbreviation/solutions/821765/c-72ms-beats-100-memory-beats-95-hash-table-no-sorting/

```
class Solution {
public:
    vector<string> wordsAbbreviation(vector<string>& dict) {
        int n = dict.size();
        vector<string> ans(n);
        unordered_map<string, vector<int>> abbrevs;

        // Go through all words in dict
		// Update ans and also record it's abbreviation and index mapping
        for (int i = 0; i < n; i++) {
            string abbrev = abbreviate(dict[i]);
            abbrevs[abbrev].emplace_back(i);
            ans[i] = abbrev;
        }
		
		// Check duplicate abbreviations
        for (auto& words: abbrevs) {
		    // Skip words without duplicates
            if (words.second.size() < 2) continue;

            // Handle the collisions
            auto& indices = words.second;
            int len = indices.size();
			// Use a DP vector to avoid re-calculation of LCP between 2 words
            vector<int> dp(len, 0);
            for (int i = 0; i < len; i++) {
                string& cur_str = dict[indices[i]];
                for (int j = i + 1; j < len; j++) {
                    int sim = LCP(cur_str, dict[indices[j]]);
                    if (sim > dp[i]) dp[i] = sim;
                    if (sim > dp[j]) dp[j] = sim;
                }
                if (dp[i] >= cur_str.length() - 3) {
                    ans[indices[i]] = cur_str;
                } else {
                    string left = cur_str.substr(dp[i]);
                    ans[indices[i]] = cur_str.substr(0, dp[i]) + abbreviate(left);
                }
            }
        }
        return ans;
    }
private:
    // Abbreviate a word
	// For example: "internal" => "i6l"; "cow" => "cow"
    inline string abbreviate(string& str) {
        if (str.length() <= 3) return str;
        return str[0] + to_string(str.length() - 2) + str.back();
    }
	
	// Check longest common prefix, and return LCP length
	// For example: ("internal", interval") => return 5
    inline int LCP(string& s1, string& s2) {
        if (s1.length() != s2.length()) return 0;
        int i = 0;
        for (; i < s1.length(); i++) {
            if (s1[i] != s2[i]) return i;
        }
        return i;
    }
};
```

LogSystem class:

.

.

in your storage system.

.

You are given several logs, where each log contains a unique ID and timestamp. Timestamp is a string that has the following format:
Year:Month: Day:Hour:Minute: Second, for example, 2017:01:01:23:59:59. All domains are zero-padded decimal numbers.

Implement the

LogSystem() Initializes the LogSystem object.

void put(int id, string timestamp) Stores the given log (id, timestamp)

int [] retrieve(string start, string end, string granularity) Returns the IDs of the logs whose timestamps are within the range from start
to end inclusive. start and end all have the same format as timestamp, and granularity means how precise the range should be (i.e. to the exact
Day, Minute, etc.). For example, start="2017:01:01:23:59:59", end = "2017:01:02:23:59:59", and granularity = "Day" means that we need
to find the logs within the inclusive range from Jan. 1st 2017 to Jan. 2nd 2017, and the Hour, Minute, and Second for each log entry can be ignored.

Example 1:

Input
["LogSystem", "put", "put", "put", "retrieve", "retrieve"]
[[], [1, "2017:01:01:23:59:59"], [2, "2017:01:01:22:59:59"], [3, "2016:01:01:00:00:00"], ["2016:01:01:01:01:01",
"2017:01:01:23:00:00", "Year"], ["2016:01:01:01:01:01", "2017:01:01:23:00:00", "Hour"]]
Output
[null, null, null, null, [3, 2, 1], [2, 1]]

Explanation
LogSystem logSystem = new LogSystem();
logSystem.put(1, "2017:01:01:23:59:59");
logSystem.put(2, "2017:01:01:22:59:59");
logSystem.put(3, "2016:01:01:00:00:00");

// return [3,2,1], because you need to return all logs between 2016 and 2017.
logSystem. retrieve("2016:01:01:01:01:01", "2017:01:01:23:00:00", "Year");

// return [2,1], because you need to return all logs between Jan. 1, 2016 01:XX:XX and Jan. 1, 2017 23:XX:XX.
// Log 3 is not returned because Jan. 1, 2016 00:00:00 comes before the start of the range.
logSystem. retrieve("2016:01:01:01:01:01", "2017:01:01:23:00:00", "Hour");

https://leetcode.com/problems/design-log-storage-system/solutions/3416482/solution/

```
class LogSystem {
private:
    unordered_map<string, int> logs;
public:
    LogSystem() {
    }
    void put(int id, string timestamp) {
        logs[timestamp] = id;
    }
    vector<int> retrieve(string start, string end, string granularity) {
        int index = getIndex(granularity);
        string startStr = start.substr(0, index);
        string endStr = end.substr(0, index);

        vector<int> result;
        for(auto it = logs.begin(); it!=logs.end();it++) {
            string str = it->first.substr(0, index);

            if (startStr <= str && endStr>=str) {
                result.push_back(it->second);
            }
        }
        return result;
    }
    int getIndex(string granularity) {
        int index = 0;
        if (granularity == "Year") index = 4; 
        else if (granularity == "Month") index = 7; 
        else if (granularity == "Day") index = 10; 
        else if (granularity == "Hour") index = 13; 
        else if (granularity == "Minute") index = 16;
        else index = 19;

        return index;
    }
};
```

void push(int x)

.

int top()

Design a max stack data structure that supports the stack operations and supports finding the stack's maximum element.

Implement the MaxStack class:

MaxStack() Initializes the stack object.

Pushes element x onto the stack.

int pop() Removes the element on top of the stack and returns it.

Gets the element on the top of the stack without removing it.

Retrieves the maximum element in the stack without removing it.
int peekMax()

int popMax() Retrieves the maximum element in the stack and removes it. If there is more than one maximum element, only remove the top-most
one.

You must come up with a solution that supports 0(1)

for each top call and 0( logn) for each other call.

Example 1:

Input
["MaxStack", "push", "push", "push", "top", "popMax", "top", "peekMax", "pop", "top"]
[ [], [5], [1], [5], [], [], [], [], [], []]
Output
[null, null, null, null, 5, 5, 1, 5, 1, 5]

Explanation
MaxStack stk = new MaxStack();
// [5] the top of the stack and the maximum number is 5.
// [5, 1] the top of the stack is 1, but the maximum is 5.
// [5, 1, 5] the top of the stack is 5, which is also the maximum, because it is the top most

// return 5, [5, 1, 5] the stack did not change.
// return 5, [5, 1] the stack is changed now, and the top is different from the max.
// return 1, [5, 1] the stack did not change.
stk.peekMax(); // return 5, [5, 1] the stack did not change.
stk.pop();
stk.top();

stk.push(5);
stk.push(1);
stk.push(5);
one
stk.top();
stk. popMax ();
stk.top();

// return 1, [5] the top of the stack and the max element is now 5.
// return 5, [5] the stack did not change.

https://leetcode.com/problems/max-stack/editorial/

```
class MaxStack {
private:
    set<pair<int, int>> stack;
    set<pair<int, int>> values;
    int cnt;

public:
    MaxStack() { cnt = 0; }

    void push(int x) {
        stack.insert({cnt, x});
        values.insert({x, cnt});
        cnt++;
    }

    int pop() {
        pair<int, int> p = *stack.rbegin();
        stack.erase(p);
        values.erase({p.second, p.first});
        return p.second;
    }

    int top() { return stack.rbegin()->second; }

    int peekMax() { return values.rbegin()->first; }

    int popMax() {
        pair<int, int> p = *values.rbegin();
        values.erase(p);
        stack.erase({p.second, p.first});
        return p.first;
    }
};
```

Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers,
should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1]

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

+

operators, and open

and closing parentheses

') '. The integer division

Example 1:

Input: s = "1+1"
Output: 2

Example 2:

Input: s = "6-4/2"
Output: 4

Example 3:

Input: s="2*(5+5*2)/3+(6/2+8)"
Output: 21

Constraints:

1 <= S <= 104

consists of digits,
s

S

.

'*'

'(', and ') '.

is a valid expression.

https://leetcode.com/problems/basic-calculator-iii/editorial/

```
class Solution {
private:
    int calculate(const string & s, int & index) {
        int lval = 0;
        int rval = 0;
        int res = 0;
        char op = '+';
        for (; index < s.length(); index++) {
            char c = s[index];
            if (c >= '0' && c <= '9') {
                int digit = c - '0';
                rval = rval*10 + digit;
            } 
            if (c == '(') {
                index++;
                rval = calculate(s, index);
            }
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == ')' || index == s.length()-1) {
                if (op == '+') {
                    res += lval;
                    lval = rval;
                } else if (op == '-') {
                    res += lval;
                    lval = -rval;
                } else if (op == '*'){
                    lval = lval * rval;
                } else {
                    lval = lval / rval;
                }
                rval = 0;
                op = c;
                if (c == ')') {
                    break;
                }
            }
        }
        res += lval;
        return res;
    }
public:
    int calculate(string s) {
        int index = 0;
        return calculate(s,index);
    }
};
```


