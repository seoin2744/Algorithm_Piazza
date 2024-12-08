#include <stdio.h>
#include <stdlib.h>

void sort_jobs(int *jobs, int n, int ascending) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((ascending && jobs[j] > jobs[j + 1]) || (!ascending && jobs[j] < jobs[j + 1])) {
                int temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }
}

int find_min_processor(int *processor_times, int num_processors) {
    int min_index = 0;
    for (int i = 1; i < num_processors; i++) {
        if (processor_times[i] < processor_times[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}

void schedule_jobs(int *jobs, int n, int num_processors, int ascending) {
    int processor_queues[num_processors][n];
    int processor_sizes[num_processors];
    int processor_times[num_processors];

    for (int i = 0; i < num_processors; i++) {
        processor_sizes[i] = 0;
        processor_times[i] = 0;
    }

    sort_jobs(jobs, n, ascending);

    for (int i = 0; i < n; i++) {
        int min_processor = find_min_processor(processor_times, num_processors);
        processor_queues[min_processor][processor_sizes[min_processor]++] = jobs[i];
        processor_times[min_processor] += jobs[i];
    }

    printf(ascending ? "Shortest Job First (SJF):\n" : "Longest Job First (LJF):\n");
    for (int i = 0; i < num_processors; i++) {
        printf("Processor %d: [", i + 1);
        for (int j = 0; j < processor_sizes[i]; j++) {
            printf("%d", processor_queues[i][j]);
            if (j < processor_sizes[i] - 1) printf(", ");
        }
        printf("] Total Time: %d\n", processor_times[i]);
    }
}

int main() {
    int jobs[] = {7, 12, 15, 9, 14, 6, 8, 10, 18, 11, 20, 13, 5, 16, 22, 4, 19, 25, 17, 21};
    int n = sizeof(jobs) / sizeof(jobs[0]);
    int num_processors = 3;

    schedule_jobs(jobs, n, num_processors, 1);

    printf("\n");

    schedule_jobs(jobs, n, num_processors, 0);

    return 0;
}
