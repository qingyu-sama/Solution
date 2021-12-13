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

#pragma endregion

#pragma region 链表题

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

#pragma endregion