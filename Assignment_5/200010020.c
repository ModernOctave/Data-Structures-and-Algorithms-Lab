/**************************************************
ASSIGNMENT 5
HASHING

ISHIKA SHARMA
200010020

REFERENCES:-
--->>geeksforgeeks
--->>Abdul Bari - Udemy
**************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *fw;

struct Node {
    char data[99];
    struct Node *next;
};

struct Node *CreateNode(char data[]) {
    struct Node *temp = malloc(sizeof(struct Node));
    int j = 0;
    for (int i = 0; data[i] != '\0'; i++) {
        (temp->data)[i] = data[i];
        j++;
    }
    (temp->data)[j] = '\0';
    temp->next = NULL;
    return temp;
}

// hash function
int hashFunction(char s[], int m) {
    int key = 0;
    for (int i = 0; s[i] != '\0'; i++)
        key = key + (int)s[i];        //typecasting
    key = key%m;
    return key;
}

// insertion function
void insertion(char s[], struct Node *hash_table[], int m) {
    struct Node *head = CreateNode(s);
    int key = 0;
    key = hashFunction(s, m);
    if (hash_table[key] == NULL)
        hash_table[key] = head;
    else {
        head->next = hash_table[key];
        hash_table[key] = head;
    }
}


void cmp(char s[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            char c;
            if (s[i] > s[j]) {
                c = s[i];
                s[i] = s[j];
                s[j] = c;
            }
        }
    }
}

// display function
void display(char s[], struct Node *hash_table[], int key) {
    if (hash_table[key] == NULL)
        return;
    else {
        int l = strlen(s);   // length

        struct Node *temp = hash_table[key];
        int k = 0;

        while (temp != NULL) {
            int l1 = strlen(temp->data);
            if (l == l1) {
                char s1[25], s2[25];
                strcpy(s1, s);
                strcpy(s2, temp->data);
                cmp(s1, l);
                cmp(s2, l1);
                if (strcmp(s1, s2) == 0) {
                    if (k == 0) {
                        fprintf(fw, "%s", temp->data);
                        k++;
                    } else {
                        fprintf(fw, " %s", temp->data);
                    }
                }
            }
            temp = temp->next;
        }
    }
    return;
}


int main(int argc, char const* argv[]) {
    FILE *fp1;
    FILE *fp2;

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[3], "r");

    fw = fopen("anagrams.txt", "w+");
    int m = atoi(argv[2]);
    struct Node *hash_table[m];

    for (int k = 0; k < m; k++)
        hash_table[k] = NULL;

    char s[25];
    char word[25];

    while (fscanf(fp1, "%s", s) != EOF)
        insertion(s, hash_table, m);

    int line = 0;
    int r = 0;

    while (fscanf(fp2, "%s", word) != EOF)
        line++;
    rewind(fp2);

    while (fscanf(fp2, "%s", word) != EOF) {
        r++;
        int key = hashFunction(word, m);
        display(word, hash_table, key);
        if (r != line)
            fprintf(fw, "\n");
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fw);

    return 0;
}
