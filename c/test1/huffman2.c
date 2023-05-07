#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hafutree {
  char ch;
  int parent;
  int weight;
  int lchild;
  int rchild;
} hafutree;
float wt[200];
char ch_ch[200];
hafutree **inithafutree(int wet[], char diff_zf[], int n) {
  hafutree **head;
  head = (hafutree **)malloc(sizeof(hafutree *) * n * 2);
  for (int i = 1; i <= n; i++) {
    head[i] = (hafutree *)malloc(sizeof(hafutree));
    head[i]->ch = diff_zf[i - 1];
    head[i]->weight = wet[i - 1];
    head[i]->parent = 0;
    head[i]->lchild = 0;
    head[i]->rchild = 0;
  }
  for (int i = n + 1; i < 2 * n; i++) {
    head[i] = (hafutree *)malloc(sizeof(hafutree));
    head[i]->ch = '#';
    head[i]->weight = 0;
    head[i]->parent = 0;
    head[i]->lchild = 0;
    head[i]->rchild = 0;
  }
  return head;
}
void create_hafutree(hafutree **head, int x) {
  int m, n;
  int k = x;
  while (k < 2 * x - 1) {
    for (int j = 1; j <= k; j++) {
      if (head[j]->parent == 0) {
        m = j;
        break;
      }
    }
    for (int i = 1; i <= k; i++) {
      if (head[m]->weight > head[i]->weight && head[i]->parent == 0)
        m = i;
    }
    for (int j = 1; j <= k; j++) {
      if (head[j]->parent == 0 && m != j) {
        n = j;
        break;
      }
    }
    for (int i = 1; i <= k; i++) {
      if (i == m)
        continue;
      if (head[n]->weight > head[i]->weight && head[i]->parent == 0)
        n = i;
    }
    head[++k]->weight = head[m]->weight + head[n]->weight;
    head[k]->lchild = m;
    head[k]->rchild = n;
    head[m]->parent = k;
    head[n]->parent = k;
  }
}
void paixu(int getwt[], char getch[]) {
  int a;
  char b;
  for (int i = 0; i < strlen(getch) - 1; i++) {
    for (int j = 0; j < strlen(getch) - 1 - i; j++) {
      if (getch[j] > getch[j + 1]) {
        b = getch[j + 1];
        getch[j + 1] = getch[j];
        getch[j] = b;
        a = getwt[j + 1];
        getwt[j + 1] = getwt[j];
        getwt[j] = a;
      }
    }
  }
  for (int i = 0; i < strlen(getch); i++)
    wt[i] = getwt[i];
}
hafutree **getdifferentchar(char *text, int *number) {
  hafutree **head;
  int m = 0;
  int n = 0;
  int flog = 0;
  char *getch;
  int *getwt;
  for (int i = 0; text[i] != '#'; i++)
    m++;
  text[m] = '\0';
  getch = (char *)malloc(sizeof(char) * m);
  getwt = (int *)malloc(sizeof(int) * m);
  for (int i = 0; i <= m; i++) {
    getwt[i] = 0;
  }
  getch[n] = text[n];
  getch[++n] = '\0';
  for (int i = 0; text[i] != '\0'; i++) {
    flog = 0;
    for (int j = 0; getch[j] != '\0'; j++) {
      if (text[i] == getch[j]) {
        getwt[j]++;
        flog = 1;
        break;
      } else
        continue;
    }
    if (flog == 0) {
      getch[n] = text[i];
      getwt[n]++;
      getch[++n] = '\0';
    }
  }
  *number = strlen(getch);
  paixu(getwt, getch);
  head = inithafutree(getwt, getch, strlen(getch));
  return head;
}
char **makecode(hafutree **head, int n) {
  char a[n];
  int start;
  int p;
  int k;
  char **ch;
  ch = (char **)malloc(sizeof(char *) * n);
  ch[0] = (char *)malloc(sizeof(char) * 5);
  for (int i = 1; i <= n; i++) {
    start = n - 1;
    a[start] = '\0';
    p = head[i]->parent;
    k = i;
    while (p) {
      if (head[p]->lchild == k) {
        a[--start] = '0';
      } else if (head[p]->rchild == k) {
        a[--start] = '1';
      }
      k = p;
      p = head[p]->parent;
    }

    ch[i] = (char *)malloc(sizeof(char) * (n - start));
    strcpy(ch[i], &a[start]);
  }
  return ch;
}
char *translatecode(hafutree **head, char hafu_number[], int y) {
  int k = 0;
  int m, x, n;
  char *tr;
  tr = (char *)malloc(sizeof(char) * 500);
  x = 0;
  for (int i = k; hafu_number[i] != '\0';) {
    m = 2 * y - 1;
    n = i;
    while (head[m]->lchild && head[m]->rchild) {
      if (hafu_number[n] == '0') {
        m = head[m]->lchild;
      } else if (hafu_number[n] == '1') {
        m = head[m]->rchild;
      }
      n++;
      i++;
    }
    tr[x++] = head[m]->ch;
    tr[x] = '\0';
  }
  return tr;
}
int main() {
  FILE *fp1;
  fp1 = fopen("/home/kangning/clone/Code/c/test1/andian.c", "r");
  if (fp1 == NULL) {
    printf("/home/kangning/clone/Code/c/test1/andian.c");
    exit(1);
  }

  char hafuch[500];
  char hafu_number[1000];
  char hafuch_num[1000] = "";
  hafutree **head;
  char *tr;
  char **ch;
  int n;
  int j;

  fgets(hafuch, 500, fp1);
  fclose(fp1);

  head = getdifferentchar(hafuch, &n);

  create_hafutree(head, n);

  ch = makecode(head, n);
  for (int i = 0; hafuch[i] != '\0'; i++) {
    j = 1;
    while (j <= n) {
      if (head[j]->ch == hafuch[i]) {
        strcat(hafuch_num, ch[j]);
        break;
      }
      j++;
    }
  }
  printf("�����ı���ɹ���\n");
  printf("��������");
  puts(hafuch_num);

  FILE *fp2;
  fp2 = fopen("/home/kangning/clone/java-work/java/java-1/src/main/java/1.code",
              "w");
  if (fp2 == NULL) {
    printf("/home/kangning/clone/java-work/java/java-1/src/main/java/1.code");
    exit(1);
  }
  fputs(hafuch_num, fp2);
  fclose(fp2);
  printf("�ѽ�����������code.txt�ļ���\n");

  FILE *fp3;
  fp3 = fopen("/home/kangning/clone/java-work/java/java-1/src/main/java/1.code",
              "r");
  if (fp3 == NULL) {
    printf("/home/kangning/clone/java-work/java/java-1/src/main/java/1.code");
    exit(1);
  }
  fgets(hafu_number, 1000, fp3);
  fclose(fp3);

  tr = translatecode(head, hafu_number, n);
  printf("/home/kangning/clone/java-work/java/java-1/src/main/java/1.code\n");
  printf("��������");
  puts(tr);

  FILE *fp4;
  fp4 = fopen(
      "/home/kangning/clone/java-work/java/java-1/src/main/java/2.souce", "w");
  if (fp4 == NULL) {
    printf("/home/kangning/clone/java-work/java/java-1/src/main/java/2.souce");
    exit(1);
  }
  fputs(tr, fp4);
  fclose(fp4);
  printf("/home/kangning/clone/java-work/java/java-1/src/main/java/2.souce");
}
