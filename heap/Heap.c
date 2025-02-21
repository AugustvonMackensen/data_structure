#include "Heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Heap* HEAP_Create(int InitialSize) {
    Heap* NewHeap = (Heap*)malloc(sizeof(Heap));
    if (NewHeap == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    NewHeap->Capacity = InitialSize;
    NewHeap->UsedSize = 0;
    NewHeap->Nodes = (HeapNode*)malloc(sizeof(HeapNode) * NewHeap->Capacity);
    if (NewHeap->Nodes == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        free(NewHeap);
        exit(EXIT_FAILURE);
    }

    printf("size: %d\n", (int)sizeof(HeapNode));

    return NewHeap;
}

void HEAP_Destroy(Heap* H) {
    if (H != NULL) {
        if (H->Nodes != NULL) {
            free(H->Nodes);
        }
        free(H);
    }
}

void HEAP_Insert(Heap* H, ElementType NewData) {
    if (H == NULL || H->Nodes == NULL) {
        return;
    }

    int CurrentPosition = H->UsedSize;
    int ParentPosition = HEAP_GetParent(CurrentPosition);

    if (H->UsedSize == H->Capacity) {
        H->Capacity *= 2; // UsedSize가 Capacity에 도달하면 2배로 늘림
        // realloc(): 메모리 축소 및 확장시 사용
        HeapNode* TempNodes = (HeapNode*)realloc(H->Nodes, sizeof(HeapNode) * H->Capacity);
        if (TempNodes == NULL) {
            fprintf(stderr, "메모리 할당 실패\n");
            exit(EXIT_FAILURE);
        }
        H->Nodes = TempNodes;
    }

    H->Nodes[CurrentPosition].Data = NewData;

    // 후속처리
    while (CurrentPosition > 0 && H->Nodes[CurrentPosition].Data < H->Nodes[ParentPosition].Data) {
        HEAP_SwapNodes(H, CurrentPosition, ParentPosition);

        CurrentPosition = ParentPosition;
        ParentPosition = HEAP_GetParent(CurrentPosition);
    }

    H->UsedSize++;
}

void HEAP_SwapNodes(Heap* H, int Index1, int Index2) {
    if (H == NULL || H->Nodes == NULL || Index1 >= H->UsedSize || Index2 >= H->UsedSize) {
        return;
    }

    int CopySize = sizeof(HeapNode);
    HeapNode* Temp = (HeapNode*)malloc(CopySize);

    memcpy(Temp, &H->Nodes[Index1], CopySize);
    memcpy(&H->Nodes[Index1], &H->Nodes[Index2], CopySize);
    memcpy(&H->Nodes[Index2], Temp, CopySize);
}

void HEAP_Delete(Heap* H, HeapNode* Root) {
    if (H == NULL || Root == NULL || H->Nodes == NULL || H->UsedSize == 0) {
        return;
    }

    int ParentPosition = 0;
    int LeftPosition = 0;
    int RightPosition = 0;

    memcpy(Root, &H->Nodes[0], sizeof(HeapNode));
    memset(&H->Nodes[0], 0, sizeof(HeapNode)); // memset(): 메모리 초기화 함수

    H->UsedSize--;
    HEAP_SwapNodes(H, 0, H->UsedSize); // 최고 깊이 우측 노드를 루트 노드로 가지고 옴

    LeftPosition = HEAP_GetLeftChild(0);
    RightPosition = LeftPosition + 1;

    while (1) {
        int SelectedChild = 0;

        if (LeftPosition >= H->UsedSize)
            break;
        if (RightPosition >= H->UsedSize) {
            SelectedChild = LeftPosition;
        }
        else {
            if (H->Nodes[LeftPosition].Data > H->Nodes[RightPosition].Data)
                SelectedChild = RightPosition;
            else
                SelectedChild = LeftPosition;
        }

        if (H->Nodes[SelectedChild].Data < H->Nodes[ParentPosition].Data) {
            HEAP_SwapNodes(H, ParentPosition, SelectedChild);
            ParentPosition = SelectedChild;
        }
        else
            break;

        LeftPosition = HEAP_GetLeftChild(ParentPosition);
        RightPosition = LeftPosition + 1;
    }

    if (H->UsedSize < (H->Capacity / 2)) {
        H->Capacity /= 2;
        HeapNode* TempNodes = (HeapNode*)realloc(H->Nodes, sizeof(HeapNode) * H->Capacity);
        if (TempNodes != NULL) {
            H->Nodes = TempNodes;
        }
        else {
            // realloc 실패 시 메모리 부족 경고
            fprintf(stderr, "메모리 부족: realloc 실패\n");
            exit(EXIT_FAILURE);
        }
    }
}

int HEAP_GetParent(int Index) {
    return (int)((Index - 1) / 2);
}

int HEAP_GetLeftChild(int Index) {
    return (2 * Index) + 1;
}

void HEAP_PrintNodes(Heap* H) {
    if (H == NULL || H->Nodes == NULL) {
        return;
    }

    for (int i = 0; i < H->UsedSize; i++) {
        printf("%d ", H->Nodes[i].Data);
    }
    printf("\n");
}