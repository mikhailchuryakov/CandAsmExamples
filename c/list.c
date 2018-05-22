#include <stdio.h>
#include <stdlib.h>

typedef struct List List;
struct List
{
    int item;
    List *next;
    List *previous;
};

List *list_add(List *head, int item)
{
    List *new_item = (List *) malloc(sizeof(List));
    new_item->item = item;
    new_item->next = head;
    new_item->previous = NULL;
    if (head)
    {
        head->previous = new_item;
    }
    return new_item;
}

List *list_append(List *head, int item)
{
    List *new_item = (List *) malloc(sizeof(List));
    new_item->item = item;
    new_item->next = NULL;
    if (head)
    {
        List *list;
        for (list = head; list->next; list = list->next);
        list->next = new_item;
        new_item->previous = list;
    }
    else
    {
        head = new_item;
        new_item->previous = NULL;
    }
    return head;
}

List *list_insert(List *head, unsigned index, int item)
{
    unsigned i;
    List *new_item = (List *) malloc(sizeof(List));
    List *list = head;
    new_item->item = item;
    if (head)
    {
        if (index == 0)
        {
            new_item->next = head;
            new_item->previous = NULL;
            head->previous = new_item;
            head = new_item;
            return head;
        }
        for (i = 0; i < index - 1; i++)
        {
            if (!list->next)
            {
                free(new_item);
                return head;
            }
            list = list->next;
        }
        if (list->next)
            list->next->previous = new_item;
        new_item->next = list->next;
        new_item->previous = list;
        list->next = new_item;
    }
    else
    {
        if (!index) // Так как !head, то добавить мы можем только нулевой элемент
        {

            new_item->previous = NULL;
            new_item->next = NULL;
            head = new_item;
        }
        else
            free(new_item);
    }
    return head;
}

List *list_delete(List *head, unsigned index)
{
    List *list = head;
    List *old_item;
    unsigned i;
    if (!head)
        return head;
    if (index == 0)
    {
        head = head->next;
        if (head)
            head->previous = NULL;
        free(list);
        return head;
    }
    for (i = 0; i < index - 1; i++)
    {
        if (!list->next)
            return head;
        list = list->next;
    }
    old_item = list->next;
    if (old_item)
    {
        if (old_item->next)
            old_item->next->previous = list;
        list->next = old_item->next;
        free(old_item);
    }
    return head;
}

List *list_delete_first(List *head)
{
    List *list = head;
    if (head)
    {
        head = head->next;
        if (head)
            head->previous = NULL;
        free(list);
    }
    return head;
}

List *list_delete_last(List *head)
{
    List *list = head;
    List *old_item;
    if (head)
    {
        if (list->next)
        {
            for ( ; list->next->next; list = list->next);
            old_item = list->next;
            list->next = NULL;
        }
        else
        {
            old_item = list;
            head = NULL;
        }
        free(old_item);
    }
    return head;
}

int list_get(List *head, unsigned index)
{
    unsigned i;
    for (i = 0; head; head = head->next, i++)
        if (i == index)
            return head->item;
    return -1;
}

void list_set(List *head, unsigned index, int item)
{
    unsigned i;
    for (i = 0; head; head = head->next, i++)
        if (i == index)
        {
            head->item = item;
            return;
        }
}

int list_find(List *head, int item)
{
    unsigned i;
    for (i = 0; head; head = head->next, i++)
        if (item == head->item)
        {
            return i;
        }
    return -1;
}

unsigned list_size(List *head)
{
    if (!head)
        return 0;
    else
        return list_size(head->next) + 1;
}

void list_print(List *head)
{
    for ( ; head; head = head->next)
        printf("%d ", head->item);
    printf("\n");
}

void list_reverse_print(List *head)
{
    if (head)
        for ( ; head->next; head = head->next);
    for ( ; head; head = head->previous)
        printf("%d ", head->item);
    printf("\n");
}

void list_destroy(List *head)
{
    if (head)
    {
        list_destroy(head->next);
        free(head);
    }
}

int main(void)
{
    int choice, index, value;
    List *list = NULL;
    do
    {
        printf("MENU:\n"
               "0. Exit\n"
               "1. Add item\n"
               "2. Del first item\n"
               "3. Get item\n"
               "4. Set item\n"
               "5. Append item\n"
               "6. Insert item\n"
               "7. Del last item\n"
               "8. Del item\n"
               "Enter your choice: "
              );
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter value: ");
            scanf("%d", &value);
            list = list_add(list, value);
            break;
        case 5:
            printf("Enter value: ");
            scanf("%d", &value);
            list = list_append(list, value);
            break;
        case 6:
            printf("Enter list index: ");
            scanf("%d", &index);
            printf("Enter value: ");
            scanf("%d", &value);
            list = list_insert(list, index, value);
            break;
        case 2:
            list = list_delete_first(list);
            break;
        case 7:
            list = list_delete_last(list);
            break;
        case 8:
            printf("Enter list index: ");
            scanf("%d", &index);
            list = list_delete(list, index);
            break;
        case 3:
            printf("Enter list index: ");
            scanf("%d", &index);
            printf("%d item = %d\n", index, list_get(list, index));
            break;
        case 4:
            printf("Enter list index: ");
            scanf("%d", &index);
            printf("Enter value: ");
            scanf("%d", &value);
            list_set(list, index, value);
            break;
        }
        printf("\n%u items:\n", list_size(list));
        list_print(list);
        printf("\n");
        list_reverse_print(list);
        printf("\n");
    }
    while (choice);
    list_destroy(list);
    return 0;
}
