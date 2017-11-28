#include "bt.h"
#include "fileio.h"
#include "data.h"

typedef struct page Page;

int getRoot()
{
	openIndexFile();
	fseek(index, 0, SEEK_SET);

	if (fread(&root, sizeof(int), 1, index) == 0)
	{
		fwrite(-1, sizeof(int), 1, index);
		root = 0;
	}
	return root;
}

int createTree()
{
	return createRoot(NIL, NIL, NIL);
}

int insert(int rrn, int key, int * promo_child, int * promo_key)
{
	Page thisPage;
	Page newPage;
	int teste;
	int found, promoted;
	int pos, promotedRRN, promotedKey;

	if (rrn == -1)
	{
		*promo_key = key;
		*promo_child = NIL;
		return 1;
	}

	readBT(rrn, &thisPage);

	found = searchNode(key, &thisPage, &pos);
	if (found)
	{
		printf("Error: attempt to insert duplicate key: %c \n\007", key);
		return 0;
	}
	promoted = insert(thisPage.child[pos], key, &promotedRRN, &promotedKey);

	if (!promoted)
	{
		return 0;
	}

	if (thisPage.keycount < MAX)
	{
		insertNode(promotedKey, promotedRRN, &thisPage);
		writeBT(rrn, &thisPage);
		printf("Register Sucessfully Added!");
		return 0;
	}
	else
	{
		splitPage(promotedKey, promotedRRN, &thisPage, promo_key, promo_child, &newPage);
		writeBT(rrn, &thisPage);
		writeBT(*promo_child, &newPage);
		printf("Register Sucessfully Added!");
		return 1;
	}

}

void setRoot(int root)
{
	openIndexFile();
	fseek(index, 0, SEEK_SET);
	fwrite(&root, sizeof(int), 1, index);
	closeIndexFile();
	openIndexFile();
}

int createRoot(int key, int left, int right)
{
	Page newPage;
	int rrn;
	rrn = getpage();
	pageinit(&newPage);
	newPage.key[0] = key;
	newPage.child[0] = left;

	/*if (right == root && right == left)
	{
		rrn = root + 1;
		right += 2;
	}*/

	newPage.child[1] = right;

	if (key == -1)
		newPage.keycount = 0;
	else
		newPage.keycount = 1;

	setRoot(rrn);
	writeBT(rrn, &newPage);

	return(rrn);
}

void readBT(int rrn, Page *page_ptr)
{
	openIndexFile();
	rewind(index);
	int addr;
	addr = (rrn * sizeof(Page)) + 4;
	fseek(index, addr, 0);
	Page aux;
	fread(&aux, sizeof(Page), 1, index);
	*page_ptr = aux;

	return;
}

void writeBT(int rrn, Page *page_ptr)
{
	openIndexFile();
	int addr;
	Page aux = *page_ptr;
	rewind(index);
	addr = (rrn * sizeof(Page))+4;
	fseek(index, addr , 0);
	fwrite(&aux, sizeof(Page), 1, index);
	fclose(index);
	return;
}

void pageinit(Page *p_page)
{
	int j;
	for (j = 0; j < MAX; j++) {
		p_page->key[j] = NIL;
		p_page->child[j] = NIL;
	}
	p_page->child[MAX] = NIL;
}

int getpage()
{
	int addr;
	openIndexFile();

	fseek(index, 0, SEEK_END) - 4;
	addr = ftell(index);
	if (addr < 0)
		return 0;

	return (addr / sizeof(Page));
}

int searchNode(int key, Page *p_page, int *pos)
{
	int i;
	for (i = 0; i < p_page->keycount && key > p_page->key[i]; i++);
	*pos = i;
	if (*pos < p_page->keycount && key == p_page->key[*pos])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void splitPage(int key, int r_child, Page *p_oldpage, int *promo_key, int *promo_r_child, Page *p_newpage)
{
	int j;
	short mid;
	int workkeys[MAX + 1];
	int workchil[MAX + 2];
	for (j = 0; j < MAX; j++) {
		workkeys[j] = p_oldpage->key[j];
		workchil[j] = p_oldpage->child[j];
	}
	workchil[j] = p_oldpage->child[j];
	for (j = MAX; key < workkeys[j - 1] && j > 0; j--) {
		workkeys[j] = workkeys[j - 1];
		workchil[j + 1] = workchil[j];
	}
	workkeys[j] = key;
	workchil[j + 1] = r_child;
	*promo_r_child = getpage();
	pageinit(p_newpage);

	/*if (*promo_r_child == root)
	{
		*promo_r_child = root+1;
		Page p_r_newpage;
		pageinit(&p_r_newpage);
		p_oldpage->key[0] = workkeys[0];
		p_oldpage->key[1] = workkeys[1];
		p_oldpage->key[2] = NIL;
		p_newpage->child[0] = root;
		p_newpage->key[0] = workkeys[2];
		p_r_newpage.key[0] = key;
		writeBT(root + 2, &p_r_newpage);
		p_newpage->child[1] = root + 2;
		*promo_key = workkeys[MIN];
		return;
	}*/

	for (j = 0; j < MIN; j++) {
		p_oldpage->key[j] = workkeys[j];
		p_oldpage->child[j] = workchil[j];
		p_newpage->key[j] = workkeys[j +  MIN];
		p_newpage->child[j] = workchil[j + 1 + MIN];
		p_oldpage->key[j + MIN] = NIL;
		p_oldpage->child[j + 1 + MIN] = NIL;
	}
	p_oldpage->child[MIN] = workchil[MIN];
	p_newpage->child[MIN] = workchil[j + 1 + MIN];
	p_newpage->keycount = MIN;
	p_oldpage->keycount = MIN;
	*promo_key = workkeys[MIN];

	if (p_newpage->key[0] == *promo_key)
	{
		p_newpage->key[0] = key;
		p_newpage->key[1] = NIL;
	}

}

void insertNode(int key, int r_child, Page *p_page)
{
	int j;
	for (j = p_page->keycount; key < p_page->key[j - 1] && j > 0; j--) {
		p_page->key[j] = p_page->key[j - 1];
		p_page->child[j + 1] = p_page->child[j];
	}
	p_page->keycount++;
	p_page->key[j] = key;
	p_page->child[j + 1] = r_child;
}

void listAll(int rrn)
{
	Page currentPage, lastPage;
	int pos = 0;
	readBT(rrn, &currentPage);

	for (pos = 0; pos < currentPage.keycount; pos++)
	{
		if (currentPage.child[pos] != NIL)
		{
			lastPage = currentPage;
			listAll(currentPage.child[pos]);
			printData(lastPage.key[pos]);
			listAll(currentPage.child[pos+1]);
		}
		else
		{
			printPage(&currentPage);
			break;
		}
	}
}

