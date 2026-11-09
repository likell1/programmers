#include <stdio.h>
#include <stdlib.h>


void merge(int A[], int tmp[], int lo, int mid, int hi) {
    int i = lo, j = mid, k = lo;


    // Finger Algorithm
    while (i < mid && j < hi) {          
        if (A[i] <= A[j]) 
            tmp[k++] = A[i++];
        else 
            tmp[k++] = A[j++];
    }

    //왼쪽 or 오른쪽 중 한 쪽 배열에서 원소가 다 빠져나감
    while (i < mid) tmp[k++] = A[i++];  
    while (j < hi) tmp[k++] = A[j++];  

    for (int t = lo; t < hi; t++)     
        A[t] = tmp[t];
}

void merge_sort(int A[], int tmp[], int lo, int hi) {   // [lo, hi) 구간 정렬
    if (hi - lo <= 1) return;                // 원소가 1개 이하면 이미 정렬됨

    int mid = (lo + hi)/2;                  // 구간을 반으로 나누는 경계

    merge_sort(A, tmp, lo, mid);        // 왼쪽 절반 정렬
    merge_sort(A, tmp, mid, hi);        // 오른쪽 절반 정렬
    merge(A, tmp, lo, mid, hi);           // 정렬된 두 절반 합치기 (지금 함수 그대로)
}


int main(void){

    int n = 0;
    scanf("%d", &n);

    int* A = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++){
        scanf("%d", &A[i]);
    }

    int* tmp = malloc(n * sizeof(int));
    
    merge_sort(A, tmp, 0, n);

    for (int i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");

    free(A);
    free(tmp);

    return 0;
}
