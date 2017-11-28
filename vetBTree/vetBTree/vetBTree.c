// vetBTree.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "fileio.h"
#include "data.h"
#include "bt.h"

int main()
{
	openControlFile();
	openDataFile();

	if (openIndexFile())
	{
		root = getRoot();
	}
	else 
		root = createTree();
	
	int exit = -1, option;

	while (exit == -1)
	{
		printf("\tWELCOME TO DOGCARE\n\n");
		printf("\t1. New Register\n");
		printf("\t2. List All\n");
		printf("\t3. Search Register \n");
		printf("\t4. Advanced Listing \n");
		printf("\t5. Quit \n\n");

		printf("\tOption: ");
		scanf("%d", &option);

		switch (option)
		{
		case 1:
			insertData();
			break;
		case 2:
			system("cls");
			listAll(root);
			getch();

			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			exit = 0;
			break;
		default:
			printf("Invalid Operation.");
			getch();
			system("cls");
			break;
		}
	}

}

