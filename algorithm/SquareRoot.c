#include<stdio.h>

double SquareRoot(int num) {
	//x^2 = num을 만족하는 x를 찾는 문제
	double x = 1.0; //초기값을 1로 설정
	double next_x = 0.0; // 다음 x값을 저장할 변수
	double diff = 0.0; // x와 next_x의 차이를 저장할 변수

	// num의 제곱근을 찾을때까지 반복
	while (1) {
		next_x = 0.5 * (x + num / x); // 방정식을 간소화
		diff = next_x - x; // x와 next_x의 차이 계산
		if (diff < 0.0000001 && diff > -0.0000001) // 차이가 0에 가까우면 반복문 종료
			break;
		x = next_x; // x값을 next_x값으로 갱신
	}

	return next_x; // 제곱근 반환
}

int main(void) {

	printf("%d의 제곱근 : %.3f\n", 2, SquareRoot(2));
	return 0;
}