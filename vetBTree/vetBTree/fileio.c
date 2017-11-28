#include "fileio.h"
#include "data.h"
#include "bt.h"


void openDataFile()
{
	//data = fopen("data.dat", "a+b");

	if ((data = fopen("data.dat", "r+")) == 0)
		data = fopen("data.dat", "w+");
}

void closeDataFile()
{
	fclose(data);
}

void openControlFile()
{
	//control = fopen("control.dat", "a+b");
	if ((control = fopen("control.dat", "r+")) == 0)
		control = fopen("control.dat", "w+");
}

void closeControlFile()
{
	fclose(control);
}

int openIndexFile()
{

	if ((index = fopen("index.dat", "r+b")) == 0)
	{
		index = fopen("index.dat", "w+b");
		return 0;
	}
	else
		return 1;
}

void closeIndexFile()
{
	fclose(index);
}

int insertRegister(DogControl newControl, DogData newData)
{
	openControlFile();
	openDataFile();

	int promoted, promo_rrn, promo_key;

	//Insert Dog Control Info to file (MAIN FILE 1)
	int rrnControl = fseek(control, 0, SEEK_END);
	fwrite(&newControl, sizeof(DogControl), 1, control);
	closeControlFile();
	openControlFile();

	//Insert Dog Data to file (MAIN FILE 2)
	int rrnData = fseek(data, 0, SEEK_END);
	fwrite(&newData, sizeof(DogData), 1, data);
	closeDataFile();
	openDataFile();

	promoted = insert(root, newControl.controlCode, &promo_rrn, &promo_key);
	if (promoted)
		root = createRoot(promo_key, root, promo_rrn);

	return 1;


}

