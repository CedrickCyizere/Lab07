#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Linked list node structure
struct node {
    char op; // Operator: 'v' for value, '*', '-', '+', '/'
    int val; // Value (if op is 'v')
    struct node *next; // Pointer to the next node
};

// Function to create a new node
struct node *create_node(char op, int val) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node) {
        new_node->op = op;
        new_node->val = val;
        new_node->next = NULL;
    }
    return new_node;
}

// Function to add a node to the end of the list (stack)
void push(struct node **head, struct node *new_node) {
    new_node->next = *head;
    *head = new_node;
}

// Function to pop the top node from the list (stack)
struct node *pop(struct node **head) {
    if (*head == NULL)
        return NULL;
    struct node *top = *head;
    *head = (*head)->next;
    return top;
}

int evaluate_postfix(const char *expression) {
    struct node *stack = NULL;

    // Parse the expression
    char *token = strtok(expression, " ");
    while (token != NULL) {
        if (isdigit(token[0])) {
            // Operand: Push onto the stack
            int val = atoi(token);
            push(&stack, create_node('v', val));
        } else {
            // Operator: Pop top two operands, perform operation, and push result
            struct node *op2 = pop(&stack);
            struct node *op1 = pop(&stack);
            int result;
            switch (token[0]) {
                case '+':
                    result = op1->val + op2->val;
                    break;
                case '-':
                    result = op1->val - op2->val;
                    break;
                case '*':
                    result = op1->val * op2->val;
                    break;
                case '/':
                    result = op1->val / op2->val;
                    break;
                default:
                    fprintf(stderr, "Invalid operator: %c\n", token[0]);
                    exit(1);
            }
            push(&stack, create_node('v', result));
            free(op1);
            free(op2);
        }
        token = strtok(NULL, " ");
    }

    // Final result
    struct node *final_result = pop(&stack);
    int result = final_result->val;
    free(final_result);

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <expression>\n", argv[0]);
        exit(1);
    }

    int result = evaluate_postfix(argv[1]);
    printf("Result: %d\n", result);

    return 0;
}
