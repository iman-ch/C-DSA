/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_queue_stack.h"
#include "expression_symbol.h"
#include "hash.h"


QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr) {
    QUEUE queue = {0};
    STACK stack = {0};
    char *p = infixstr;
    int sign = 1;
    int num = 0;
    char symbol[11] = {0};

    while (*p) {
        if (*p == '-' && (p == infixstr || *(p - 1) == '(')) {
            sign = -1;
        } else if (*p >= '0' && *p <= '9') {
            num = *p - '0';
            while (*(p + 1) >= '0' && *(p + 1) <= '9') {
                num = num * 10 + *(p + 1) - '0';
                p++;
            }
            enqueue(&queue, new_node(sign * num, 0));
            sign = 1;
        } else if (*p == '(') {
            push(&stack, new_node('(', 2));
        } else if (*p == ')') {
            while (stack.top) {
                if (stack.top->type == 2) {
                    free(pop(&stack));
                    break;
                }
                enqueue(&queue, pop(&stack));
            }
        } else if (*p == '/' || *p == '*' || *p == '%' || *p == '+' || *p == '-') {
            while (stack.top && stack.top->type == 1 && get_priority(stack.top->data) >= get_priority(*p)) {
                enqueue(&queue, pop(&stack));
            }
            push(&stack, new_node(*p, 1));
        } else if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
            char *sp = symbol;
            *sp = *p;
            while ((*(p + 1) >= 'a' && *(p + 1) <= 'z') || (*(p + 1) >= 'A' && *(p + 1) <= 'Z') ||
                   (*(p + 1) >= '0' && *(p + 1) <= '9')) {
                p++;
                sp++;
                *sp = *p;
            }
            *(sp + 1) = '\0';

            HASHNODE *hn = hashtable_search(ht, symbol);
            if (hn) {
                enqueue(&queue, new_node(hn->value, 0));
            } else {
                printf("Symbol '%s' not found in hashtable.\n", symbol);
                return queue;
            }
        }
        p++;
    }

    while (stack.top) {
        enqueue(&queue, pop(&stack));
    }

    return queue;
}

int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr) {
    QUEUE queue = infix_to_postfix_symbol(ht, infixstr);
    int result = evaluate_postfix(queue);
    clean_queue(&queue);
    return result;
}

int evaluate_postfix(QUEUE queue) {
    STACK stack = {0};

    NODE *p = queue.front;

    while (p) {
        if (p->type == 0) {
            push(&stack, new_node(p->data, 0));
        } else if (p->type == 1) { // If it's an operator
            int result = 0;
            NODE *operand2 = pop(&stack); // Pop the second operand
            NODE *operand1 = pop(&stack); // Pop the first operand

            // Perform the operation based on the operator
            switch (p->data) {
                case '+': result = operand1->data + operand2->data; break;
                case '-': result = operand1->data - operand2->data; break;
                case '*': result = operand1->data * operand2->data; break;
                case '/': result = operand1->data / operand2->data; break;
            }

            // Push the result back onto the stack
            push(&stack, new_node(result, 0));

            // Free the nodes for the operands
            free(operand1);
            free(operand2);
        }
        p = p->next;
    }

    // The final result should be at the top of the stack
    int result = stack.top->data;
    clean_stack(&stack); // Don't forget to clean up the stack
    return result;
}

HASHDATA evaluate_statement(HASHTABLE *ht, char *statement) {
    HASHDATA hd = {0};
    char line[80] = {0};
    strcpy(line, statement);
    char *p = line, *dp = line;
    while (*p) {
        if (*            p != ' ') {
            *dp = *p;
            dp++;
        }
        p++;
    }
    *dp = '\0';

    char name[20] = {0};
    char *eqp = strstr(line, "=");
    if (eqp) {
        *eqp = '\0';
        strcpy(name, line);
        if ((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')) {
            int value = evaluate_infix_symbol(ht, eqp + 1);
            hashtable_insert(ht, name, value);
            strcpy(hd.key, name);
            hd.value = value;
        }
    } else {
        strcpy(name, line);
        if ((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')) {
            HASHNODE *hnp = hashtable_search(ht, name);
            if (hnp) {
                strcpy(hd.key, name);
                hd.value = hnp->value;
            }
        }
    }

    return hd;
}