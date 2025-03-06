#ifndef CAESAR_H
#define CAESAR_H


#define MAX_LEN 1000000
#define ALPHA 26


void read_distribution(const char*filename,double distribution[ALPHA]);
void compute_histogram(const char*text,double histogra[ALPHA]);
double chi_square_dist(const double hist1[ALPHA],const double hist2[ALPHA]);
double euclidean_dist(const double hist1[ALPHA],const double hist2[ALPHA]);
double cosine_dist(const double hist1[ALPHA],const double hist2[ALPHA]);
void encrypt(const char *text,int shift,char *output);
void decrypt(const char *text,int shift,char *output);
void break_chiper(const char *text,int top[3],double top_dist[3],double (*distance_function)(const double[],const double[]));
void display_histogram(const double hist[ALPHA]);
void read_from_text_file(const char *filename,char *text);
void read_from_keyboard(char *text);
#endif