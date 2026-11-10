#include <stdio.h>
#include <stdlib.h>


void merge(int A[], int tmp[], int lo, int mid, int hi) {
    int i = lo, j = mid, k = lo;

    while (i < mid && j < hi) {          
        if (A[i] <= A[j]) 
            tmp[k++] = A[i++];
        else 
            tmp[k++] = A[j++];
    }
    while (i < mid) tmp[k++] = A[i++];  
    while (j < hi) tmp[k++] = A[j++];  

    for (int t = lo; t < hi; t++)     
        A[t] = tmp[t];
}


int main(void){

    int n = 0;
    scanf("%d", &n);

    int* A = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++){
        scanf("%d", &A[i]);
    }

    int* tmp = malloc(n * sizeof(int));
    
    
    for (int width=1; width<n; width*=2){
        for (int lo = 0; lo < n; lo+= 2*width){
            int mid = lo + width;
            int hi = lo + 2*width;

            // n이 2의 거듭제곱이 아닌경우
            if (mid >= n) break;
            if (hi > n) hi = n;

            merge(A, tmp, lo, mid, hi);
        }
    }
    for (int i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
    

    return 0;
}
