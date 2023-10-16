#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sale {
    double value;
    char month[20];
};

double avg(struct Sale sales[], int size, int start, int stop)
{
    double sum = 0.0;
    for (int i = start; i < stop; i++)
    {
        sum += sales[i].value;
    }

    return (sum / (double)(stop-start));
}

struct Sale min(struct Sale sales[], int size)
{
    struct Sale _min = sales[0];
    for (int i = 0; i < size; i++)
    {
        if (sales[i].value < _min.value)
        {
            _min.value = sales[i].value;
            // Copy the month 
            for (int j = 0; j < 20; j++)
            {
                _min.month[j] = sales[i].month[j];
            }
        }
    }

    return _min;
}

struct Sale max(struct Sale sales[], int size)
{
    struct Sale _max = sales[0];
    for (int i = 0; i < size; i++)
    {
        if (&sales[i] == NULL)
        {
            continue;
        }
        if (sales[i].value > _max.value)
        {
            _max.value = sales[i].value;

            // Copy the month 
            for (int j = 0; j < 20; j++)
            {
                _max.month[j] = sales[i].month[j];
            }
        }
    }

    return _max;
}

int compareSales(const void *a, const void *b) {
    double valueA = ((struct Sale *)a)->value;
    double valueB = ((struct Sale *)b)->value;
    
    if (valueA < valueB) return 1;  // We want descending order, so swap the return values
    if (valueA > valueB) return -1;
    return 0;
}

void sortSales(struct Sale *sales, size_t n) {
    qsort(sales, n, sizeof(struct Sale), compareSales);
}

/*
struct Sale * sort(struct Sale sales[], int size)
{
    struct Sale _max;
    struct Sale _sorted[12];
    struct Sale _salesCopy[size];
    int newSize = size;

    // Copy struct
    for (int i = 0; i < size; i++)
    {
        _salesCopy[i] = sales[i];
    }
    
    for (int i = 0; i < size; i++)
    {
        struct Sale toSort[newSize];
        _max = max(sales, size);
        newSize--;
        // Place remaining values in 
        for (int j = 0; j < newSize; j++)
        {

        }
        _sorted[i] = _max;
    }

    return (_sorted);
}
*/

int main() 
{
    //-- DECLARATIONS --//
    FILE* file_ptr;
    char string[50];
    int counter = 0;
    int monthCounter = 0;
    char ch;
    char* endptr;
    struct Sale sales[12];
    char months[12][20] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    //-- INPUT --//
    file_ptr = fopen("input.txt", "r");
    while (!feof(file_ptr)) {

        ch = fgetc(file_ptr);
        if (ch != EOF){
            string[counter] = ch;
            counter++;
        }

        // On newline, append the value to the sales array and continue
        if (ch == '\n' || ch == EOF)
        {
            // Set sale value and month
            sales[monthCounter].value = strtod(string, &endptr);

            // Copy the month 
            for (int i = 0; i < 20; i++)
            {
                sales[monthCounter].month[i] = months[monthCounter][i];
            }

            // Clear string
            strcpy(string, "");

            // Reset and increment counters
            monthCounter++;
            counter = 0;
            continue;
        }

    }
    // Close the file once we're finished
    fclose(file_ptr);

    //-- CALCULATIONS --//
    struct Sale maximum;
    struct Sale minimum;
    double average;
    // Minimum
    minimum = min(sales, 12);

    // Maximum
    maximum = max(sales, 12);

    // Average
    average = avg(sales, 12, 0, 12);

    //-- PRINTING --//
    // Monthly Sales Report
    printf("\nMonthly Sales Report for 2022:\n");
    printf("%-8s \t\t %-8s\n", "Month", "Sales");
    for (int i = 0; i < 12; i++)
    {
        printf("%-8s \t\t $ %-8.2f\n", months[i], sales[i].value);
    }

    // Summary
    printf("\nMinimum sales: \t\t $ %-8.2f (%s)\n", minimum.value, minimum.month);
    printf("Maxmimum sales: \t\t $ %-8.2f (%s)\n", maximum.value, maximum.month);
    printf("Average sales: \t\t $ %-8.2f\n", average);

    // 6-Month Moving Average
    char startMonth[20];
    char endMonth[20];
    printf("\nSix-Month Moving Average Report: \n");
    for (int i = 0; i < 7; i++)
    {
        strcpy(startMonth, months[i]);
        strcpy(endMonth, months[i+5]);
        printf("%-8s \t - \t %-8s \t\t $%-8.2f\n", startMonth, endMonth, avg(sales, 12, i, i+6));
    }

    // Sorted Order
    printf("\nSales Report (Highest to Lowest)\n");
    printf("%8s \t\t %8s", "Month", "Sales\n");
    sortSales(sales, 12);
    for (int i = 0; i < 12; i++)
    {
        printf("%-10s \t\t $ %-10.2f", sales[i].month, sales[i].value);
        printf("\n");
    }
    
    return 0;
}