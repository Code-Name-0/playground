#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

void newTailNode(struct ListNode **head, struct ListNode **last, int value)
{
    struct ListNode *new = malloc(sizeof(struct ListNode));
    new->next = NULL;
    new->val = value;

    if (*head == NULL)
    {
        *head = new;
        *last = new;
    }
    else
    {
        (*last)->next = new;
        *last = new;
    }
}

void printList(struct ListNode *head)
{
    struct ListNode *c = head;

    while (c)
    {
        printf("%d", c->val);
        c = c->next;
        if (c)
        {
            printf("%s ", "->");
        }
    }
    printf("\n");
}

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{

    struct ListNode *resultHead = NULL;
    struct ListNode *current = resultHead;

    int sum;

    int carry = 0;

    while (l1 || l2)
    {

        // Sum Logic

        sum = (carry + (l1 != NULL ? l1->val : 0) + (l2 != NULL ? l2->val : 0)) % 10;
        carry = (carry + (l1 != NULL ? l1->val : 0) + (l2 != NULL ? l2->val : 0)) / 10;

        // Add a node logic
        newTailNode(&resultHead, &current, sum);

        // Advance l1 and l2 logic
        l1 = l1 != NULL ? l1->next : NULL;
        l2 = l2 != NULL ? l2->next : NULL;
    }

    if (carry)
    {
        newTailNode(&resultHead, &current, carry);
    }
    printList(resultHead);
    return resultHead;
}

int main()
{
    struct ListNode *l1, *l2, *l1c, *l2c;
    l1 = malloc(sizeof(struct ListNode));
    l2 = malloc(sizeof(struct ListNode));

    l1c = l1;
    l2c = l2;

    l1c->val = 9;
    l2c->val = 9;

    l1c->next = malloc(sizeof(struct ListNode));
    l2c->next = malloc(sizeof(struct ListNode));

    l1c = l1c->next;
    l2c = l2c->next;

    l1c->val = 9;
    l2c->val = 9;

    l1c->next = malloc(sizeof(struct ListNode));
    l2c->next = malloc(sizeof(struct ListNode));

    l1c = l1c->next;
    l2c = l2c->next;

    l1c->val = 9;
    l2c->val = 9;

    l1c->next = NULL;
    l2c->next = NULL;

    printList(l1);
    printList(l2);

    addTwoNumbers(l1, l2);

    return 0;
}