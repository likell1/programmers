#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int swaps = 0;
int* ptr_swaps = &swaps;

long long insertion_sort_cmp(int A[], int n);         // 원소 비교 횟수 반환
long long binary_insertion_sort_cmp(int A[], int n);  // 원소 비교 횟수 반환

void shift(int A[], int start, int end){
    while (start < end) {
        A[end] = A[end-1];
        end--;
        *ptr_swaps += 1;
    }
}

void insert(int A[], int x, int key, int end){
    shift(A, x, end);
    A[x] = key;
}

int binary_search(int A[], int idx, int key){
    int l = 0; int r = idx;
    
    while (l<r){
        int mid = (l+r) / 2;
        if (key < A[mid]){
            r = mid;
        } 
        else {
            l = mid+1; }
    }
    return l;
}


int main(void) {

    int n = 0; int idx = 0;
    scanf("%d", &n);

    int* A = malloc(n * sizeof(int));  //동적배열 할당
    if (A == NULL) return 1;
    
    for (int i = 0; i < n; i++){  //입력
        scanf("%d", &A[i]);
    }

    for (int i = 1; i < n; i++) {  //정렬
        idx = binary_search(A, i, A[i]);
        insert(A, idx, A[i], i);
        }
        

    for (int i = 0; i<n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
    printf("swaps = %d\n", *ptr_swaps);


    return 0;
}