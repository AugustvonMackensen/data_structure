#include<stdlib.h>
#include<stdio.h>
#include "Point.h"


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
	Point target;
	Point* found = NULL;

	//구매포인트에 대해 오름차순 정렬
	qsort((void*)DataSet, Length, sizeof(Point), ComparePoint);


	// 구매포인트가 671.78인 고객을 검색
	//bsearch()라는 c언어 함수로 이진탐색 알고리즘을 사용할 수 있다.
	//bsearch() :
	//const void* bsearch(const void* key, const void* base, size_t num, size_t size, int(*compare)(const void*, const void*));
	//key : 검색할 대상
	//base : 검색할 배열의 주소
	//num : 데이터 요소의 개수
	//width: 한 데이터 요소의 크기
	//int(*compare)(const void*, const void*) : 비교 함수에 대한 포인터
	target.id = 0;
	target.point = 671.78;
	found = bsearch((void*)&target, (void*)DataSet, Length, sizeof(Point), ComparePoint);

	printf("found.. ID : %d, Point : %f\n", found->id, found->point);

	return 0;
}