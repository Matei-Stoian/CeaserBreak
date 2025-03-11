#include "caeser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <ctype.h>

void read_distribution(const char *filename, double distribution[ALPHA])
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error reading the distibution file\n");
        exit(1);
    }

    for (int i = 0; i < ALPHA; i++)
    {
        if (fscanf(fp, "%lf", &distribution[i]) != 1)
        {
            printf("Error reading the distribution for the letter: %c", 'a' + i);
            fclose(fp);
            exit(1);
        }
    }
    fclose(fp);
}

void compute_histogram(const char *text, double histogram[ALPHA])
{
    int counter[ALPHA] = {0};
    int total = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            char c = tolower(text[i]);  // Convert to lowercase first
            counter[c - 'a']++;         // Now safe to use as index
            total++;
        }
    }
    for (int i = 0; i < ALPHA; i++)
    {
        histogram[i] = total > 0 ? (double)1.0 * counter[i] / total : 0.0;
    }
}

double chi_square_dist(const double hist1[ALPHA], const double hist2[ALPHA])
{
    double distance = 0.0;

    for (int i = 0; i < ALPHA; i++)
    {
        if (hist2[i] > 0)
        {
            double diff = hist1[i] - hist2[i];
            distance += (diff * diff) / hist2[i];
        }
    }
    return distance;
}

double euclidean_dist(const double hist1[ALPHA], const double hist2[ALPHA])
{
    double distance = 0.0;
    for (int i = 0; i < ALPHA; i++)
    {
        double diff = hist1[i] - hist2[i];
        distance += diff * diff;
    }
    return sqrt(distance);
}

double cosine_dist(const double hist1[ALPHA], const double hist2[ALPHA])
{
    double dotProd = 0.0;
    double sum1 = 0.0;
    double sum2 = 0.0;
    for (int i = 0; i < ALPHA; i++)
    {
        dotProd += (hist1[i] * hist2[i]);
        sum1 += hist1[i];
        sum2 += hist2[i];
    }
    return 1.0 - (double)(dotProd / (sqrt(sum1) * sqrt(sum2)));
}

void encrypt(const char *text, int shift, char *output)
{
    int i;
    shift = ((shift % 26) + 26) % 26; // Set the shift between 0 and 25 even if the input is negative or over 26

    for (i = 0; text[i] != '\0'; i++)
    {
        char ch = text[i];
        if (isalpha(ch))
        {
            char kase = islower(ch) ? 'a' : 'A';
            output[i] = kase + ((ch - kase + shift) % 26);
        }
        else
        {
            output[i] = ch;
        }
    }
    output[i] = '\0';
}

void decrypt(const char *text, int shift, char *output)
{
    encrypt(text, 26 - (shift % 26), output);
}

void break_chiper(const char *text, int top[3], double top_dist[3], double (*distamce_function)(const double[], const double[]))
{
    double english_distibution[ALPHA];
    read_distribution("distribution.txt", english_distibution);

    for (int i = 0; i < 3; i++)
    {
        top[i] = -1;
        top_dist[i] = DBL_MAX;
    }

    for (int shift = 0; shift < ALPHA; shift++)
    {
        char decrypted[MAX_LEN];
        decrypt(text, shift, decrypted);

        double hist[ALPHA];
        compute_histogram(decrypted, hist);

        double dist = distamce_function(hist, english_distibution);

        for (int i = 0; i < 3; i++)
        {
            if (dist < top_dist[i])
            {
                for (int j = 2; j > i; j--)
                {
                    top[j] = top[j - 1];
                    top_dist[j] = top_dist[j - 1];
                }
                top[i] = shift;
                top_dist[i] = dist;
                break;
            }
        }
    }
}

void display_histogram(const double histogram[ALPHA])
{
    printf("\nCharacter frequency distribution:\n");
    for (int i = 0; i < ALPHA; i++)
    {
        printf("%c: %.2f%%\n", 'a' + i, histogram[i] * 100);
    }
}

void read_from_text_file(const char *filename, char *text)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error oppening the input file: %s\n", filename);
        text[0] = '\0';
        return;
    }

    int i = 0;
    char c;
    while ((c = fgetc(fp)) != EOF && i < MAX_LEN - 1)
    {
        text[i++] = c;
    }
    text[i] = '\0';

    fclose(fp);
    printf("Input from the file: %s\n", text);
}

void read_from_keyboard(char *text)
{
    printf("Enter text: ");
    if (fgets(text, MAX_LEN, stdin) == NULL)
    {
        text[0] = '\0';
        return;
    }
    text[strcspn(text, "\n")] = '\0'; //Remove the last enter from keyboard
    printf("Text entered: %s\n", text);
}