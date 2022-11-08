#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    char *code;
    int weight;
    struct Node *lchild;
    struct Node *rchild;
} Node;

int cmp(const void *a, const void *b) {
    Node *aa = (Node *) a, *bb = (Node *) b;
    // printf("a->weight = %d, b->weight = %d\n", aa->weight, bb->weight);
    if (aa->weight > bb->weight) {
        return 1; //要换
    } else {
        return -1;
    }
}

void merge(Node **a, int start, int end, int start1, int end1) {
    int i, j, count = 0;
    Node **temp = (Node **) malloc(sizeof(Node *) * (end1 - start + 1));
    for (i = start, j = start1; i <= end && j <= end1;) {
        if (cmp(a[i], a[j]) == -1) {
            temp[count++] = a[i++];
        } else {
            temp[count++] = a[j++];
        }
    }
    if (i > end) {
        while (j <= end1)
            temp[count++] = a[j++];
    }
    if (j > end) {
        while (i <= end)
            temp[count++] = a[i++];
    }
    for (i = 0, j = start; i < count; i++, j++)
        a[j] = temp[i];
}

void sort(Node **node, int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        sort(node, start, mid);
        sort(node, mid + 1, end);
        merge(node, start, mid, mid + 1, end);
    }
}

Node *build(int *code) {
    Node **node = (Node **) calloc(108, sizeof(Node *));
    for (int i = 0; i < 54; i++) {
        Node *n = (Node *) malloc(sizeof(Node));
        n->lchild = n->rchild = NULL;
        if (i < 26) {
            n->data = 'a' + i;
        } else if (i < 52) {
            n->data = 'A' + i;
        } else if (i == 52) {
            n->data = ' ';
        } else {
            n->data = '.';
        }

        n->code = (char *) malloc(100);
        n->weight = code[i];
        node[i] = n;
    }
    int start = 0,  count = 54;
    while (count) {
        sort(node, start, start + count - 1);
        if (count == 1) {
            return node[start];
        } else {
            while(node[start]->weight==0){
                start++;
                count--;
            }
            Node *n1 = node[start++];
            while(node[start]->weight==0){
                start++;
                count--;
            }
            Node *n2 = node[start++];
            Node *new = (Node *) malloc(sizeof(Node));
            new->lchild = n1;
            new->rchild = n2;
            new->weight = n1->weight + n2->weight;
            new->data = '\0';
            new->code = (char *) malloc(100);
            count--;
            node[start + count - 1] = new;
        }
    }
    return NULL;
}

void setCode(Node *root) {
    int start = 0, end = 0;
    Node *stack[1000];
    stack[end++] = root;
    while (start < end) {
        int start1 = start, end1 = end;
        for (int i = start1; i < end1; i++) {
            if (stack[i]->lchild) {
                strcpy(stack[i]->lchild->code, stack[i]->code);
                strcat(stack[i]->lchild->code, "0");
                stack[end++] = stack[i]->lchild;
            }
            if (stack[i]->rchild) {
                strcpy(stack[i]->rchild->code, stack[i]->code);
                strcat(stack[i]->rchild->code, "1");
                stack[end++] = stack[i]->rchild;
            }
        }
        start = end1;
    }
}

void preCode(Node *root) {
    if (!root)
        return;
    preCode(root->lchild);
    printf("%c %d %s \n", root->data, root->weight,root->code);

    preCode(root->rchild);
}

void getCode(char ***hash, Node *root) {
    if (!root)
        return;
    getCode(hash, root->lchild);
    char data=root->data;
    if (data != '\0') {
        if(data>='a'&&data<='z'){
            (*hash)[data - 'a'] = root->code;
        }else if(data>='A'&&data<='Z'){
            (*hash)[data - 'A'+26] = root->code;
        }else if(data==' '){
            (*hash)[52] = root->code;
        }else{
            (*hash)[53] = root->code;
        }
    }
    getCode(hash, root->rchild);
}

char *coding(char **hash, char *s) {
    char *ans = (char *) malloc(10000);
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if(s[i]<='z'&&s[i]>='a'){
            strcat(ans, hash[s[i] - 'a']);
        }else if(s[i]<='Z'&&s[i]>='A'){
            strcat(ans, hash[s[i] - 'A'+26]);
        }else if(s[i]==' '){
            strcat(ans, hash[52]);
        }else{
            strcat(ans, hash[53]);
        }
    }
    return ans;
}

char *contain(char **hash, char *s) {
    int ansi = 0;
    for (int i = 0; i < 54; i++) {
        if (strcmp(hash[i], s) == 0) {
            ansi = i + 1;
            break;
        }
    }
    char *ans = (char *) malloc(2);
    strcpy(ans, "");
    switch (ansi) {
        case 1:
            strcat(ans, "a");
            break;
        case 2:
            strcat(ans, "b");
            break;
        case 3:
            strcat(ans, "c");
            break;
        case 4:
            strcat(ans, "d");
            break;
        case 5:
            strcat(ans, "e");
            break;
        case 6:
            strcat(ans, "f");
            break;
        case 7:
            strcat(ans, "g");
            break;
        case 8:
            strcat(ans, "h");
            break;
        case 9:
            strcat(ans, "i");
            break;
        case 10:
            strcat(ans, "j");
            break;
        case 11:
            strcat(ans, "k");
            break;
        case 12:
            strcat(ans, "l");
            break;
        case 13:
            strcat(ans, "m");
            break;
        case 14:
            strcat(ans, "n");
            break;
        case 15:
            strcat(ans, "o");
            break;
        case 16:
            strcat(ans, "p");
            break;
        case 17:
            strcat(ans, "q");
            break;
        case 18:
            strcat(ans, "r");
            break;
        case 19:
            strcat(ans, "s");
            break;
        case 20:
            strcat(ans, "t");
            break;
        case 21:
            strcat(ans, "u");
            break;
        case 22:
            strcat(ans, "v");
            break;
        case 23:
            strcat(ans, "w");
            break;
        case 24:
            strcat(ans, "x");
            break;
        case 25:
            strcat(ans, "y");
            break;
        case 26:
            strcat(ans, "z");
            break;
        case 27:
            strcat(ans, "A");
            break;
        case 28:
            strcat(ans, "B");
            break;
        case 29:
            strcat(ans, "C");
            break;
        case 30:
            strcat(ans, "D");
            break;
        case 31:
            strcat(ans, "E");
            break;
        case 32:
            strcat(ans, "F");
            break;
        case 33:
            strcat(ans, "G");
            break;
        case 34:
            strcat(ans, "H");
            break;
        case 35:
            strcat(ans, "I");
            break;
        case 36:
            strcat(ans, "J");
            break;
        case 37:
            strcat(ans, "K");
            break;
        case 38:
            strcat(ans, "L");
            break;
        case 39:
            strcat(ans, "M");
            break;
        case 40:
            strcat(ans, "N");
            break;
        case 41:
            strcat(ans, "O");
            break;
        case 42:
            strcat(ans, "P");
            break;
        case 43:
            strcat(ans, "Q");
            break;
        case 44:
            strcat(ans, "R");
            break;
        case 45:
            strcat(ans, "S");
            break;
        case 46:
            strcat(ans, "T");
            break;
        case 47:
            strcat(ans, "U");
            break;
        case 48:
            strcat(ans, "V");
            break;
        case 49:
            strcat(ans, "W");
            break;
        case 50:
            strcat(ans, "X");
            break;
        case 51:
            strcat(ans, "Y");
            break;
        case 52:
            strcat(ans, "Z");
            break;
        case 53:
            strcat(ans, " ");
            break;
        case 54:
            strcat(ans, ".");
            break;
        default:
            ans = NULL;
    }
    return ans;
}

char *uncoding(char **hash, char *s) {
    char *ans = (char *) malloc(1000);
    strcpy(ans, "");
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (i == len - 1)
            break;
        for (int L = 1; L <= len / 2 + 1; L++) {
            int j = i + L;
            if (j > len)
                break;
            char *ss = (char *) malloc(L + 1);
            int count = 0;
            for (int k = i; k < j; k++) {
                ss[count++] = s[k];
            }
            ss[count] = '\0';
            char *anss;
            if (anss = contain(hash, ss)) {
                strcat(ans, anss);
                i += L;
                L = 0;
            }
            free(ss);
        }
    }
    return ans;
}

int *getWeight(char *s) {
    int *code = (int *) malloc(sizeof(int) * 54);
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == '.')
            code[53]++;
        else if (s[i] == ' ')
            code[52]++;
        else if (s[i] <= 'Z' && s[i] >= 'A') {
            code[26 + s[i] - 'A']++;
        } else {
            code[s[i] - 'a']++;
        }
    }
//    for (int i = 0; i < 54; i++) {
//        printf("%d\n", code[i]);
//    }
    return code;
}
int main() {

    char *s = (char *) malloc(1000), *s1 = (char *) malloc(1000),
            *temp = (char *) malloc(100);
    do {
        scanf("%s", temp);
        strcat(s, temp);
        strcat(s, " ");
    } while (temp[strlen(temp) - 1] != '#' != 0);
    s[strlen(s)-2]='\0';
    scanf("%s", s1);
    int *code = getWeight(s);

    Node *root = build(code);
       char **hash = (char **)malloc(sizeof(char *) * 54);
       for (int i = 0; i < 54; i++) {
         hash[i] = (char *)malloc(100);
       }
    setCode(root);
    preCode(root);
       getCode(&hash, root);
    //   for (int i = 0; i < 6; i++) {
    //     printf("%c:%s\n", 'A' + i, hash[i]);
    //   }
       printf("%s\n", coding(hash, s));
       printf("%s", uncoding(hash, s1));

    return 0;
}
