#include <stdio.h>

int main() {
    int temperature_data[] = {25, 28, 27, 30, 31, 29, 26};
    int size = sizeof(temperature_data) / sizeof(temperature_data[0]);
    int sum = 0,i;
    for (i = 0; i < size; i++) {
        sum += temperature_data[i];
    }
    float average_temperature = (float)sum / size;
    int hottest_day = temperature_data[0];
    int coldest_day = temperature_data[0];
    for (i = 1; i < size; i++) {
        if (temperature_data[i] > hottest_day) {
            hottest_day = temperature_data[i];
        }
        if (temperature_data[i] < coldest_day) {
            coldest_day = temperature_data[i];
        }
    }
    int temperature_range = hottest_day - coldest_day;
    printf("Average Temperature: %.2f\n", average_temperature);
    printf("Hottest Day: %d\n", hottest_day);
    printf("Coldest Day: %d\n", coldest_day);
    printf("Temperature Range: %d\n", temperature_range);

    return 0;
}
