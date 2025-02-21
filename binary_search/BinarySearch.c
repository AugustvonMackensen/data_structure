#include <stdlib.h>
#include <stdio.h>
#include "Point.h"

Point* BinarySearch(Point PointList[], int Size, double Target) {
	//검색 결과를 반환해야 하므로 Point*를 반환. 검색 대상이 없을때는 NULL을 반호나해야함.
	int Left, Right, Mid;
	Left = 0;
	Right = Size - 1;
	while (Left <= Right) {
		Mid = (Left + Right) / 2;

		if (Target == PointList[Mid].point)
			return &(PointList[Mid]);
		else if (Target > PointList[Mid].point)
			Left = Mid + 1;
		else
			Right = Mid - 1;
	}

	return NULL;
}

int ComparePoint(const void* _elem1, const void* _elem2) {
	Point* elem1 = (Point*)_elem1;
	Point* elem2 = (Point*)_elem2;

	if (elem1->point > elem2->point)
		return 1;
	else if (elem1->point < elem2->point)
		return -1;
	else
		return 0;
}

int main(void) {
	int Length = sizeof DataSet / sizeof DataSet[0];
	Point* found = NULL;

	//구매포인트에 대해 오름차순 정렬
	qsort((void*)DataSet, Length, sizeof(Point), ComparePoint);


	// 구매포인트가 671.78인 고객을 검색
	found = BinarySearch(DataSet, Length, 671.78);

	printf("found.. ID : %d, Point : %f\n", found->id, found->point);

	return 0;
}