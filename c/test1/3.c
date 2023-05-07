#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define N 100
#define M 2 * N + 1
int n;
typedef struct {
  int Weight;
  int parent, lchild, rchild;
} HTNode, HuffumanTree[M + 1];
typedef struct {
  char value;
  int fre;
} keyw, keyword[N];
typedef struct node {
  int num;
  struct node *next;
} Node;
typedef struct {
  char Value;
  Node *head;
} HcCode, HuffumanCode[N];
void Mainmean() {
  printf("-------------------����������������-------------------\n");
  printf("1.�����ļ�souce��ͳ���ַ�Ƶ�ȣ���������������\n");
  printf("2.�����ѽ��õĹ����������б��룬�����ļ�code�С�\n");
  printf("3.�����ѽ��õĹ����������ļ�code���룬�����ļ�decode�С�\n");
  printf("4.�˳�����\n");
  printf("------------------------------------------------------\n");
  printf("���������ѡ��\n");
}
int existin(char a, keyword kw, int n);
int countvalue(char a, char str[]);
int StatChar(char str[], keyword kw);
void CreatHufuman(HuffumanTree ht, keyword kw, int n);
void select(HuffumanTree ht, int n, int *a, int *b);
void CrtHuffmanCode1(HuffumanTree ht, HuffumanCode hc, int n, keyword kw);
void print(keyword kw, int n, HuffumanTree ht);
void print2(HuffumanCode hc, int n);
void creatcode(HuffumanCode hc, char str[], char num[]);
void opencode(HuffumanTree ht, char str[], int n, char inter[], keyword kw);
int main() {
  HuffumanTree ht;
  keyword kw;
  HuffumanCode hc;
  while (1) {
    Mainmean();
    int num;
    scanf("%d", &num);
    switch (num) {
    case 1: {
      printf("-------------------������������-------------------\n");
      printf("1.�Ӽ����������ַ������ļ�souce,������������\n");
      printf("2.ֱ�Ӵ��ļ�souce�ж�ȡ�ַ�������������\n");
      printf(
          "3."
          "�Ӽ����������ַ�����ԭ���ļ�"
          "�"
          "�"
          "�"
          "�"
          "�"
          "�"
          "�"
          "�"
          "�"
          "�"
          "�"
          "�"
          "�"
          "�"
          "\n");
      printf("��ѡ�����������е�һ��:\n");
      int num1;
      scanf("%d", &num1);
      switch (num1) {
      case 1: {
        FILE *fp = fopen("E:\\����������������\\souce.txt", "w");
        printf("��������Ҫ������ַ���\n");
        char str1[1000];
        scanf("%s", str1);
        fputs(str1, fp);
        n = StatChar(str1, kw);
        CreatHufuman(ht, kw, n);
        print(kw, n, ht);
        fclose(fp);
        break;
      }
      case 2: {
        FILE *fp = fopen("E:\\����������������\\souce.txt", "r");
        char str2[1000];
        int i = 0;
        char ch;
        while ((ch = fgetc(fp)) != EOF) {
          str2[i++] = ch;
        }
        n = StatChar(str2, kw);
        CreatHufuman(ht, kw, n);
        print(kw, n, ht);
        fclose(fp);
        break;
      }
      case 3: {
        FILE *fp = fopen("E:\\����������������\\souce.txt", "r+");
        fseek(fp, 0, SEEK_END);
        printf("��������Ҫ���ӱ�����ַ���\n");
        char str3[1000];
        scanf("%s", str3);
        fputs(str3, fp);
        fclose(fp);
        FILE *fq = fopen("E:\\����������������\\souce.txt", "r");
        int i = 0;
        char ch;
        while ((ch = fgetc(fq)) != EOF) {
          str3[i++] = ch;
        }
        n = StatChar(str3, kw);
        CreatHufuman(ht, kw, n);
        print(kw, n, ht);
        fclose(fq);
        break;
      }
      default:
        printf("�������ѡ�����������²���\n");
        break;
      }
      break;
    }
    case 2: {
      printf("-------------------����-------------------\n");
      CrtHuffmanCode1(ht, hc, n, kw);
      FILE *fp = fopen("E:\\����������������\\souce.txt", "r");
      char str4[1000];
      int i = 0;
      char ch;
      while ((ch = fgetc(fp)) != EOF) {
        str4[i++] = ch;
      }
      fclose(fp);
      print2(hc, n);
      char num[10000];
      creatcode(hc, str4, num);
      FILE *fq = fopen("E:\\����������������\\code.txt", "w");
      fputs(num, fq);
      fclose(fq);
      break;
    }
    case 3: {
      printf("-------------------����-------------------\n");
      FILE *fp = fopen("E:\\����������������\\code.txt", "r");
      char str5[1000];
      int i = 0;
      char ch;
      while ((ch = fgetc(fp)) != EOF) {
        str5[i++] = ch;
      }
      fclose(fp);
      char inter[1000];
      opencode(ht, str5, n, inter, kw);
      FILE *fq = fopen("E:\\����������������\\decode.txt", "r");
      fputs(inter, fq);
      fclose(fq);
      break;
    }
    case 4: {
      return 0;
      break;
    }
    default: {
      printf("�������ѡ�����������²���\n");
      break;
    }
    }
  }
}
int existin(char a, keyword kw, int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (kw[i].value == a) {
      return 1;
    }
  }
  return 0;
}
int countvalue(char a, char str[]) {
  int n = 0, i = 0;
  while (str[i] != '\0') {
    if (str[i] == a) {
      n++;
    }
    i++;
  }
  return n;
}
int StatChar(char str[], keyword kw) {
  int n = 0, m = 0;
  while (str[m] != '\0') {
    if (existin(str[m], kw, n) == 0) {
      kw[n].value = str[m];
      kw[n].fre = countvalue(str[m], str);
      n++;
    }
    m++;
  }
  return n;
}
void select(HuffumanTree ht, int n, int *s1, int *s2) {
  int a = 1000, b = 10000, t1 = 0, t2 = 0;
  for (int i = 1; i <= n; i++) {
    if (ht[i].parent == 0) {
      if (ht[i].Weight < a) {
        b = a;
        a = ht[i].Weight;
        t2 = t1;
        t1 = i;
      } else if (ht[i].Weight < b) {
        b = ht[i].Weight;
        t2 = i;
      }
    }
  }
  *s1 = t1;
  *s2 = t2;
}
void CreatHufuman(HuffumanTree ht, keyword kw, int n) {
  int m = 2 * n - 1, i;
  int s1, s2;
  for (i = 0; i < n; i++) {
    ht[i + 1] = { kw[i].fre, 0, 0, 0};
  }
  for (i = n; i < m; i++) {
    ht[i + 1] = { 0, 0, 0, 0};
  }
  for (i = n + 1; i <= m; i++) {
    select(ht, i - 1, &s1, &s2);
    ht[i].Weight = ht[s1].Weight + ht[s2].Weight;
    ht[i].lchild = s1;
    ht[i].rchild = s2;
    ht[s1].parent = i;
    ht[s2].parent = i;
  }
}
void print(keyword kw, int n, HuffumanTree ht) {
  int i;
  printf("ͳ�Ƶ��ַ���Ƶ��Ϊ��\n");
  for (i = 0; i < n; i++) {
    printf("%c %d\n", kw[i].value, kw[i].fre);
  }
  printf("�����Ĺ�������Ϊ��\n");
  int j;
  for (j = 1; j <= 2 * n - 1; j++) {
    printf("%d %d %d %d\n", ht[j].Weight, ht[j].parent, ht[j].lchild,
           ht[j].rchild);
  }
}
void CrtHuffmanCode1(HuffumanTree ht, HuffumanCode hc, int n, keyword kw) {
  int s;
  for (int i = 1; i <= n; i++) {
    hc[i].Value = kw[i - 1].value;
    HTNode *t = &ht[i];
    Node *head1, *p;
    p = (Node *)malloc(sizeof(Node));
    p->next = NULL;
    head1 = p;
    s = i;
    while (t->parent != 0) {
      Node *q = (Node *)malloc(sizeof(Node));
      if (ht[t->parent].lchild == s) {
        q->num = 0;
      } else if (ht[t->parent].rchild == s) {
        q->num = 1;
      }
      q->next = p->next;
      p->next = q;
      s = t->parent;
      t = &ht[t->parent];
    }
    hc[i].head = head1;
  }
}

void print2(HuffumanCode hc, int n) {
  printf("�õ��Ĺ�������Ϊ��\n");
  int i;
  for (i = 1; i <= n; i++) {
    printf("%c:", hc[i].Value);
    Node *p = hc[i].head;
    p = p->next;
    while (p != NULL) {
      printf("%d->", p->num);
      p = p->next;
    }
    printf("NULL\n");
  }
}
void creatcode(HuffumanCode hc, char str[], char num[]) {
  printf("����Ϊ��\n");
  int i = 1, j = 0, k = 0;
  while (j < strlen(str)) {
    while (1) {
      if (str[j] == hc[i].Value) {
        break;
      } else
        i++;
    }
    Node *p = hc[i].head->next;
    while (p != NULL) {
      printf("%d", p->num);
      num[k++] = '0' + p->num;
      p = p->next;
    }
    j++;
  }
  printf("\n");
}
void opencode(HuffumanTree ht, char str[], int n, char inter[], keyword kw) {
  printf("����Ϊ��\n");
  int m = 2 * n - 1;
  int i = 0, j = 0, t = 0;
  while (j < strlen(str)) {
    HTNode *p = &ht[m];
    while (p->rchild != 0) {
      if (str[j++] == '0') {
        t = p->lchild;
        p = &ht[p->lchild];
      } else {
        t = p->rchild;
        p = &ht[p->rchild];
      }
    }
    printf("%c", kw[t - 1].value);
    inter[i++] = kw[t - 1].value;
  }
  printf("\n");
}
