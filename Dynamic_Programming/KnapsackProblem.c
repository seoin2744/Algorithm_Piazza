#include <stdio.h>
#include <stdlib.h>

int main() {
    int items = 8;
    int weights[] = {5,10,8,7,4,6,3,9};
    int values[]  = {20,40,35,25,15,30,10,50};
    int capacity = 50;

    int **dp = (int**)malloc((items+1)*sizeof(int*));
    for(int i=0; i<=items; i++){
        dp[i] = (int*)malloc((capacity+1)*sizeof(int));
    }
    
    for(int i=0; i<=items; i++){
        for(int j=0; j<=capacity; j++){
            dp[i][j] = 0;
        }
    }

    for(int i=1; i<=items; i++){
        int curr_weight = weights[i-1];
        int curr_value = values[i-1];
        for(int w=1; w<=capacity; w++){
            if(w < curr_weight){
                dp[i][w] = dp[i-1][w];
            } else {
                int val_including = dp[i-1][w - curr_weight] + curr_value;
                int val_excluding = dp[i-1][w];
                dp[i][w] = (val_including > val_excluding) ? val_including : val_excluding;
            }
        }
    }

    int max_value = dp[items][capacity];

    int *selected_items = (int*)malloc(items*sizeof(int));
    int count = 0;
    int w = capacity;
    for(int i=items; i>0; i--){
        if(dp[i][w] != dp[i-1][w]) {
            selected_items[count++] = i-1;
            w -= weights[i-1];
        }
    }

    printf("Max Value: %d\n", max_value);
    printf("Selected Items (index): ");
    for(int i = 0; i < count; i++){
        printf("%d ", selected_items[i]);
    }
    printf("\n");

    for(int i=0; i<=items; i++){
        free(dp[i]);
    }
    free(dp);
    free(selected_items);

    return 0;
}
