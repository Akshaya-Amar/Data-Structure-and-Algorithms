#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *link;
};

struct node *create_node();
struct node *insert_at_beg(struct node*);
struct node *insert_at_end(struct node*);
struct node *insert_at_pos(struct node*, int);
struct node *del_at_beg(struct node*);
struct node *del_at_end(struct node**);
struct node *del_at_pos(struct node*, int);
struct node *del_list(struct node*);
struct node *reverse(struct node*);
void display(struct node*);
void count(struct node*);

// tail pointer to keep track of the last node ,so as to insert nodes at the end in constant time
struct node *tail = NULL; 

int main() {

    struct node *head = NULL;
    int choice, pos;

    while(1) {

        // for linux users
        system("clear");
        
        // For windows users
        // system("cls");

        printf("<---------------- Singly Linked List Operations ---------------->\n\n");
        printf("Enter a choice:\n\n");
        printf("1. Insert a new node at beginning.\n");
        printf("2. Insert a new node at the end.\n");
        printf("3. Insert a new node at specific position.\n");
        printf("4. Delete a node at beginning.\n");
        printf("5. Delete a node at end.\n");
        printf("6. Delete a node at specific position.\n");
        printf("7. Delete the whole list.\n");
        printf("8. Reverse a List.\n");
        printf("9. Display the data of all nodes.\n");
        printf("10. Count number of nodes in the list.\n");
        printf("11. Exit program.\n\n");

        scanf("%d", &choice);

        switch(choice) {
            case 1:
            head = insert_at_beg(head);
            if(tail == NULL) {
                tail = head;
            }
            display(head);
            break;

            case 2:
            tail = insert_at_end(tail);
            if(head == NULL) {
                head = tail;
            }
            display(head);
            break;

            case 3:
            printf("Enter the position to insert new element.\n");
            scanf("%d", &pos);
            head = insert_at_pos(head, pos);
            if(tail == NULL) {
                tail = head;
            }
            display(head);
            break;

            case 4: 
            head = del_at_beg(head);  
            if(head != NULL) {
                display(head);
            }
            break;

            case 5:
            tail = del_at_end(&head);
            if(head != NULL) {
                display(head);
            }
            break;

            case 6:
            printf("Enter the position to delete element.\n");
            scanf("%d", &pos);
            head = del_at_pos(head, pos);
            if(head == NULL) {
                tail = NULL;
            } else {
                display(head);
            }
            break;

            case 7:
            head = del_list(head);
            break;

            case 8:
            head = reverse(head);
            display(head);
            break;

            case 9:
            display(head);
            break;

            case 10:
            count(head);
            break;

            case 11:
            system("clear");
            exit(0);

            default:
            printf("Not a valid choice.\n");
        }

        // for linux users
        system("read -r -p \"\nPress any key to continue...\" key\n");

        // For windows users
        // system("pause");
    }

    return 0;
}

// O(1) - constant time
struct node *create_node() {
    
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    printf("Enter the element\n");
    scanf("%d", &newNode->data);
    newNode->link = NULL;

    return newNode;
}

// O(1) - constant time
struct node *insert_at_beg(struct node *head) {

    struct node *temp = create_node();

    temp->link = head;
    return temp;
}

// O(1) - constant time
struct node *insert_at_end(struct node *tail) {

    struct node *temp = create_node();

    // condition for case when the list is empty or there is no node in the list
    if(tail == NULL) {
        return temp;
    }

    tail->link = temp;
    return temp;
}

// O(n) - linear time
struct node *insert_at_pos(struct node *head, int pos) {

    if(pos < 1) {
        printf("Not a valid position !!\n");
        return head;
    }

    if(pos == 1) {
        return insert_at_beg(head);
    }

    struct node *temp = create_node();
    struct node *ptr = head;
    
    while(pos != 2 && ptr != NULL) {
        ptr = ptr->link;
        --pos;
    }

    if(ptr == NULL) {
        printf("Not a valid position !!\n");
        return head;
    }

    // to store the address of the new node, added at last position, in tail pointer
    if(ptr->link == NULL) {
        tail = temp;
    }

    temp->link = ptr->link;
    ptr->link = temp;

    return head;
}

// O(1) - constant time
struct node *del_at_beg(struct node *head) {

    if(head == NULL) {
        printf("List is empty !!\n");
        return head;
    }

    struct node *temp = head;
    head = head->link;
    free(temp);

    if(head == NULL) {
        printf("List is empty now !!\n");
        tail = NULL;
    }

    return head;
}

// O(n) - linear time
struct node *del_at_end(struct node **head) {

    if(*head == NULL) {
        printf("List is empty !!\n");
        return *head;
    }

    // condition for case when there is only a single node in the list
    if((*head)->link == NULL) {
        free(*head);
        *head = NULL;
        tail = NULL;
        printf("List is empty now !!\n");
        return tail;
    }

    struct node *temp = *head;
    while(temp->link->link != NULL) {
        temp = temp->link;
    }

    free(tail);
    temp->link = NULL;
    
    return temp;
}

// O(n) - linear time
struct node *del_at_pos(struct node *head, int pos) {

    if(head == NULL) {
        printf("List is empty !!\n");
        return head;
    }

    if(pos < 1) {
        printf("Invalid position !!\n");
        return head;
    }

    struct node *temp = head;
    if(pos == 1) {
        return del_at_beg(head);
    }

    while(pos != 2 && temp->link != NULL) {
        temp = temp->link;
        --pos;
    }

    if(temp->link == NULL) {
        printf("Not a valid position !!\n");
        return head;
    }

    struct node *ptr = temp->link->link;
    free(temp->link);
    temp->link = ptr;

    // to store the address of second last node, if it was the last node which was deleted, in tail pointer
    if(temp->link == NULL) {
        tail = temp;
    }

    return head;
}

// O(n) - linear time
struct node *del_list(struct node *head) {
    
    if(head == NULL) {
        printf("List is empty !!\n");
        return head;
    }

    struct node *temp = head;
    while(head != NULL) {
        head = head->link;
        free(temp);
        temp = head;
    }

    tail = NULL;

    printf("List is empty now !!\n");
    return head;
}

// O(n) - linear time
struct node *reverse(struct node *head) {

    if(head == NULL || head->link == NULL) {
        return head;
    }

    struct node *prev = NULL;
    struct node *next = NULL;

    tail = head;

    while(head != NULL) {
        next = head->link;
        head->link = prev;
        prev = head;
        head = next;
    }

    head = prev;

    return head;
}

// O(n) - linear time
void display(struct node *head) {

    if(head == NULL) {
        printf("\nList is empty !!\n");
        return;
    }
    
    printf("\nAll elements in the list are:\n");
    struct node *ptr = head;
    while(ptr != NULL) {
        printf("%d\t", ptr->data);
        ptr = ptr->link;
    }

    printf("\n");
}

// O(n) - linear growth
void count(struct node *head) {

    if(head == NULL) {
        printf("\nList is empty !!\n");
        return;
    }

    int count = 0;
    struct node *ptr = head;
    while(ptr != NULL) {
        ptr = ptr->link;
        ++count;
    }

    if(count == 1) {
        printf("\nThere is only 1 node in the list.\n");
    } else {
        printf("\nThere are %d nodes in the list.\n", count);
    }

    // one liner
    // printf(count == 1 ? "\nThere is only 1 node in the list.\n" : "\nThere are %d nodes in the list.\n", count);
}