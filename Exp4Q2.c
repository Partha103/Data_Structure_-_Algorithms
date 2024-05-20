#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_LINE_LENGTH 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

int lcs_length(char X[], char Y[]) {
    int m = strlen(X);
    int n = strlen(Y);
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[m][n];
}

void find_present_students(char master_list[][MAX_NAME_LENGTH], int master_count, char attendance_list[][MAX_NAME_LENGTH], int attendance_count, float threshold, FILE *output_file) {
    for (int i = 0; i < master_count; i++) {
        for (int j = 0; j < attendance_count; j++) {
            int lcs_len = lcs_length(master_list[i], attendance_list[j]);
            float similarity = (float) lcs_len / max(strlen(master_list[i]), strlen(attendance_list[j]));
            if (similarity >= threshold) {
                fprintf(output_file, "%s\n", master_list[i]);
                break;
            }
        }
    }
}

int main() {
    char MasterList[MAX_STUDENTS][MAX_NAME_LENGTH];
    char OnlineAttendance[MAX_STUDENTS][MAX_NAME_LENGTH];

    
    FILE *master_file = fopen("MasterList.csv", "r");
    if (master_file == NULL) {
        printf("Error: Unable to open MasterList.csv\n");
        return 1;
    }
    int master_count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), master_file) != NULL && master_count < MAX_STUDENTS) {
        line[strcspn(line, "\n")] = '\0'; // Remove trailing newline character
        strcpy(MasterList[master_count], line);
        master_count++;
    }
    fclose(master_file);
    FILE *attendance_file = fopen("OnlineAttendance.csv", "r");
    if (attendance_file == NULL) {
        printf("Error: Unable to open OnlineAttendance.csv\n");
        return 1;
    }
    int attendance_count = 0;
    while (fgets(line, sizeof(line), attendance_file) != NULL && attendance_count < MAX_STUDENTS) {
        line[strcspn(line, "\n")] = '\0'; // Remove trailing newline character
        strcpy(OnlineAttendance[attendance_count], line);
        attendance_count++;
    }
    fclose(attendance_file);

    float threshold = 0.8;

    FILE *output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Error: Unable to open present.txt\n");
        return 1;
    }

    find_present_students(MasterList, master_count, OnlineAttendance, attendance_count, threshold, output_file);

    // Close output file
    fclose(output_file);

    printf("Present students written to output.txt\n");

    return 0;
}