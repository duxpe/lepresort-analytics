#include "leprechaun.h"
#include "utils.h"
#include <stdio.h>


void main(){
    //TODO: Get rid of all this test crap and do the actual menu!

    printf("Hi, this is a test menu! We must yet implement a cool more useful menu :)");

    int array[] = {6,5,3,4,7,8,9,2,1,0};
    int menu = 0;
    int size = get_array_length(sizeof(array), sizeof(array[0]));
    
    printf("This is an unsorted array :( \n");
    print_array(array, size);

    TAnalyticsData anData = {0,0,0,0};

    printf("Select an algorithm to sort it: \n 1-Selection Sort \n 2-Bubble Sort \n 3-Insertion Sort \n 4-Merge Sort \n 5-Quick Sort \n");
    scanf("%d", &menu);

    switch(menu){
        case 1:
            and_selection_sort(array,10,&anData);
            break;
        case 2:
            break;
        case 3:
            and_insertion_sort(array,10,&anData);
            break;
        case 4:
            break;
        case 5:
            and_quick_sort(array,0,9,&anData);
            break;
        default:
            printf("Invalid option selected, so im using using quick sort instead \n");
            and_quick_sort(array,0,9,&anData);
    }

    printf("Hey! A sorted array :) \n");
    print_array(array, size);

    printf("c: %d, s: %d \n", anData.comparisonCount, anData.swapCount);
}