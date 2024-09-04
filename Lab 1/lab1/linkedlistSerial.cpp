#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 65535 // 2^16 - 1

// Node structure for the linked list
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Function prototypes
int Member(Node* head, int value);
Node* Insert(Node* head, int value);
Node* Delete(Node* head, int value);
void PrintList(Node* head);
int isUnique(Node* head, int value);
int getRandomUnique(Node* head);
void freeList(Node* head);

int main() {
    int n, m;
    float mMember, mInsert, mDelete;
    Node* head = NULL;

    // Seed random generator with current time
    srand(time(NULL));

    // Input n, m, mMember, mInsert, and mDelete
    printf("Enter number of initial unique random values (n): ");
    scanf("%d", &n);

    printf("Enter number of random operations (m): ");
    scanf("%d", &m);

    printf("Enter fraction for Member operations (mMember): ");
    scanf("%f", &mMember);

    printf("Enter fraction for Insert operations (mInsert): ");
    scanf("%f", &mInsert);

    printf("Enter fraction for Delete operations (mDelete): ");
    scanf("%f", &mDelete);

    // Ensure that mMember + mInsert + mDelete = 1
    if (mMember + mInsert + mDelete != 1.0) {
        printf("Error: mMember + mInsert + mDelete must equal 1.0\n");
        return -1;
    }

    // Populate the linked list with 'n' unique random values
    for (int i = 0; i < n; i++) {
        int new_value = getRandomUnique(head);
        head = Insert(head, new_value);
    }

    // Perform 'm' random operations (Member, Insert, Delete)
    for (int i = 0; i < m; i++) {
        float operationType = (float)rand() / RAND_MAX; // Random float between 0 and 1
        int random_value = rand() % (MAX_VALUE + 1); // Random value between 0 and 65535

        if (operationType < mMember) {
            // Perform Member operation
            printf("Member(%d): %s\n", random_value, Member(head, random_value) ? "true" : "false");
        } else if (operationType < mMember + mInsert) {
            // Perform Insert operation
            if (!Member(head, random_value)) {
                printf("Insert(%d)\n", random_value);
                head = Insert(head, random_value);
            }
        } else {
            // Perform Delete operation
            printf("Delete(%d)\n", random_value);
            head = Delete(head, random_value);
        }
    }

    // Free the linked list memory
    freeList(head);

    return 0;
}

// Check if a value is in the list (Member operation)
int Member(Node* head, int value) {
    Node* current = head;
    while (current != NULL) {
        if (current->value == value) {
            return 1; // Found
        }
        current = current->next;
    }
    return 0; // Not found
}

// Insert a value into the list (Insert operation)
Node* Insert(Node* head, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = head;
    return new_node;
}

// Delete a value from the list (Delete operation)
Node* Delete(Node* head, int value) {
    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->value == value) {
            if (prev == NULL) {
                // Deleting the head
                Node* temp = head;
                head = head->next;
                free(temp);
            } else {
                prev->next = current->next;
                free(current);
            }
            return head;
        }
        prev = current;
        current = current->next;
    }

    return head; // Value not found, return unchanged list
}

// Check if a value is unique in the list
int isUnique(Node* head, int value) {
    return !Member(head, value);
}

// Get a unique random value for insertion
int getRandomUnique(Node* head) {
    int random_value;
    do {
        random_value = rand() % (MAX_VALUE + 1);
    } while (!isUnique(head, random_value));
    return random_value;
}

// Free all nodes in the linked list
void freeList(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
