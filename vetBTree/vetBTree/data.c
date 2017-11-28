#include "data.h"
#include "bt.h"
#include "fileio.h"

typedef struct dogcontrol DogControl;
typedef struct dogdata DogData;

void insertData() {
	system("cls");

	DogControl newControl;
	DogData newData;

	printf("Control Code: ");
	scanf("%d", &newControl.controlCode);
	getc(stdin);
	printf("\n");

	newControl.dogCode = newData.dogCode = getLastCode() + 1;
	setLastCode(newControl.dogCode);

	printf("Medicine Name: ");
	gets(&newControl.medicine);
	printf("\n");

	printf("Doctor's Name: ");
	gets(&newControl.doctor);
	printf("\n");

	printf("Dog's Race: ");
	gets(&newData.race);
	printf("\n");

	printf("Dog's Name: ");
	gets(&newData.name);
	printf("\n");

	if (insertRegister(newControl, newData) == 1)
	{
		getch();
		system("cls");
	}
}


int getLastCode()
{
	int code = 0;
	openDataFile();
	rewind(data);
	fread(&code, sizeof(int), 1, data);
	return code;
}


int setLastCode(int code)
{
	openDataFile();
	rewind(data);
	fwrite(&code, sizeof(int), 1, data);
	closeDataFile();
}

void printPage(Page * currentPage)
{
	int node;
	for (node = 0; node < currentPage->keycount; node++)
	{
		if (currentPage->key[node] == NIL)
			break;
		printData(currentPage->key[node]);
	}
}


void printData(int key)
{
	DogControl node;
	DogData dog;
	openControlFile();
	rewind(control);
	int addr;
	fflush(stdin);

	while (fread(&node, sizeof(DogControl), 1, control) != 0)
	{
		if (node.controlCode == key)
		{
			printf("\n Control Code: %d", key);
			printf("\n Dog Code: %d ", node.dogCode);
			printf("\n Medicine: %s ", node.medicine);
			printf("\n Apllying Doctor: %s ", node.doctor);

			closeDataFile();
			openDataFile();
			rewind(data);

			addr = fseek(data, (sizeof(DogData) * (node.dogCode-1) + 4), 0);
			fread(&dog, sizeof(DogData), 1, data);
			printf("\n Dog's Name: %s ", dog.name);
			printf("\n Dog's Race: %s", dog.race);
			printf("\n");

		}
	}
	openControlFile();
}