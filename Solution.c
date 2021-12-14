#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int max(int a, int b) {
	return a > b ? a : b;
}
int min(int a, int b) {
	return a < b ? a : b;
}

#pragma region 题目提供的数据结构

struct Node {
	int val;
	struct Node* left;
	struct Node* right;
	struct Node* next;
};

struct ListNode {
	int val;
	struct ListNode* next;
};

struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

#pragma endregion

#pragma region 一般题

// 709. 转换成小写字母
char* toLowerCase(char* s) {
	for (char* c = s; *c != '\0'; c++)
		if (*c >= 'A' && *c <= 'Z') *c += 32;
	return s;
}

//6. Z 字形变换
char* convert(char* s, int numRows) {
	if (numRows == 1) return s;
	int length = strlen(s);
	if (numRows >= length) return s;
	char* cs = (char*)malloc(sizeof(char) * length + 1), * c = cs;
	for (int i = 0; i < numRows; i++) {
		for (int n = i; n < length;) {
			*cs = s[n];
			cs++;
			n += numRows + numRows - 2;
			int l;
			if (i > 0 && i < numRows - 1 && ((l = n - (i << 1)) < length)) {
				*cs = s[l];
				cs++;
			}
		}
	}
	*cs = '\0';
	return c;
}

// 75. 颜色分类
void sortColors(int* nums, int numsSize) {
	int l = 0, r = numsSize - 1;
	for (int i = 0; i <= r; i++)
	{
		if (nums[r] == 2) r--;
		if (nums[l] == 0) {
			l++;
			i = l;
		}
		if (nums[l] != 0 && nums[r] != 2) {
			if (nums[i] == 2) {
				int t = nums[r];
				nums[r] = nums[i];
				nums[i] = t;
				r--;
			}
			if (nums[i] == 0) {
				int t = nums[i];
				nums[i] = nums[l];
				nums[l] = t;
				l++;
			}
		}
	}
}

// 169. 多数元素
int majorityElement(int* nums, int numsSize) {
	int m = nums[0];
	int vc = 0;
	for (int i = 0; i < numsSize; i++)
	{
		if (nums[i] == m) vc++;
		else vc--;
		if (vc == 0) {
			m = nums[i];
			vc = 1;
		}
	}
	return m;
}

// 136. 只出现一次的数字
int singleNumber(int* nums, int numsSize) {
	int p = 0;
	for (int i = 0; i < numsSize; i++)
		p ^= nums[i];
	return p;
}

// 11. 盛最多水的容器
int maxArea(int* height, int heightSize) {
	int n1 = 0, n2 = heightSize - 1;
	int size = 0;
	while (n1 < n2)
		size = height[n1] < height[n2] ?
		max(size, (n2 - n1) * height[n1++]) :
		max(size, (n2 - n1) * height[n2--]);
	return size;
}

// 153. 寻找旋转排序数组中的最小值
int findMin(int* nums, int numsSize) {
	if (numsSize == 1) return nums[0];
	if (nums[0] < nums[numsSize - 1]) return nums[0];
	int l = 1, m, r = numsSize - 1;
	while (l <= r)
	{
		m = l + r >> 1;
		if (nums[m] < nums[m - 1]) return nums[m];
		if (nums[m] > nums[0]) l = m + 1;
		else r = m - 1;
	}
	return nums[m];
}

// 33. 搜索旋转排序数组
int searchRotate(int* nums, int numsSize, int target) {
	int l = 0, m, r = numsSize - 1;
	while (l <= r)
	{
		m = l + r >> 1;
		if (nums[m] == target) return m;
		if (nums[m] >= nums[0])
			if (nums[m] < target) l = m + 1;
			else if (target >= nums[0]) r = m - 1;
			else l = m + 1;
		else if (nums[m] > target) r = m - 1;
		else if (target >= nums[0]) r = m - 1;
		else l = m + 1;
	}
	return -1;
}

// 26. 删除有序数组中的重复项
int removeDuplicates(int* nums, int numsSize) {
	if (numsSize <= 1) return numsSize;
	int l = 0;
	for (int i = 0; i < numsSize; i++) {
		if (nums[i] != nums[l]) {
			l++;
			nums[l] = nums[i];
		}
	}
	return l + 1;
}

// 27. 移除元素
int removeElement(int* nums, int numsSize, int val) {
	int l = numsSize - 1;
	for (int i = l; i >= 0; i--) {
		if (nums[i] == val) {
			nums[i] = nums[l];
			l--;
		}
	}
	return l + 1;
}

// 35. 搜索插入位置
int searchInsert(int* nums, int numsSize, int target) {
	if (numsSize == 1) nums[0] < target ? 1 : 0;
	int left = 0, right = numsSize - 1, p, length = right;
	while (left <= right)
	{
		p = left + right >> 1;
		if (nums[p] == target)
			return p;
		else if (nums[p] > target)
		{
			if (p == 0)
				return 0;
			else if (nums[p - 1] < target)
				return p;
			right = p - 1;
		}
		else if (nums[0] < target)
		{
			if (p == length)
				return p + 1;
			else if (nums[p + 1] > target)
				return p + 1;
			left = p + 1;
		}
	}
	return -1;
}

// 53. 最大子数组和
int maxSubArray(int* nums, int numsSize) {
	int pre = 0, maxAns = nums[0];
	for (int i = 0; i < numsSize; i++) {
		pre = max(pre + nums[i], nums[i]);
		maxAns = max(maxAns, pre);
	}
	return maxAns;
}

// 70. 爬楼梯
int climbStairs(int n) {
	if (n <= 3) return n;
	int p1 = 2, p2 = 3;
	for (int i = 3; i < n; i++) {
		p2 += p1;
		p1 = p2 - p1;
	}
	return p2;
}

// 74. 搜索二维矩阵
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
	int p1 = 0, p2 = matrixColSize[0] - 1, len = matrixSize;
	while (p1 < len && p2 >= 0)
		if (matrix[p1][p2] == target) return true;
		else if (matrix[p1][p2] > target) {
			int l = 0;
			while (l <= p2)
			{
				len = l + p2 >> 1;
				if (matrix[p1][len] == target) return true;
				if (matrix[p1][len] > target) p2 = len - 1;
				else l = len + 1;
			}
			return false;
		}
		else p1++;
	return false;
}

// 167. 两数之和 II - 输入有序数组
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
	int* ns = (int*)malloc(sizeof(int) * 2);
	*returnSize = 2;
	int p1 = 0, p2 = numbersSize - 1, n;
	while (p1 < p2)
	{
		n = numbers[p1] + numbers[p2];
		if (n > target)
			p2--;
		else if (n < target)
			p1++;
		else
		{
			ns[0] = p1 + 1;
			ns[1] = p2 + 1;
			break;
		}
	}
	return ns;
}

// 189. 轮转数组
void reverse(int* nums, int start, int end) {
	while (start < end) {
		nums[start] = nums[start] ^ nums[end];
		nums[end] = nums[end] ^ nums[start];
		nums[start] = nums[start] ^ nums[end];
		start += 1;
		end -= 1;
	}
}

void rotate(int* nums, int numsSize, int k) {
	k %= numsSize;
	reverse(nums, 0, numsSize - 1);
	reverse(nums, 0, k - 1);
	reverse(nums, k, numsSize - 1);
}

// 278. 第一个错误的版本
bool isBadVersion(int version) {
	return true;
}

int firstBadVersion(int n) {
	if (n == 1) return n;
	long left = 1, right = n, p;
	while (left <= right)
	{
		p = left + right >> 1;
		if (!isBadVersion(p))
		{
			n = p;
			left = p + 1;
		}
		else
		{
			if (!isBadVersion(p - 1)) break;
			right = p - 1;
		}
	}
	return p;
}

// 283. 移动零
void moveZeroes(int* nums, int numsSize) {
	int p1 = 0, p2 = numsSize - 1;
	while (p1 < numsSize)
	{
		if (nums[p1] == 0)
		{
			p2 = p1 + 1;
			while (p2 < numsSize)
			{
				if (nums[p2] != 0)
				{
					nums[p1] = nums[p2];
					nums[p2] = 0;
					break;
				}
				p2++;
			}
			if (p2 == numsSize) return;
		}
		p1++;
	}
}

// 344. 反转字符串
void reverseString(char* s, int sSize) {
	while (s < s + sSize - 1)
	{
		*s = *s ^ *(s + sSize - 1);
		*(s + sSize - 1) = *(s + sSize - 1) ^ *s;
		*s = *s ^ *(s + sSize - 1);
		sSize -= 2;
		s++;
	}
}

// 509. 斐波那契数
int fib(int n) {
	if (n <= 1) return n;
	int p1 = 0, p2 = 1;
	for (int i = 1; i < n; i++) {
		p2 += p1;
		p1 = p2 - p1;
	}
	return p2;
}

// 557. 反转字符串中的单词 III
char* reverseWords(char* s) {
	int p1 = 0, p2, p = 0;
	int length = strlen(s);
	while (p < length)
	{
		p1 = p;
		p2 = p1 + 1;
		while (p2 < length && s[p2] != ' ')
			p2++;
		p = p2 + 1;
		p2--;
		while (p1 < p2)
		{
			s[p1] = s[p1] ^ s[p2];
			s[p2] = s[p2] ^ s[p1];
			s[p1] = s[p1] ^ s[p2];
			p1++;
			p2--;
		}
	}
	return s;
}

// 704. 二分查找
int search(int* nums, int numsSize, int target) {
	int l = 0, m, r = numsSize - 1;
	while (l <= r)
	{
		m = l + r >> 1;
		if (nums[m] == target) return m;
		else if (nums[m] > target) r = m - 1;
		else l = m + 1;
	}
	return -1;
}

// 746. 使用最小花费爬楼梯
int minCostClimbingStairs(int* cost, int costSize) {
	int p1 = 0, p2 = 0, g;
	for (int i = 2; i <= costSize; i++) {
		g = min(p1 + cost[i - 2], p2 + cost[i - 1]);
		p1 = p2;
		p2 = g;
	}
	return p2;
}

// 977. 有序数组的平方
int* sortedSquares(int* nums, int numsSize, int* returnSize) {
	int* p1 = nums, * p2 = nums + numsSize - 1;
	int* ns = (int*)malloc(sizeof(int) * numsSize) + numsSize;
	while (p1 <= p2)
	{
		ns--;
		if (abs(*p1) > abs(*p2))
		{
			*ns = *p1 * *p1;
			p1++;
		}
		else
		{
			*ns = *p2 * *p2;
			p2--;
		}
	}
	*returnSize = numsSize;
	return ns;
}

// 1137. 第 N 个泰波那契数
int tribonacci(int n) {
	if (n <= 1) return n;
	if (n == 2) return 1;
	int p1 = 0, p2 = 1, p3 = 1;
	for (int i = 2; i < n; i++) {
		p3 += p2 + p1;
		p2 = p3 - p2 - p1;
		p1 = p3 - p2 - p1;
	}
	return p3;
}

// 1816. 截断句子
char* truncateSentence(char* s, int k) {
	unsigned short i = 0;
	while (s[i] != '\0')
		if (s[i] == ' ' && k-- == 1) break;
		else i++;
	s[i] = '\0';
	return s;
}

// 1518. 换酒问题
int numWaterBottles(int numBottles, int numExchange) {
	int bottles = numBottles;
	while (numBottles >= numExchange) {
		bottles += numBottles / numExchange;
		numBottles = numBottles / numExchange + numBottles % numExchange;
	}
	return bottles;
}

#pragma endregion

#pragma region 二叉树题

// 572. 另一棵树的子树
bool isSubtreeDFS(struct TreeNode* t1, struct TreeNode* t2) {
	if (t1 == NULL && t2 == NULL) return true;
	if (t1 == NULL || t2 == NULL) return false;
	return t1->val == t2->val && isSubtreeDFS(t1->left, t2->left) && isSubtreeDFS(t1->right, t2->right);
}

bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot) {
	if (root->val == subRoot->val) if (isSubtreeDFS(root, subRoot)) return true;
	if (root->left != NULL && isSubtree(root->left, subRoot)) return true;
	if (root->right != NULL && isSubtree(root->right, subRoot)) return true;
	return false;
}

// 94. 二叉树的中序遍历
void inorderTraversalDFS(struct TreeNode* root, int* nums, int* p) {
	if (!root) return;
	inorderTraversalDFS(root->left, nums, p);
	nums[(*p)++] = root->val;
	inorderTraversalDFS(root->right, nums, p);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
	int* nums = malloc(sizeof(int) * 100);
	*returnSize = 0;
	inorderTraversalDFS(root, nums, returnSize);
	return nums;
}

// 101. 对称二叉树
bool isSymmetricDFS(struct TreeNode* t1, struct TreeNode* t2) {
	if (t1 == NULL && t2 == NULL) return true;
	if (t1 == NULL || t2 == NULL) return false;
	return t1->val == t2->val && isSymmetricDFS(t1->left, t2->right) && isSymmetricDFS(t1->right, t2->left);
}

bool isSymmetric(struct TreeNode* root) {
	if (root == NULL) return true;
	return isSymmetricDFS(root, root);
}

// 100. 相同的树
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
	if (p == NULL && q == NULL) return true;
	if (p == NULL || q == NULL) return false;
	if (p->val != q->val) return false;
	return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

// 617. 合并二叉树
void mergeTreesDFS(struct TreeNode* p1, struct TreeNode* p2)
{
	p1->val += p2->val;
	if (p2->left != NULL)
		if (p1->left == NULL)
			p1->left = p2->left;
		else mergeTreesDFS(p1->left, p2->left);
	if (p2->right != NULL)
		if (p1->right == NULL)
			p1->right = p2->right;
		else mergeTreesDFS(p1->right, p2->right);
}

struct TreeNode* mergeTrees(struct TreeNode* root1, struct TreeNode* root2) {
	if (root1 == NULL) return root2;
	if (root2 == NULL) return root1;
	mergeTreesDFS(root1, root2);
	return root1;
}

#pragma endregion

#pragma region 链表题

int getListNodeLength(struct ListNode* head) {
	int c = 0;
	while (head != NULL && c++ == c)
		head = head->next;
	return c;
}

// 82. 删除排序链表中的重复元素 II
struct ListNode* deleteDuplicates(struct ListNode* head) {
	struct ListNode* p1 = head, * p2 = head;
	while (p1 != NULL && p1->next != NULL && p1->val == p1->next->val) {
		p2 = p1->next->next;
		while (p2 != NULL && p1->val == p2->val)
			p2 = p2->next;
		head = (p1 = p2);
	}
	if (head == NULL) return head;
	p2 = p1->next;
	while (p2 != NULL && p2->next != NULL)
		if (p2->val == p2->next->val) {
			int val = p2->val;
			p2 = p2->next->next;
			while (p2 != NULL && p2->val == val)
				p2 = p2->next;
			p1->next = p2;
		}
		else {
			p1 = p2;
			p2 = p2->next;
		}
	return head;
}

// 206. 反转链表
struct ListNode* reverseList(struct ListNode* head) {
	struct ListNode* p1 = head, * p2 = p1;
	while (p2 != NULL && p2->next != NULL)
	{
		p1 = p2->next;
		p2->next = p2->next->next;
		p1->next = head;
		head = p1;
	}
	return head;
}

// 234. 回文链表
bool isPalindrome(struct ListNode* head) {
	if (head->next == NULL) return true;
	struct ListNode* p1 = head, * p2 = head;
	int i = 0;
	while (p2 != NULL && p2->next != NULL)
	{
		p1 = p1->next;
		p2 = p2->next->next;
		i++;
	}
	if (p2 != NULL) p1 = p1->next;
	p2 = head;
	p1 = reverseList(p1);
	while (i > 0)
	{
		if (p1->val != p2->val) break;
		p1 = p1->next;
		p2 = p2->next;
		i--;
	}
	return i == 0;
}

// 328. 奇偶链表
struct ListNode* oddEvenList(struct ListNode* head) {
	if (head == NULL) return head;
	struct ListNode* p1 = head, * p2 = head->next, * p3 = p2;
	while (p3 != NULL && p3->next != NULL)
	{
		p1->next = p3->next;
		p1 = p1->next;
		p3->next = p1->next;
		p3 = p3->next;
	}
	p1->next = p2;
	return head;
}

// 203. 移除链表元素
struct ListNode* removeElements(struct ListNode* head, int val) {
	if (head == NULL) return head;
	while (head != NULL && head->val == val)
		head = head->next;
	struct ListNode* p = head;
	while (p != NULL && p->next != NULL)
	{
		if (p->next->val == val)
			p->next = p->next->next;
		else
			p = p->next;
	}
	return head;
}

// 160. 相交链表
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
	if (headA == NULL || headB == NULL) return NULL;
	struct ListNode* p1 = headA, * p2 = headB;
	while (p1 != p2)
	{
		p1 = p1 == NULL ? headB : p1->next;
		p2 = p2 == NULL ? headA : p2->next;
	}
	return p1;
}

// 142. 环形链表 II
struct ListNode* detectCycle(struct ListNode* head) {
	struct ListNode* p1 = head, * p2 = head;
	while (p1 != NULL && p1->next != NULL)
	{
		p1 = p1->next->next;
		p2 = p2->next;
		if (p1 == p2) goto CON;
	}
	return NULL;
CON:
	p1 = head;
	while (p1 != p2)
	{
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1;
}

// 142. 环形链表
bool hasCycle(struct ListNode* head) {
	struct ListNode* p1 = head, * p2 = head;
	while (p1 != NULL && p1->next != NULL)
	{
		p1 = p1->next->next;
		p2 = p2->next;
		if (p1 == p2) return true;
	}
	return false;
}

// 24. 两两交换链表中的节点
struct ListNode* swapPairs(struct ListNode* head) {
	struct ListNode* p = head;
	while (p != NULL && p->next != NULL)
	{
		if (p->next != NULL)
		{
			p->val = p->val ^ p->next->val;
			p->next->val = p->next->val ^ p->val;
			p->val = p->val ^ p->next->val;
			p = p->next->next;
		}
		else break;
	}
	return head;
}

// 237. 删除链表中的节点
void deleteNode(struct ListNode* node) {
	*node = *(node->next);
}

// 21. 合并两个有序链表
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
	if (l1 == NULL) return l2;
	if (l2 == NULL) return l1;
	struct ListNode* p1 = l1, * p2 = l2;
	while (l2 != NULL)
	{
		if (p1->val > p2->val)
		{
			p2 = p2->next;
			l2->next = p1;
			p1 = l2;
			l1 = p1;
			l2 = p2;
		}
		else if (p1->val == p2->val)
		{
			p2 = p2->next;
			l2->next = p1->next;
			p1->next = l2;
			p1 = p1->next;
			l2 = p2;
		}
		else
		{
			if (p1->next == NULL)
			{
				p1->next = p2;
				return l1;
			}
			else if (p1->next->val > p2->val)
			{
				p2 = p2->next;
				l2->next = p1->next;
				p1->next = l2;
				p1 = p1->next;
				l2 = p2;
			}
			else p1 = p1->next;
		}
	}
	return l1;
}

// 23. 合并K个升序链表
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
	if (listsSize == 0) return NULL;
	for (int i = listsSize - 1; i > 0; i--)
		lists[0] = mergeTwoLists(lists[0], lists[i]);
	return lists[0];
}

// 19. 删除链表的倒数第 N 个结点
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
	struct ListNode* l1 = head, * l2 = head;
	int i = 0;
	while (l1->next != NULL)
	{
		l1 = l1->next;
		if (i >= n)
			l2 = l2->next;
		i++;
	}
	if (i < n)
		head = head->next;
	else if (n == 1)
		l2->next = NULL;
	else
		l2->next = l2->next->next;
	return head;
}

// 876. 链表的中间结点
struct ListNode* middleNode(struct ListNode* head) {
	int length = getListNodeLength(head);
	length = length >> 1;
	for (int i = 0; i < length; i++)
		head = head->next;
	return head;
}

#pragma endregion