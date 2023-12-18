#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;
int main()
{
	// Открываем архив
	setlocale(LC_ALL, "Russian");
	const char* archiveName = "archive.rar.rar";
	HANDLE hFile = CreateFile(archiveName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Ошибка открытия архива. Пожалуйста, попробуйте снова" << endl;
		return 1;
	}
	// Подсчитываем размер архива
	DWORD archiveSize = GetFileSize(hFile, NULL);
	if (archiveSize == INVALID_FILE_SIZE)
	{
		cerr << "Ошибка подсчёта размера архива" << endl;
		CloseHandle(hFile);
		return 1;
	}
	// Выводим размер архива
	cout << "Размер архива: " << archiveSize << " байт" << endl;
	// Добавляем информацию о размере архива в массив buffer типа vector
	vector<char> buffer(archiveSize);
	// Проверяем, успешно ли добавлена информация о размере архива в массив buffer
	DWORD bytesRead;
	if (!ReadFile(hFile, &buffer[0], archiveSize, &bytesRead, NULL))
	{
		cerr << "Ошибка чтения архива" << endl;
		CloseHandle(hFile);
		return 1;
	}

	CloseHandle(hFile);

	// Далее можно выполнять необходимые дальнейшие действия над данными, поскольку мы не удаляем значения из массива buffer

	return 0;
}
