#include "SimpleHashTable.h"

//구조체 변수를 활용하여 구조체 변수를 사용할때는, 도트연산자를 사용
//포인터를 사용하여 구조체 원소에 접근할때는 화살표를 사용해서 값을 할당함.

HashTable* SHT_CreateHashTable(int TableSize) {
	HashTable* HT = (HashTable*)malloc(sizeof(HashTable));
	HT->Table = (Node*)malloc(sizeof(Node) * TableSize);
	HT->TableSize = TableSize;

	return HT;
}

void SHT_Set(HashTable* HT, KeyType Key, ValueType Value) {
	int Address = SHT_Hash(Key, HT->TableSize);

	HT->Table[Address].Key = Key;
	HT->Table[Address].Value = Value;
}

ValueType SHT_Get(HashTable* HT, KeyType Key) {
	int Address = SHT_Hash(Key, HT->TableSize);

	return HT->Table[Address].Value;
}

void SHT_DestroyHashTable(HashTable* HT) {
	//free() : 동적으로 할당된 메모리 해제
	free(HT->Table);
	free(HT);
}

int SHT_Hash(KeyType Key, int TableSize) {
	return Key % TableSize;
}