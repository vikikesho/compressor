#include "LZW.h"
#include "FolderHandler.h"
#include <fstream>

int main()
{
	cout << "Nhap c de nen, d de giai nen." << endl;

	char cmd;
	cin >> cmd;

	if (cmd == 'c') {
		vector<string> nameList;
		vector<ifstream> fileList;

		cout << "So file can nen: ";
		int n;
		cin >> n;
		fileList.resize(n);

		cout << "Nhap ten tung file." << endl;

		for (int i = 0; i < n; i++)
		{
			string temp;
			cin >> temp;
			nameList.push_back(temp);

			fileList[i].open(temp);
		}

		ofstream tempOut("medium.txt", ios::app);

		for (int i = 0; i < nameList.size(); i++)
		{
			Combine(fileList[i], nameList[i], tempOut);
		}

		tempOut.close();

		ifstream tempIn("medium.txt");
		tempOut.open("output.lzw", ios::binary);

		LZWEncoder(tempIn, tempOut);

		tempIn.close();
		tempOut.close();

		remove("medium.txt");
	}
	else {
		string name;
		ifstream tempIn;
		ofstream tempOut;

		cout << "Nhap ten file can giai nen." << endl;
		cin >> name;

		tempIn.open(name, ios::binary);
		tempOut.open("medium.txt");

		LZWDecoder(tempIn, tempOut);

		tempOut.close();
		tempIn.close();

		tempIn.open("medium.txt");

		Separate(tempIn);

		tempIn.close();

		remove("medium.txt");
	}
	return 0;
}