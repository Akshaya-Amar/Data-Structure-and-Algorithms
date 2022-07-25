#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *prev;
    struct node *next;
};

struct node *createNode();
struct node *insert_at_start(struct node*);
struct node *insert_at_end(struct node*);
struct node *insert_after_pos(struct node*);
struct node *insert_before_pos(struct node*);
struct node *delete_at_first(struct node*);
struct node *delete_at_end(struct node**);
struct node *delete_at_pos(struct node*);
void display(struct node*);

struct node *tail = NULL;

int main() {
    
    struct node *head = NULL;
    int choice;

    while(1){
        system("clear");
        printf("<---------------- Doubly Linked List Operations ---------------->\n\n");
        printf("Enter a choice:\n\n");
        printf("1. Insert a new node at beginning.\n");
        printf("2. Insert a new node at the end.\n");
        printf("3. Insert a new node after specific position.\n");
        printf("4. Insert a new node before specific position.\n");
        printf("5. Delete node at the beginning.\n");
        printf("6. Delete node at the end.\n");
        printf("7. Delete node at position.\n");
        printf("10. Display the data of all nodes.\n");
        printf("11. Exit the program.\n\n");

        scanf("%d", &choice);

        switch(choice) {
            case 1:
            head = insert_at_start(head);
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
            head = insert_after_pos(head);
            display(head);
            break;

            case 4:
            head = insert_before_pos(head);
            if(head != NULL) {
                display(head);
            }
            break;

            case 5:
            head = delete_at_first(head);
            if(head != NULL) {
                display(head);
            }
            break;

            case 6:
            tail = delete_at_end(&head);
            if(head != NULL) {
                display(head);
            }
            break;

            case 7:
            head = delete_at_pos(head);
            if(head != NULL) {
                display(head);
            }
            break;

            case 10:
            display(head);
            break;

            case 11:
            system("clear");
            exit(0);

            default:
            printf("Invalid choice\n");
        }

        system("read -r -p \"\nPress Enter key to continue...\" key\n");
    }

    return 0;
}

struct node *createNode() {

    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->prev = NULL;
    printf("Enter the element\n");
    scanf("%d", &newNode->data);
    newNode->next = NULL;

    return newNode;
}

struct node *insert_at_start(struct node *head) {

    struct node *newNode = createNode();

    if(head == NULL) {
        tail = newNode;
        return newNode;
    }

    head->prev = newNode;
    newNode->next = head;

    return newNode;
}

struct node *insert_at_end(struct node *tail) {

    struct node *newNode = createNode();

    if(tail == NULL) {
        return newNode;
    }

    tail->next = newNode;
    newNode->prev = tail;

    return newNode;
}

// O(n) - linear time
struct node *insert_after_pos(struct node *head) {

    int pos;
    printf("After which position do you want to insert an element?\n");
    scanf("%d", &pos);

    if(pos < 1 || head == NULL) {
        printf("Invalid Position !!\n");
        return head;
    }

    struct node *newNode = createNode();

    struct node *temp = head;
    while(pos != 1 && temp != NULL) {
        temp = temp->next;
        --pos;
    }

    if(temp == NULL) {
        printf("Invalid Position\n");
        return head;
    }

    if (temp->next == NULL) {
        temp->next = newNode;
        newNode->prev = temp;
        tail = newNode;
        return head;
    }

    /*struct node *temp2 = temp->next;
    temp->next = newNode;
    temp2->prev = newNode;
    newNode->prev = temp;
    newNode->next = temp2;*/

    // OR without using extra temp2
    newNode->prev = temp;
    newNode->next = temp->next;
    temp->next = newNode;
    newNode->next->prev = newNode;

    return head;
}

// O(n) - linear time
struct node *insert_before_pos(struct node *head) {

    if(head == NULL) {
        printf("List is empty !!\n");
        return head;
    }

    int pos;
    printf("Before which position do you want to insert an element?\n");
    scanf("%d", &pos);

    if(pos < 1) {
        printf("Invalid position !!\n");
        return head;
    }

    if(pos == 1) {
        return insert_at_start(head);
    }

    struct node *newNode = createNode();

    struct node *temp = head;
    while(pos != 1 && temp != NULL) {
        temp = temp->next;
        --pos;
    }

    if(temp == NULL) {
        printf("Invalid position !!\n");
        return head;
    }

    /*struct node *temp2 = temp->prev;
    newNode->prev = temp2;
    newNode->next = temp;
    temp2->next = newNode;
    temp->prev = newNode;*/

    // without using extra variable temp2
    newNode->prev = temp->prev;
    newNode->next = temp;
    temp->prev->next = newNode;
    temp->prev = newNode;
    
    return head;
}

// O(1) - constant time
struct node *delete_at_first(struct node *head) {

    if(head == NULL) {
        printf("List is empty !!\n");
        return head;
    }

    // for case when there is a single node in the list
    if(head->next == NULL) {
        free(head);
        head = NULL;
        tail = NULL;

        printf("List is empty now !!\n");

        return head;
    }

    /*struct node *temp = head;
    head = head->next;
    free(temp);
    head->prev = NULL;*/

    // without using extra variable temp
    head = head->next;
    free(head->prev);
    head->prev = NULL;

    return head;
}

// O(1) - constant time
struct node *delete_at_end(struct node **head) {

    if(*head == NULL) {
        printf("List is empty !!\n");
        return *head;
    }

    if((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        tail = NULL;
        printf("List is empty now !!\n");
        return tail;
    }

    /*struct node *temp = *head;
    while(temp->next != NULL) {
        temp = temp->next;
    }

    struct node *temp2 = temp->prev;
    free(temp);
    temp2->next = NULL;

    return temp2;
    */

    // in constant time without using while loop and taking advantage of tail pointer
    /*struct node *temp = tail->prev;
    free(tail);
    temp->next = NULL;
    return temp;
    */

    // in constant time without using while loop and without using extra variable temp
    tail = tail->prev;
    free(tail->next);
    tail->next = NULL; 

    return tail;
}

// O(n) - linear time
struct node *delete_at_pos(struct node *head) {

    if(head == NULL) {
        printf("List is empty !!\n");
        return head;
    }

    int pos;
    printf("Enter the position of the element to be deleted\n");
    scanf("%d", &pos);

    if(pos == 1) {
        // for cases when there is only a single node present in the list
        if(head->next == NULL) {
            free(head);
            head = NULL;
            tail = NULL;
            printf("List is empty now !!\n");
            return head;
        }

        head = head->next;
        free(head->prev);
        head->prev = NULL;
        return head;
    }

    struct node *temp = head;
    while(pos != 1 && temp != NULL) {
        temp = temp->next;
        --pos;
    }

    // for case when the position entered is more than the number of nodes present in the list
    if(temp == NULL) {
        printf("Invalid position\n");
        return head;
    }

    // for case when the node to be deleted is the last one
    if(temp->next == NULL) {
        tail = temp->prev;
        tail->next = NULL;
        free(temp);
        return head;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp);
    return head;
}

// O(n) - linear time
void display(struct node *head) {

    if(head == NULL) {
        printf("List is empty !!\n");
        return;
    }

    struct node *temp = head;
    printf("\nAll elements in the list are:\n");
    while(temp != NULL) {
        printf("%d\t", temp->data);
        temp = temp->next;
    }   

    printf("\n");

}