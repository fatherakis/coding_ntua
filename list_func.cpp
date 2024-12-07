#include <stdio.h>
#include <iostream>
using namespace std;

/*
    List implementation with functions and nodes
*/

struct node
{
    int info;
    struct node *next;
};
typedef struct node NODE;

void insertAtPosition(NODE **, int, int);
void traverse(NODE **);

int main()
{

    NODE *start = NULL;

    insertAtPosition(&start, 7, 1);
    insertAtPosition(&start, 4, 1);
    insertAtPosition(&start, 4, 2);
    insertAtPosition(&start, 2, 3);
    insertAtPosition(&start, 1, 4);
    traverse(&start);
    return 0;
}

void insertAtPosition(NODE **start, int info, int POS /*position*/)
{
    NODE *ptr = (NODE *)malloc(sizeof(NODE));
    NODE *temp;
    ptr->info = info;
    int k;
    if (POS < 1)
    {
        printf("\nPosition can't be less than one..");
        free(ptr);
    }
    else if (POS == 1)
    {
        ptr->next = *start;
        *start = ptr;
    }
    else if (*start != NULL)
    { /* list has no node and N is greater than 1 */
        for (k = 2, temp = *start; k < POS; k++)
        {
            temp = temp->next;
            if (temp == NULL)
            {
                printf("\nInvalid position\n");
                return;
            }
        }
        ptr->next = temp->next;
        temp->next = ptr;
    }
    else
    {
        printf("\nList has no node and postition is greater than 1");
        free(ptr);
    }
}

void traverse(NODE **start)
{
    NODE *temp;
    temp = *start;
    while (temp != NULL)
    {
        printf("%d  ", temp->info);
        temp = temp->next;
    }
}
