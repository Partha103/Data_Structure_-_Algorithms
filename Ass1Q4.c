#include <stdio.h>

int main() {
    int test_scores[] = {85, 78, 92, 65, 89, 76, 94, 81, 87, 90, 72, 88, 95, 79, 83, 91, 70, 84, 86, 93};
    int size = sizeof(test_scores) / sizeof(test_scores[0]);
    int sum = 0,i;
    int highest_score = test_scores[0];
    for (i = 0; i < size; i++) {
        sum += test_scores[i];
        if (test_scores[i] > highest_score) {
            highest_score = test_scores[i];
        }
    }
    float average_score = (float)sum / size;
    int passing_threshold = 70;
    int passed_count = 0;
    int failed_count = 0;
    for (i = 0; i < size; i++) {
        if (test_scores[i] >= passing_threshold) {
            passed_count++;
        } else {
            failed_count++;
        }
    }
    int grade_counts[5] = {0};
    for (i = 0; i < size; i++) {
        int score = test_scores[i];
        if (score >= 95) {
            grade_counts[0]++;
        } else if (score >= 90) {
            grade_counts[1]++;
        } else if (score >= 80) {
            grade_counts[2]++;
        } else if (score >= 70) {
            grade_counts[3]++;
        } else {
            grade_counts[4]++;
        }
    }
    printf("Average Score: %.2f\n", average_score);
    printf("Highest Score: %d\n", highest_score);
    printf("Number of Students Passed: %d\n", passed_count);
    printf("Number of Students Failed: %d\n", failed_count);
    printf("Grade Distribution:\n");
    printf("O: %d\n", grade_counts[0]);
    printf("E: %d\n", grade_counts[1]);
    printf("A: %d\n", grade_counts[2]);
    printf("B: %d\n", grade_counts[3]);
    printf("F: %d\n", grade_counts[4]);
    return 0;
}
