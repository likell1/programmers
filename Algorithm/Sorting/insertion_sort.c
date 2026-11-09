#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int swaps = 0;
int* ptr_swaps = &swaps;

void swap(int* pi, int* pj){
    int temp = 0;
    temp = *pi;
    *pi = *pj;
    *pj = temp;
}

void compare(int A[], int j){
    while (j>0 && A[j-1] > A[j]){
        swap(&A[j-1], &A[j]);
        *ptr_swaps += 1;
        j--;
        compare(A, j);
    }

}

long long insertion_sort(int A[], int n) {   // 정렬하고 swap 횟수를 반환

    for (int i = 1; i<n; i++){
        compare(A, i);
    }
        
    return *ptr_swaps;
    }

int main(void){

    int n = 0;
    scanf("%d", &n);

    int* A = malloc(n * sizeof(int));


    for(int i=0; i<n; i++){
        scanf("%d", &A[i]);
    }

    int result = insertion_sort(A, n);

    for (int i = 0; i<n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
    printf("swaps = %d\n", result);

    free(A);
    return 0;
}
