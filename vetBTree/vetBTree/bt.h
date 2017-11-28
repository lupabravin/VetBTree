
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2
#define NIL (-1)
#define NOKEY '@'
#define FALSE 0
#define TRUE 1

typedef struct page {
	int keycount;
	int key[MAX];
	int child[MAX + 1];
} Page;

int root;

void btclose();
void btopen();
void readBT(int rrn, Page *page_ptr);
void writeBT(int rrn, Page *page_ptr);
int createRoot(int key, int left, int right);
int createTree();
int getpage();
int getRoot(); 
int insert(int rrn, int key, int *promo_r_child, int *promo_key);
void insertNode(int key, int r_child, Page *p_page);
void pageinit(Page *p_page);
void setRoot(int root);
int searchNode(int key, Page *p_page, int *pos);
void splitPage(int key, int r_child, Page *p_oldpage, int *promo_key, int *promo_r_child, Page *p_newpage);
int getLastCode();
void listAll(int rrn);
void printPage(Page * currentPage);
void printData(int key);
void printRegister(int key, Page * currentPage);
int searchRegister(int key, int root);
