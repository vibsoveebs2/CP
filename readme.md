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

```
class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
        // Initialize the left and right boundaries.
        // left = 1 and right = total sweetness / number of people.
        int numberOfPeople = k + 1;
        int left = *min_element(sweetness.begin(), sweetness.end());
        int right = accumulate(sweetness.begin(), sweetness.end(), 0) / numberOfPeople;
        
        while (left < right) { 
            // Get the middle index between left and right boundary indexes.
            // cur_sweetness stands for the total sweetness for the current person.
            // people_with_chocolate stands for the number of people that have 
            // a piece of chocolate of sweetness greater than or equal to mid.  
            int mid = (left + right + 1) / 2;
            int curSweetness = 0;
            int peopleWithChocolate = 0;
            
            // Start assigning chunks to the current people.
            for (int s : sweetness) {
                curSweetness += s;
                
                // When the total sweetness from him is no less than mid, meaning we 
                // have done with him and move on to assigning chunks to the next people.
                if (curSweetness >= mid) {
                    peopleWithChocolate += 1;
                    curSweetness = 0;
                }
            }
            
            // Check if we successfully give everyone a piece of chocolate with sweetness
            // no less than mid, and eliminate the search space by half.
            if (peopleWithChocolate >= numberOfPeople) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        
        // Once the left and right boundaries coincide, we find the target value,
        // that is, the maximum possible sweetness we can get.
        return right;
    }
    // Time complexity: O(n * log(sum(sweetness)))
    // Space complexity: O(1)
};
```

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
        int ns = s.size(); // Length of string s
        int nt = t.size(); // Length of string t

        // Ensure that s is shorter than t.
        if (ns > nt) return isOneEditDistance(t, s);

        // The strings are NOT one edit away distance
        // if the length difference is more than 1.
        if (nt - ns > 1) return false;

        for (int i = 0; i < ns; i++) {
            if (s[i] != t[i]) {
                // If strings have the same length
                if (ns == nt) return s.substr(i + 1) == t.substr(i + 1);
                // If strings have different lengths
                else return s.substr(i) == t.substr(i + 1);
            }
        }

        // If there are no differences in ns distance,
        // the strings are one edit away only if
        // t has one more character.
        return (ns + 1 == nt);
    }
};
// time O(max(ns, nt))
// space O(1)
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
        if (words.size() == 0) return ""; // If there are no words, return an empty string

        // Initialize data structures
        unordered_map<char, int> indegree; // Stores the indegree of each character
        unordered_map<char, unordered_set<char>> graph; // Represents the directed graph

        // Initialize indegree for all characters
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].size(); j++) {
                char c = words[i][j];
                indegree[c] = 0; // Set initial indegree to 0
            }
        }

        // Build the graph and record indegree
        for (int i = 0; i < words.size() - 1; i++) {
            string cur = words[i];
            string nex = words[i + 1];

            // Check if cur is a prefix of nex
            if (cur.size() > nex.size() && cur.compare(0, nex.length(), nex) == 0) {
                return ""; // Invalid order, return empty string
            }

            // Compare characters in cur and nex
            int len = min(cur.size(), nex.size());
            for (int j = 0; j < len; j++) {
                if (cur[j] != nex[j]) {
                    // Add nex[j] to the set of characters reachable from cur[j]
                    unordered_set<char> set = graph[cur[j]];
                    if (set.find(nex[j]) == set.end()) {
                        graph[cur[j]].insert(nex[j]); // Build the graph
                        indegree[nex[j]]++; // Increment indegree for nex[j]
                    }
                    break;
                }
            }
        }

        // Perform topological sort
        string ans;
        queue<char> q;
        for (auto& e : indegree) {
            if (e.second == 0) {
                q.push(e.first); // Add characters with indegree 0 to the queue
            }
        }
        while (!q.empty()) {
            char cur = q.front();
            q.pop();
            ans += cur; // Append to the result

            // Update indegree for adjacent characters
            if (graph[cur].size() != 0) {
                for (auto& e : graph[cur]) {
                    indegree[e]--;
                    if (indegree[e] == 0) {
                        q.push(e); // Add characters with updated indegree 0 to the queue
                    }
                }
            }
        }

        // Check if the result is cyclic (all characters included)
        return ans.length() == indegree.size() ? ans : "";
    }
};
// Space complexity: O(N), where N is the total number of characters in all words
// Time complexity: O(N), considering the graph construction and topological sort
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
    // Function to find the closest value to the target in the BST
    int closestValue(TreeNode* root, double target) {
        if (!root) return -1; // Base case: empty tree
        // Recursively find the closest values in the left and right subtrees
        int left = closestValue(root->left, target);
        int right = closestValue(root->right, target);
        // Determine the closest value among the children and the current node
        int childrenClosest = closerValue(left, right, target);
        return closerValue(childrenClosest, root->val, target);
    }

    // Helper function to find the closer value between two values
    int closerValue(int firstVal, int secondVal, double target) {
        if (firstVal == -1) {
            return secondVal;
        } else if (secondVal == -1) {
            return firstVal;
        }
        // Compare absolute differences and return the closer value
        if (abs(firstVal - target) < abs(secondVal - target) || secondVal == -1) {
            return firstVal;
        } else if (abs(firstVal - target) > abs(secondVal - target) || firstVal == -1) {
            return secondVal;
        } else {
            return firstVal < secondVal ? firstVal : secondVal;
        }
    }
};
// space & time O(log n)
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
    // Helper function to find the representative of a set
    int find(vector<int>& memo, int x) {
        int rep = memo[x];
        if (rep == memo[rep]) return rep;
        while (rep != memo[rep]) {
            rep = memo[rep];
        }
        int tmp;
        while (memo[x] != rep) {
            tmp = x;
            x = memo[x];
            memo[tmp] = rep;
        }
        return rep;
    }

    // Helper function to combine two sets
    int combine(vector<int>& memo, vector<int>& rank, int a, int b) {
        if (find(memo, a) == find(memo, b)) return 0;
        if (rank[memo[a]] < rank[memo[b]]) {
            rank[memo[b]] += rank[memo[a]];
            memo[memo[a]] = memo[b];
        } else {
            rank[memo[a]] += rank[memo[b]];
            memo[memo[b]] = memo[a];
        }
        return -1;
    }

    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        vector<int> memo(m * n, -1); // Initialize disjoint-set data structure
        vector<int> rank(m * n, 0); // Initialize rank for union-by-rank optimization
        vector<int> result(positions.size(), 0); // Initialize result vector

        result[0] = 1; // First position always forms a new island
        int cell = positions[0][0] * n + positions[0][1];
        memo[cell] = cell; // Mark the cell as part of an island
        rank[cell] = 1; // Set rank to 1

        for (int i = 1; i < positions.size(); i++) {
            cell = positions[i][0] * n + positions[i][1];
            if (memo[cell] != -1) {
                // If the cell is already part of an island, skip
                result[i] = result[i - 1];
                continue;
            }

            int count = 1; // Initialize count for this position
            memo[cell] = cell; // Mark the cell as part of an island
            rank[cell] = 1; // Set rank to 1

            // Check adjacent cells and combine islands if needed
            if (cell >= n && memo[cell - n] != -1) {
                count += combine(memo, rank, cell, cell - n);
            }
            if (cell < (m - 1) * n && memo[cell + n] != -1) {
                count += combine(memo, rank, cell, cell + n);
            }
            if (cell % n > 0 && memo[cell - 1] != -1) {
                count += combine(memo, rank, cell, cell - 1);
            }
            if (cell % n < n - 1 && memo[cell + 1] != -1) {
                count += combine(memo, rank, cell, cell + 1);
            }

            result[i] = result[i - 1] + count; // Update result
        }

        return result;
    }
};
//Space Complexity: O(m * n + positions.size())

//Time Complexity: O(positions.size())
```


Given the root of a binary tree, return the vertical order traversal of its nodes' values. (i.e., from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

https://leetcode.com/problems/binary-tree-vertical-order-traversal/solutions/821324/c-easy-bfs-with-map/

```
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        // Initialize the result vector
        vector<vector<int>> res;
        
        // Handle the case when the tree is empty
        if (!root) return res;
        
        // Create a map to store the nodes at each vertical level
        map<int, vector<int>> levelMap;
        
        // Create a queue for BFS traversal
        queue<pair<TreeNode*, int>> q;
        
        // Start with the root node at vertical level 0
        q.push({root, 0});
        
        while (!q.empty()) {
            int size = q.size();
            
            // Process nodes at the current level
            for (int i = 0; i < size; i++) {
                TreeNode* curr = q.front().first;
                int dir = q.front().second;
                q.pop();
                
                // Add the current node's value to the corresponding vertical level
                levelMap[dir].push_back(curr->val);
                
                // Enqueue left child with adjusted vertical level
                if (curr->left) q.push({curr->left, dir - 1});
                
                // Enqueue right child with adjusted vertical level
                if (curr->right) q.push({curr->right, dir + 1});
            }
        }
        
        // Populate the result vector from the map
        for (auto& entry : levelMap) {
            res.push_back(entry.second);
        }
        
        return res;
    }
};
//time & space o(N)
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
// Space Complexity: O(m * n) where m is the number of rows and n is the number of columns in the grid. 

// Time Complexity: O(m^2 * n^2) in the worst case, where m and n are the dimensions of the grid. The BFS traversal can visit all cells in the grid.
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
//space o(1) time o(n)
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
// time & space O(N)
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
    unordered_map<string, int> logs; // Stores timestamps and corresponding IDs

public:
    LogSystem() {
        // Constructor: Initialize the logs map
    }

    void put(int id, string timestamp) {
        logs[timestamp] = id; // Add the timestamp and ID to the logs map
    }

    vector<int> retrieve(string start, string end, string granularity) {
        int index = getIndex(granularity); // Get the index based on granularity
        string startStr = start.substr(0, index); // Extract the relevant part of the start timestamp
        string endStr = end.substr(0, index); // Extract the relevant part of the end timestamp

        vector<int> result; // Initialize the result vector
        for (auto it = logs.begin(); it != logs.end(); it++) {
            string str = it->first.substr(0, index); // Extract the relevant part of the current timestamp

            if (startStr <= str && endStr >= str) {
                // If the current timestamp falls within the specified range, add the corresponding ID to the result
                result.push_back(it->second);
            }
        }
        return result; // Return the retrieved IDs
    }

    int getIndex(string granularity) {
        int index = 0;
        if (granularity == "Year") index = 4; 
        else if (granularity == "Month") index = 7; 
        else if (granularity == "Day") index = 10; 
        else if (granularity == "Hour") index = 13; 
        else if (granularity == "Minute") index = 16;
        else index = 19;

        return index; // Return the appropriate index based on granularity
    }
};
// time: put & getIndex -> O(1) retrive -> o(n)
//space: o(n)
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
#include <set>

class MaxStack {
private:
    // Using two sets to maintain the stack and values.
    // The first element of each pair is the count (to handle duplicates).
    std::set<std::pair<int, int>> stack; // {count, value}
    std::set<std::pair<int, int>> values; // {value, count}
    int cnt; // Counter for unique elements

public:
    MaxStack() {
        cnt = 0;
    }

    // Push a value onto the stack.
    void push(int x) {
        stack.insert({cnt, x});
        values.insert({x, cnt});
        cnt++;
    }

    // Pop the top value from the stack.
    int pop() {
        std::pair<int, int> p = *stack.rbegin();
        stack.erase(p);
        values.erase({p.second, p.first});
        return p.second;
    }

    // Get the top value without removing it.
    int top() {
        return stack.rbegin()->second;
    }

    // Get the maximum value in the stack.
    int peekMax() {
        return values.rbegin()->first;
    }

    // Pop the maximum value from the stack.
    int popMax() {
        std::pair<int, int> p = *values.rbegin();
        values.erase(p);
        stack.erase({p.second, p.first});
        return p.first;
    }
};
// time O(n log n)
// space O(n)
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
        int lval = 0; // Initialize left operand value
        int rval = 0; // Initialize right operand value
        int res = 0;  // Initialize result
        char op = '+'; // Initialize operator as addition

        for (; index < s.length(); index++) {
            char c = s[index]; // Get the current character

            // If the character is a digit, update the right operand value
            if (c >= '0' && c <= '9') {
                int digit = c - '0';
                rval = rval * 10 + digit;
            } 

            // If the character is an opening parenthesis, recursively evaluate the expression inside
            if (c == '(') {
                index++;
                rval = calculate(s, index);
            }

            // When encountering an operator or closing parenthesis, perform the operation
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == ')' || index == s.length() - 1) {
                if (op == '+') {
                    res += lval;
                    lval = rval;
                } else if (op == '-') {
                    res += lval;
                    lval = -rval;
                } else if (op == '*') {
                    lval = lval * rval;
                } else {
                    lval = lval / rval;
                }
                rval = 0; // Reset right operand value
                op = c; // Update operator

                // If it's a closing parenthesis, break out of the loop
                if (c == ')') {
                    break;
                }
            }
        }
        res += lval; // Add the last left operand value to the result
        return res; // Return the final result
    }

public:
    int calculate(string s) {
        int index = 0; // Initialize index for parsing
        return calculate(s, index); // Call the helper function
    }
};

//space & time o(N)
```
Given an array of meeting time intervals intervals
where intervals [i] =
[starti, endi], return the minimum number of conference rooms required.

Example 1:

Input: intervals = [[0,30], [5,10], [15,20]]
Output: 2

Example 2:

Input: intervals = [[7,10], [2,4]]
Output: 1

Constraints:

. 1 <= intervals. length <= 104

· 0 <= starti < endi <= 106

https://leetcode.com/problems/meeting-rooms-ii/solutions/4527442/c-priority-queue-heap-clean-code/

```
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
       
        // sort according to start time
        sort(intervals.begin(), intervals.end());

        // min heap to store number of rooms occupied at any point of time
        priority_queue<int, vector<int>, greater<int>> pq;

        // max rooms occupied
        int maxRooms = 0;
       
        for(auto interval : intervals) {
            
            int start = interval[0];
            int end = interval[1];

            // free up ended meeting rooms
            while(!pq.empty() && pq.top() <= start) {
                pq.pop();
            }
            
            // use a room for current meeting
            pq.push(end);
            
            // update max everytime
            maxRooms = max(maxRooms, (int) pq.size());

        }

        // max rooms after all meetings
        return maxRooms;
    }
};
// time O(n log n)
// space O(n)
```
Certainly! Let's dive into each of your questions:

1. **Smart Pointers**:
    - **Definition**: Smart pointers are a type of C++ data structure that manage the lifetime of dynamically allocated objects. They automatically deallocate memory when it is no longer needed, preventing memory leaks.
    - **Types of Smart Pointers**:
        1. **`std::unique_ptr`**: Represents ownership of a dynamically allocated object. It ensures that only one `unique_ptr` can own the object at a time. When the `unique_ptr` goes out of scope, it automatically deletes the object.
        2. **`std::shared_ptr`**: Allows multiple `shared_ptr` instances to share ownership of the same object. It keeps track of the reference count, and when the last `shared_ptr` goes out of scope, the object is deleted.
        3. **`std::weak_ptr`**: Used in conjunction with `shared_ptr`. It provides a non-owning reference to the object. It doesn't affect the reference count, and it doesn't prevent the object from being deleted. Useful for avoiding circular references.
    - **Implementation of Smart Pointer**:
        - Here's a basic implementation of a simplified `std::unique_ptr`:
        ```cpp
        template <typename T>
        class UniquePtr {
        private:
            T* ptr;

        public:
            explicit UniquePtr(T* p) : ptr(p) {}
            ~UniquePtr() { delete ptr; }

            T* operator->() const { return ptr; }
            T& operator*() const { return *ptr; }
        };
        ```

2. **`std::map` and `std::unordered_map`**:
    - Both are associative containers in C++ that store key-value pairs.
    - **`std::map`**:
        - Implemented as a **balanced binary search tree (usually Red-Black Tree)**.
        - Keys are always sorted in ascending order.
        - Provides logarithmic time complexity for insertion, deletion, and search operations.
        - Useful when you need ordered keys.
    - **`std::unordered_map`**:
        - Implemented as a **hash table**.
        - Keys are not sorted.
        - Provides constant time complexity (average case) for insertion, deletion, and search operations.
        - Useful when you don't need ordered keys and want faster lookups.
    - Example usage:
        ```cpp
        #include <iostream>
        #include <map>
        #include <unordered_map>

        int main() {
            // std::map example
            std::map<std::string, int> myMap;
            myMap["Alice"] = 25;
            myMap["Bob"] = 30;

            // std::unordered_map example
            std::unordered_map<std::string, int> myUnorderedMap;
            myUnorderedMap["Charlie"] = 22;
            myUnorderedMap["David"] = 28;

            std::cout << "Age of Bob: " << myMap["Bob"] << std::endl;
            std::cout << "Age of David: " << myUnorderedMap["David"] << std::endl;

            return 0;
        }
        ```
