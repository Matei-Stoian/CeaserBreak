#include "caeser.h"
#include "stdio.h"
void display_menu()
{
    printf("\n=== Caesar Cipher Menu ===\n");
    printf("1. Read text from keyboard\n");
    printf("2. Read text from file\n");
    printf("3. Encrypt text with specified shift\n");
    printf("4. Decrypt text with known shift\n");
    printf("5. Compute and display frequency distribution\n");
    printf("6. Break cipher using Chi-squared distance\n");
    printf("7. Break cipher using Euclidean distance\n");
    printf("8. Break cipher using Cosine distance\n");
    printf("9. Exit\n");
    printf("Enter your choice (1-9): ");
}
void clear_buffer()
{
    while (getchar() != '\n')
        ; // Clear the buffer
}
int main()
{

    int choice;
    char input_text[MAX_LEN] = {0};
    char output_text[MAX_LEN] = {0};
    int shift;
    char filename[256];
    int top[3];
    double top_dist[3];

    while (1)
    {
        display_menu();
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input\n");
            clear_buffer(); // Clear the buffer
            continue;
        }
        while (getchar() != '\n')
            ;

        switch (choice)
        {
        case 99:
            printf("Debug:\n Input: %s\nOutput: %s\n", input_text, output_text);
            break;
        case 1:
            read_from_keyboard(input_text);
            break;
        case 2:
            printf("Enter filename: ");
            scanf("%255s", filename);
            clear_buffer();
            read_from_text_file(filename, input_text);
            break;

        case 3:
            if (input_text[0] == '\0')
            {
                printf("No input text available. Please read text first.\n");
                break;
            }
            printf("Enter shift(0-25): ");
            if (scanf("%d", &shift) != 1)
            {
                printf("Invalid input.\n");
                clear_buffer();
                break;
            }
            clear_buffer();
            encrypt(input_text, shift, output_text);
            printf("Encrypted text: %s", output_text);
            break;
        case 4:
            if (input_text[0] == '\0')
            {
                printf("No input text available. Please read text first.\n");
                break;
            }
            printf("Enter shift(0-25): ");
            if (scanf("%d", &shift) != 1)
            {
                printf("Invalid input.\n");
                clear_buffer();
                break;
            }
            clear_buffer();
            decrypt(input_text, shift, output_text);
            printf("Decrypted text: %s\n", output_text);
            break;
        case 5:
            if (input_text[0] == '\0')
            {
                printf("No input text available. Please read text first.\n");
                break;
            }
            double hist[ALPHA];
            compute_histogram(input_text, hist);
            display_histogram(hist);
            break;
        case 6:
            if (input_text[0] == '\0')
            {
                printf("No input text available. Please read text first.\n");
                break;
            }
            break_chiper(input_text, top, top_dist, chi_square_dist);
            printf("\nTop %d most likely shifts using Chi-squared distance:\n", 3);
            for (int i = 0; i < 3; i++)
            {
                if (top[i] != -1)
                {
                    decrypt(input_text, top[i], output_text);
                    printf("%d. Shift: %d, Distance: %.6f\n", i + 1, top[i], top_dist[i]);
                    printf("Decrypted: %s\n", output_text);
                }
            }
            break;
        case 7:
            if (input_text[0] == '\0')
            {
                printf("No input text available. Please read text first.\n");
                break;
            }
            break_chiper(input_text, top, top_dist, euclidean_dist);
            printf("\nTop %d most likely shifts using Euclidean   distance:\n", 3);
            for (int i = 0; i < 3; i++)
            {
                if (top[i] != -1)
                {
                    decrypt(input_text, top[i], output_text);
                    printf("%d. Shift: %d, Distance: %.6f\n", i + 1, top[i], top_dist[i]);
                    printf("Decrypted: %s\n", output_text);
                }
            }
            break;
        case 8:
            if (input_text[0] == '\0')
            {
                printf("No input text available. Please read text first.\n");
                break;
            }
            break_chiper(input_text, top, top_dist, cosine_dist);
            printf("\nTop %d most likely shifts using Cosine   distance:\n", 3);
            for (int i = 0; i < 3; i++)
            {
                if (top[i] != -1)
                {
                    decrypt(input_text, top[i], output_text);
                    printf("%d. Shift: %d, Distance: %.6f\n", i + 1, top[i], top_dist[i]);
                    printf("Decrypted: %s\n", output_text);
                }
            }
            break;
        case 9:
            return 0;
        default:
            break;
        }
    }
}