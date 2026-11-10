#include <stdio.h>
#include <stdlib.h>

void swap(int* pa, int* pb){
    int temp = 0;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

int max_heapify(int A[], int heap_size, int i) {

    int swaps = 0;
    while (1) {
        int l = 2*i + 1; int r = 2*i + 2; int largest = i;

        //왼쪽 child가 더 큰 경우
        if (l < heap_size && A[l] > A[largest]){
            largest = l;
        }
        //오른쪽 child가 더 큰 경우
        if (r < heap_size && A[r] > A[largest]){
            largest = r;
        }
        // 부모가 이미 최댓값
        if (largest == i){
            break;
        }
        swap(&A[i], &A[largest]); swaps++;
        i = largest;
        
    }
    return swaps;
}

int build_max_heap(int A[], int n){
    
    int total_swaps = 0;
    for(int i = n/2 -1; i >= 0; i--){
        total_swaps += max_heapify(A, n, i);
    }

    return total_swaps;
}

int main(void){

    int n = 0;
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        scanf("%d", &A[i]);
    }

    int swaps = build_max_heap(A, n);

    for (int i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");

    printf("swaps = %d\n", swaps);

    free(A);
    return 0;
}
