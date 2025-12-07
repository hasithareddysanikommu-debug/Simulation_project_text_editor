#include <stdio.h>
#include <string.h>

#define MAX 100

// Stack structure to store text states
struct Stack {
    char items[MAX][MAX];
    int top;
};

// Function prototypes
void push(struct Stack *s, char text[]);
void pop(struct Stack *s, char text[]);
int isEmpty(struct Stack *s);
void displayText(char text[]);

int main() {
    struct Stack undoStack, redoStack;
    undoStack.top = redoStack.top = -1;

    char text[MAX] = "";     // Current text
    char newText[MAX];       // Temporary text
    int choice;

    while (1) {
        printf("\n=== TEXT EDITOR SIMULATION ===\n");
        printf("1. Type Text\n");
        printf("2. Undo\n");
        printf("3. Redo\n");
        printf("4. Display Text\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf(" %d", &choice);
        getchar();   // clear buffer

        switch (choice) {
            case 1:
                push(&undoStack, text); // Save current state
                printf("Enter text to add: ");
                fgets(newText, MAX, stdin);
                newText[strcspn(newText, "\n")] = '\0'; // remove newline
                strcat(text, newText);
                printf("Text added!\n");
                redoStack.top = -1; // Clear redo stack when new text added
                break;

            case 2:
                if (isEmpty(&undoStack)) {
                    printf("Nothing to undo!\n");
                } else {
                    push(&redoStack, text); // Save current state to redo
                    pop(&undoStack, text);  // Restore previous state
                    printf("Undo performed!\n");
                }
                break;

            case 3:
                if (isEmpty(&redoStack)) {
                    printf("Nothing to redo!\n");
                } else {
                    push(&undoStack, text);
                    pop(&redoStack, text);
                    printf("Redo performed!\n");
                }
                break;

            case 4:
                displayText(text);
                break;

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}

// Push text state to stack
void push(struct Stack *s, char text[]) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    s->top++;
    strcpy(s->items[s->top], text);
}

// Pop text state from stack
void pop(struct Stack *s, char text[]) {
    strcpy(text, s->items[s->top]);
    s->top--;
}

// Check if stack is empty
int isEmpty(struct Stack *s) {
    return s->top == -1;
}

// Display current text
void displayText(char text[]) {
    printf("\nCurrent Text: \"%s\"\n", text);
}
