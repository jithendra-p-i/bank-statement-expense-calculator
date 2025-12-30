#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILENAME "statement.txt"

void hdfc_card_total_spend(double *total, char *month_arg, char* year_arg)
{
    FILE *fp = NULL;
    int i = 0;
    char line[1024] = {0};

    //open the file for reading
    fp = fopen(FILENAME,"r");
    if(fp == NULL) {
        printf("Failed to open %s\n",FILENAME);
    }
    //line by line read
    while(fgets(line, sizeof(line), fp)) {
        
        int day = 0, year = 0, n = 0, j = 0;
        char month[4] = {0};
        char year_str[5] = {0};
        char drcr[3] = {0};
        char amount_str[32] = {0};
        char tmp[32] = {0};
        /*
            Expected Format
            27-Jan-2025  MORE BANGALORE  194.00  DR
        */
        n = sscanf(line, "%d-%3s-%d %*[^0-9] %31s %2s", &day, month, &year, amount_str, drcr);
        if(n != 5) continue;
        for(i = 0;amount_str[i];i++)
        {
            if(amount_str[i] != ',')
                tmp[j++] = amount_str[i];
        }
        tmp[j] = '\0';
        snprintf(year_str, sizeof(year_str), "%d", year);
        double amount = atof(tmp);
        if(strcmp(drcr, "DR") == 0) {
            if((strcmp(month, month_arg) == 0) && (strcmp(year_str, year_arg) == 0))
                *total += amount;
        }
    }
    fclose(fp);
}

int main(int argc, char *argv[])
{
    int status = 0;
    char cmd[128] = {0};
    double total = 0.0;
    int opt;
    char *bank = NULL;
    char *password = NULL;
    char *month = NULL;
    char *year = NULL;
    char *pdf_filename = NULL;

    while((opt = getopt(argc, argv, "b:p:m:y:n:")) != -1){
        switch(opt) {
            case 'b':
                bank = optarg;
                break;
            case 'p':
                password = optarg;
                break;
            case 'm':
                month = optarg;
                break;
            case 'y':
                year = optarg;
                break;
            case 'n':
                pdf_filename = optarg;
                break;
            default:
                printf("Usage: %s -b Bank Name -p Password -m Month -y Year -n Filename\n \
                        Bank name  - e.g HDFC, ICIC etc... \n \
                        password   - For HDFC First 4 letter of name + last 4 digits of card\n \
                        Month      - e.g Jan, Feb etc...\n \
                        Year       - e.g 2024, 2025 \n \
                        Filename   - Name of bank statement PDF\n",
                    argv[0]);
                exit(EXIT_FAILURE);

        }
    }
    if(!bank || !password || !month || !pdf_filename ||!year) {
        printf("Missing arguments\n \
            Usage: %s -b BANK -p PASSWORD -m MONTH -y Year -n FILE.pdf\n \
            Bank name  - e.g HDFC, ICIC etc... \n \
            password   - For HDFC First 4 letter of name + last 4 digits of card\n \
            Month      - e.g Jan, Feb etc... \n \
            Year       - e.g 2024, 2025 \n \
            Filename   - Name of bank statement PDF\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    snprintf(cmd, sizeof(cmd), "pdftotext -layout -upw %s %s %s", password, pdf_filename ,FILENAME);
    status = system(cmd); 
    if(status != 0){
        printf("Failed to convert PDF to txt file %d\n",status);
        return 0;
    }
    if(strcmp(bank, "HDFC") == 0) {
        hdfc_card_total_spend(&total, month, year);
    }   
    printf("Total Expense of Month %s is %.2f\n",month, total); 
    
    return 0;
}