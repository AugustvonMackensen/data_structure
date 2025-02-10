#include<stdio.h>
#include<string.h>

/* 
InsertionSort by ascending order. 
*/
void InsertionSort(int DataSet[], int length) {
	int i = 0;
	int j = 0;
	int value = 0;

	for (i = 1; i < length; i++) {
		if (DataSet[i - 1] <= DataSet[i]) {
			continue;
		}

		value = DataSet[i];

		for (j = 0; j < i; j++) {
			if (DataSet[j] > value) {
				//memmove() : 메모리내용 이동.
				//memmove() 대신 순환(loop)문으로 대체할수있으나, 성능이 떨어짐
				memmove(&DataSet[j + 1], &DataSet[j], sizeof(DataSet[0]) * (i - j));
				DataSet[j] = value;
				break;
			}
		}
	}
}

int main(void) {
	int DataSet[] = { 6, 4, 2, 3, 1, 5 };
	int Length = sizeof DataSet / sizeof DataSet[0];
	int i = 0;

	InsertionSort(DataSet, Length);
	for (i = 0; i < Length; i++) {
		printf("%d", DataSet[i]);
	}

	printf("\n");

	return 0;
}