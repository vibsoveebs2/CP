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
