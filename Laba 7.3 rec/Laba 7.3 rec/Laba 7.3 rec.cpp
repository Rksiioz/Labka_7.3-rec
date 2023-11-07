#include <iostream>
#include <iomanip>
#include <limits>
#include <unordered_map>
#include <time.h>

void Create(int** arr, const int rowCount, const int colCount, const int Low, const int High, int i, int j) {
	if (i >= rowCount) {
		return;
	}

	arr[i][j] = Low + rand() % (High - Low + 1);

	if (j + 1 < colCount) {
		Create(arr, rowCount, colCount, Low, High, i, j + 1);
	}
	else {
		Create(arr, rowCount, colCount, Low, High, i + 1, 0);
	}
}

void Input(int** arr, const int rowCount, const int colCount, int i, int j)
{
	if (i < rowCount)
	{
		if (j < colCount)
		{
			std::cout << "a[" << i << "][" << j << "] = ";
			std::cin >> arr[i][j];
			Input(arr, rowCount, colCount, i, j + 1);
		}
		else
		{
			Input(arr, rowCount, colCount, i + 1, 0);
		}
	}
}

void Print(int** arr, const int rowCount, const int colCount, int i, int j) {
	if (i >= rowCount) {
		return;
	}

	std::cout << " " << std::setw(4) << arr[i][j];

	if (j + 1 < colCount) {
		Print(arr, rowCount, colCount, i, j + 1);
	}
	else {
		std::cout << std::endl;
		Print(arr, rowCount, colCount, i + 1, 0);
	}
}

int countNonZeroRows(int** arr, int rowCount, int colCount, int currentRow) {
	if (currentRow >= rowCount) {
		return 0;
	}

	int rowHasZero = 0;

	for (int j = 0; j < colCount; j++) {
		if (arr[currentRow][j] == 0) {
			rowHasZero = 1;
			break;
		}
	}
	return countNonZeroRows(arr, rowCount, colCount, currentRow + 1) + (1 - rowHasZero);
}


void findMaxDoubleValue(int** arr, const int rowCount, const int colCount, int& result, int i, int j, std::unordered_map<int, bool>& cache) {
	if (i >= rowCount) {
		return;
	}

	if (i == 0 && j == 0) {
		result = std::numeric_limits<int>::min();
	}

	int value = arr[i][j];
	if (cache[value]) {
		if (value > result) {
			result = value;
		}
	}

	cache[value] = true;

	if (j + 1 < colCount) {
		findMaxDoubleValue(arr, rowCount, colCount, result, i, j + 1, cache);
	}
	else {
		findMaxDoubleValue(arr, rowCount, colCount, result, i + 1, 0, cache);
	}
}

int main() {

	srand((unsigned)time(NULL));

	int rowCount, colCount, maxDouble;
	int Low = 0;
	int High = 30;
	std::cout << "rowCount: "; std::cin >> rowCount;
	std::cout << "colCount: "; std::cin >> colCount;
	int** arr = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
		arr[i] = new int[colCount];

	//Input(arr, rowCount, colCount, 0, 0);
	Create(arr, rowCount, colCount, Low, High, 0, 0);
	Print(arr, rowCount, colCount, 0, 0);

	int nonZeroRowCount = countNonZeroRows(arr, rowCount, colCount, 0);
	std::unordered_map<int, bool> cache;

	findMaxDoubleValue(arr, rowCount, colCount, maxDouble, 0, 0, cache);

	printf("Non zero rows: %d\n", nonZeroRowCount);
	printf("Max double value: %d\n", maxDouble);


	for (int i = 0; i < rowCount; i++)
		delete[] arr[i];
	delete[] arr;

	return 0;
}