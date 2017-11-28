#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

typedef struct dogcontrol {
	int controlCode;
	int dogCode;
	char medicine[30];
	char doctor[30];
}  DogControl;

typedef struct dogdata {
	int dogCode;
	char race[30];
	char name[30];

}  DogData;

void insertData();

#define CONTROL sizeof(DogControl)
#define DATA sizeof(DogData)

