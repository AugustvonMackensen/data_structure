#include "Chaining.h"

HashTable* CHT_CreateHashTable(int TableSize) {
	HashTable* HT = (HashTable*)malloc(sizeof(TableSize));
	HT->Table = (List*)malloc(sizeof(Node) * TableSize);

	memset(HT->Table, 0, sizeof(List) * TableSize); // 메모리 초기화

	HT->TableSize = TableSize;

	return HT;
}

Node* CHT_CreateNode(KeyType Key, ValueType Value) {
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->Key = (char*)malloc(sizeof(char) * (strlen(Key) + 1));
	strcpy(NewNode->Key, Key);

	NewNode->Value = (char*)malloc(sizeof(char) * (strlen(Value) + 1));
	strcpy(NewNode->Value, Value);
	NewNode->Next = NULL;
	return NewNode;
}

void CHT_DestroyNode(Node* TheNode) {
	free(TheNode->Key);
	free(TheNode->Value);
	free(TheNode);
}

void CHT_Set(HashTable* HT, KeyType Key, ValueType Value){
	int Address = CHT_Hash(Key, strlen(Key), HT->TableSize);
	Node* NewNode = CHT_CreateNode(Key, Value);

	//해당 주소가 비어있는 경우
	if (HT->Table[Address] == NULL) {
		HT->Table[Address] = NewNode;
	}
	else {
		// 해당 주소가 비어있지 않은 경우
		List L = HT->Table[Address];
		NewNode->Next = L;
		HT->Table[Address] = NewNode;

		printf("Collision Occured : Key(% s), Address(% d) \n", Key, Address);
		
	}
}
ValueType CHT_Get(HashTable* HT, KeyType Key){
	// 주소 해싱
	int Address = CHT_Hash(Key, strlen(Key), HT->TableSize);

	//해싱한 주소에 있는 링크드 리스트 가져오기
	List TheList = HT->Table[Address];
	List Target = NULL;

	if (TheList == NULL) {
		return NULL;
	}

	//원하는 값 찾을때까지 순차 탐색
	while (1) {
		if (strcmp(TheList->Key, Key) == 0) {
			// 원하는 값을 찾은 경우
			Target = TheList;
			break;
		}

		//찾지 못한 경우 계속 찾는데, Next가 Null이면 반복문 종료.
		if (TheList->Next == NULL)
			break;
		else
			TheList = TheList->Next;
	}

	return Target->Value;
}

void CHT_DestroyList(List L) {
	if (L == NULL)
		return;
	
	if (L->Next != NULL)
		CHT_DestroyList(L->Next);

	CHT_DestroyNode(L);
}

void CHT_DestroyHashTable(HashTable* HT){
	// 1. 각 링크드 리스트를 자유 저장소에서 제거
	int i = 0;
	for (i = 0; i < HT->TableSize; i++) {
		List L = HT->Table[i];
		CHT_DestroyList(L);
	}

	//2. 해시 테이블을 자유 저장소에서 제거
	free(HT->Table);
	free(HT);
}


int CHT_Hash(KeyType Key, int KeyLength, int TableSize){
	int i=0;
	int HashValue = 0;

	for (i=0; i<KeyLength; i++) {
		//왼쪽 시프트 연산으로 3비트씩 왼쪽으로 민 뒤, 아스키 코드번호 더한다.
		HashValue = (HashValue << 3) + Key[i]; 
	}

	HashValue = HashValue % TableSize;

	return HashValue;
}
