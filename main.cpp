#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;
int main()
{
	// ��������� �����
	setlocale(LC_ALL, "Russian");
	const char* archiveName = "archive.rar.rar";
	HANDLE hFile = CreateFile(archiveName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "������ �������� ������. ����������, ���������� �����" << endl;
		return 1;
	}
	// ������������ ������ ������
	DWORD archiveSize = GetFileSize(hFile, NULL);
	if (archiveSize == INVALID_FILE_SIZE)
	{
		cerr << "������ �������� ������� ������" << endl;
		CloseHandle(hFile);
		return 1;
	}
	// ������� ������ ������
	cout << "������ ������: " << archiveSize << " ����" << endl;
	// ��������� ���������� � ������� ������ � ������ buffer ���� vector
	vector<char> buffer(archiveSize);
	// ���������, ������� �� ��������� ���������� � ������� ������ � ������ buffer
	DWORD bytesRead;
	if (!ReadFile(hFile, &buffer[0], archiveSize, &bytesRead, NULL))
	{
		cerr << "������ ������ ������" << endl;
		CloseHandle(hFile);
		return 1;
	}

	CloseHandle(hFile);

	// ����� ����� ��������� ����������� ���������� �������� ��� �������, ��������� �� �� ������� �������� �� ������� buffer

	return 0;
}
