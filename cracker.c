#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <float.h>
#define MAX_LEN 1000000

int read_distribution(char *filename, double distribution[26]);
void compute_histogram(char *text, double histogram[26]);
double chi_square_distance(double observed[26], double expected[26]);
void encrypt(char *input, int shift, char *output);
void decrypt(char *input, int shift, char *output);
int break_code(char *input, char *output, double expected[26]);

int read_distribution(char *filename, double distribution[26])
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return -1;
    }

    int i = 0;
    while (i < 26 && fscanf(fp, "%lf", &distribution[i]) == 1)
    {
        i++;
    }
    fclose(fp);
    return (i == 26) ? 0 : 1;
}

void compute_histogram(char *text, double histogram[26])
{
    int cnt[26] = {0};
    int total = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        char ch = text[i];
        if (isalpha(ch))
        {
            ch = tolower(ch);
            cnt[ch - 'a']++;
            total++;
        }
    }
    for (int i = 0; i < 26; i++)
    {
        histogram[i] = (total > 0) ? (double)1.0 * cnt[i] / total : 0.0;
    }
}

double chi_square_distance(double observed[26], double expected[26])
{
    double chi2 = 0;
    for (int i = 0; i < 26; i++)
    {
        if (expected[i] > 0)
        {
            double diff = observed[i] - expected[i];
            chi2 += (double)(diff * diff) / expected[i];
        }
    }
    return chi2;
}

void encrypt(char *input, int shift, char *output)
{
    int i;
    for (i = 0; input[i] != '\0'; i++)
    {
        char ch = input[i];
        if (isalpha(ch))
        {
            if (islower(ch))
            {
                output[i] = 'a' + ((ch - 'a' + shift) % 26 + 26) % 26;
            }
            else
            {
                output[i] = 'A' + ((ch - 'A' + shift) % 26 + 26) % 26;
            }
        }
        else
        {
            output[i] = ch;
        }
    }
    output[i] = '\0';
}

void decrypt(char *input, int shift, char *output)
{
    encrypt(input, 26 - shift, output);
}

int break_code(char *input, char *output, double expected[26])
{
    double min_dist = FLT_MAX;
    int best_shift = 0;
    char D[MAX_LEN];

    for (int shift = 0; shift < 26; shift++)
    {
        decrypt(input, shift, D);
        double hist[26];
        compute_histogram(D, hist);
        double dist = chi_square_distance(hist, expected);
        if (dist < min_dist)
        {
            min_dist = dist;
            best_shift = shift;
            strcpy(output, D);
        }
    }
    return best_shift;
}

int main()
{

    double english_dist[26];
    if (read_distribution("distribution.txt", english_dist) != 0)
    {
        printf("Error reading the distributions file.");
        return 1;
    }

    int choice;
    char input_text[MAX_LEN];
    char output_text[MAX_LEN];
    int shift;

    while (1)
    {
        printf("\n=== Caesar Cipher Menu ===\n");
        printf("1. Encrypt a message using Caesar cipher\n");
        printf("2. Decrypt a message using shift\n");
        printf("3. Decrypt a message using frequency analysis\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Exiting.\n");
            break;
        }
        getchar();

        if (choice == 1)
        {
            printf("Enter the messag to encrypt: ");
            if (fgets(input_text, MAX_LEN, stdin) == NULL)
                continue;
            input_text[strcspn(input_text, "\n")] = '\0';

            printf("Enter the shift (0-25): ");
            if (scanf("%d", &shift) != 1)
            {
                printf("Invalid shift.\n");
                getchar();
                continue;
            }
            getchar();

            encrypt(input_text, shift, output_text);
            printf("Encrypted message: %s\n", output_text);
        }
        else if (choice == 2)
        {
            printf("Enter the ciphertext to decrypt: ");
            if (fgets(input_text, MAX_LEN, stdin) == NULL)
                continue;
            input_text[strcspn(input_text, "\n")] = '\0';
            printf("Enter the shift (0-25): ");
            if (scanf("%d", &shift) != 1)
            {
                printf("Invalid shift.\n");
                getchar();
                continue;
            }
            getchar();

            decrypt(input_text, shift, output_text);
            printf("Decrypted message: %s\n", output_text);
        }
        else if (choice == 3)
        {
            printf("Enter the ciphertext to decrypt: ");
            if (fgets(input_text, MAX_LEN, stdin) == NULL)
                continue;
            input_text[strcspn(input_text, "\n")] = '\0';
            int detected_shift = break_code(input_text, output_text, english_dist);
            printf("Decrypted message: %s\n", output_text);
            printf("Detected shift: %d\n", detected_shift);
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            printf("Invalid input.");
        }
    }
    return 0;
}