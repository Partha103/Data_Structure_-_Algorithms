#include <stdio.h>
#define N 10           
#define M 50   
#define P 8         
void set_grade(int student_grades[N][M][P], int cls, int st, int sub, int grade) {
    student_grades[cls][st][sub] = grade;
}
int get_grade(int student_grades[N][M][P], int cls, int st, int sub) {
    return student_grades[cls][st][sub];
}
int main() {
    int student_grades[N][M][P] = {0};

    int cls, st, sub, grade;

    printf("Enter class index (1-%d): ", N);
    scanf("%d", &cls);
    printf("Enter roll number of student (1-%d): ", M);
    scanf("%d", &st);
    printf("Enter subject_code (0-%d): ", P - 1);
    scanf("%d", &sub);
    printf("Enter grade: ");
    scanf("%d", &grade);

    if (cls >= 0 && cls < N &&
        st >= 0 && st < M &&
        sub >= 0 && sub < P) {
        
        set_grade(student_grades, cls, st, sub, grade);
        printf("Grade set successfully.\n");
        printf("Enter class index (0-%d): ", N - 1);
        scanf("%d", &cls);
        printf("Enter roll number of student (0-%d): ", M - 1);
        scanf("%d", &st);
        printf("Enter subject_code (0-%d): ", P - 1);
        scanf("%d", &sub);

        if (cls >= 0 && cls < N &&
            st >= 0 && st < M &&
            sub >= 0 && sub < P) {

            int retrieved_grade = get_grade(student_grades, cls, st, sub);
            printf("Retrieved grade: %d\n", retrieved_grade);
        } else {
            printf("Invalid indices for retrieving grade.\n");
        }
    } else {
        printf("Invalid indices for setting grade.\n");
    }
    return 0;
}
