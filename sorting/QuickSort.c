#include<stdio.h>

void Swap(int* A, int* B) {
	int Temp = *A;
	*A = *B;
	*B = Temp;
}

int Partition(int DataSet[], int Left, int Right) {
	int First = Left;
	int Pivot = DataSet[First];

	++Left;

	while (Left <= Right) {
		//Left와 RIght은 양 끝에서부터 pivot보다 크거나 작은 요소를 탐색하는 것
		//두 변수가 만나면 while문 종료
		while (DataSet[Left] <= Pivot && Left < Right)
			++Left;

		while (DataSet[Right] > Pivot && Left <= Right)
			--Right;

		if (Left < Right)
			Swap(&DataSet[Left], &DataSet[Right]);
		else
			break;
	}

	//마지막에 기준 요소를 마지막 요소와 교체
	Swap(&DataSet[First], &DataSet[Right]);

	return Right; //새 기준이 될 요소의 위치 반환
}

void QuickSort(int DataSet[], int Left, int Right){
	if (Left < Right) {
		int Index = Partition(DataSet, Left, Right);

		//재귀로 호출함(반복되는 분할과정 처리)
		QuickSort(DataSet, Left, Index - 1);
		QuickSort(DataSet, Index + 1, Right);
	}
}

int main(void) {
	int DataSet[] = { 6,4,2,3,1,5 };
	int Length = sizeof DataSet / sizeof DataSet[0];
	int i = 0;

	QuickSort(DataSet, 0, Length - 1);

	for (int i = 0; i < Length; i++) {
		printf("%d", DataSet[i]);
	}

	printf("\n");

	return 0;
}