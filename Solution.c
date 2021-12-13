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

#pragma region һ����

// 709. ת����Сд��ĸ
char* toLowerCase(char* s) {
	for (char* c = s; *c != '\0'; c++)
		if (*c >= 'A' && *c <= 'Z') *c += 32;
	return s;
}

//6. Z ���α任
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

#pragma region ��������

// 572. ��һ����������
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

// 94. ���������������
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

// 101. �Գƶ�����
bool isSymmetricDFS(struct TreeNode* t1, struct TreeNode* t2) {
	if (t1 == NULL && t2 == NULL) return true;
	if (t1 == NULL || t2 == NULL) return false;
	return t1->val == t2->val && isSymmetricDFS(t1->left, t2->right) && isSymmetricDFS(t1->right, t2->left);
}

bool isSymmetric(struct TreeNode* root) {
	if (root == NULL) return true;
	return isSymmetricDFS(root, root);
}

#pragma endregion

#pragma region ������

// 82. ɾ�����������е��ظ�Ԫ�� II
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

// 206. ��ת����
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

// 234. ��������
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

// 328. ��ż����
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

// 203. �Ƴ�����Ԫ��
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

// 160. �ཻ����
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

// 142. �������� II
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

// 142. ��������
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

// 24. �������������еĽڵ�
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

// 237. ɾ�������еĽڵ�
void deleteNode(struct ListNode* node) {
	*node = *(node->next);
}

// 21. �ϲ�������������
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

// 23. �ϲ�K����������
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
	if (listsSize == 0) return NULL;
	for (int i = listsSize - 1; i > 0; i--)
		lists[0] = mergeTwoLists(lists[0], lists[i]);
	return lists[0];
}

// 19. ɾ������ĵ����� N �����
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

// 876. ������м���
struct ListNode* middleNode(struct ListNode* head) {
	int length = getListNodeLength(head);
	length = length >> 1;
	for (int i = 0; i < length; i++)
		head = head->next;
	return head;
}

#pragma endregion