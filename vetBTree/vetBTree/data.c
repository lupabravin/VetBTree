#include "data.h"
#include "bt.h"

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

	newControl.dogCode = newData.dogCode = getLastCode();

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
		printf("Register Sucessfully Added!");
		getch();
		system("cls");
	}
}