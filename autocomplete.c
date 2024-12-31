#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

typedef struct term{
char term[200]; // assume terms are not longer than 200
double weight;
} term;

int compare_terms(const void* a, const void* b)
{
    term* term_a = (term*)a;
    term* term_b = (term*)b;
    return strcmp(term_a->term, term_b->term);
}

int reverse_weight_sorter(const void* a, const void* b)
{
    term* term_a = (term*)a;
    term* term_b = (term*)b;
    return term_b->weight - term_a->weight;
}

char* remove_whitespaces(char* str)
{
    if (str == NULL) {return NULL;}
    int i = 0;
    int j = 0;
    char* new_str = str;
    while (str[i] != '\0')
    {
        if (str[i] != '\n' && str[i] != '\v' && str[i] != '\f' && str[i] != '\r') {new_str[j] = str[i]; j++;} // all whitespaces except ' ' and '\t'
        i++;
    }
    new_str[j] = '\0';
    return new_str;
}

int count_terms(char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file\n");
        exit(1);
    }
    int counter = 0;
    char line_contents[200];
    while (fgets(line_contents, sizeof(line_contents), file) != NULL)
    {
        char* trimmed_line = (char*)remove_whitespaces(line_contents);
        if (trimmed_line != NULL && strlen(trimmed_line) > 0)
        {
            bool has_only_numbers = true;
            for (int i = 0; i < strlen(trimmed_line); i++) 
            {
                if (!isdigit(trimmed_line[i])) 
                {has_only_numbers = false; break;}
            }
            if (!has_only_numbers) {counter++;}
        }
    }
    fclose(file);
    return counter;
}

void read_in_terms(term** terms, int* pnterms, char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("Error: Could not open file\n");
        exit(1);
    }
    *pnterms = count_terms(filename);
    *terms = (term*)malloc(*pnterms * sizeof(term)); 
    char line[200];
    int j = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char* trimmed_line = remove_whitespaces(line);
        if (trimmed_line != NULL && strlen(trimmed_line) > 0)
        {
            bool has_only_numbers = true;
            for (int k = 0; k < strlen(trimmed_line); k++)
            {
                if (!isdigit(trimmed_line[k])) 
                {has_only_numbers = false; break;}
            }
            if (!has_only_numbers)
            {
                int i = 0;
                int m = 0;
                while (!isdigit(trimmed_line[m])) {m++;}
                trimmed_line = &trimmed_line[m]; // get rid of trailing whitespace
                while (isdigit(trimmed_line[i])) {i++;}
                trimmed_line[i] = '\0'; // i should be the \t between the weight and the term
                double actual_weight = atof(trimmed_line);
                char* actual_term = trimmed_line + i + 1;
                strcpy((*terms)[j].term, actual_term);
                (*terms)[j].weight = actual_weight;
                
                j++;
            }
        }
    }
    fclose(file);

    qsort(*terms, *pnterms, sizeof(term), compare_terms);
}

void test_read_in_terms()
{
    term* terms;
    char filename[] = "cities.txt";
    int num_terms = count_terms(filename);
    read_in_terms(&terms, &num_terms, filename);

    for (int i = 0; i < num_terms; i++) {
        printf("Term: %s ", terms[i].term);
        printf("Weight: %f\n", terms[i].weight);
    }

    free(terms);
}

int lowest_match(term* terms, int nterms, char* substr)
{
    if (substr == NULL) {return -1;}
    // binary_search_first where list is terms, nterms is len(list), and target is substr
    int left_index = 0;
    int right_index = nterms - 1;
    while (left_index < right_index)
    {
        int middle_index;
        middle_index = (left_index + right_index) / 2;
        if ((int)strncmp(substr, terms[middle_index].term, strlen(substr)) > 0) {left_index = middle_index + 1;}
        else {right_index = middle_index;}
    }
    return left_index;
}

int highest_match(term* terms, int nterms, char* substr)
{
    if (substr == NULL) {return -1;}
    // binary_search_last where list is terms, nterms is len(list), and target is substr
    int left_index = 0;
    int right_index = nterms - 1;
    while (left_index < right_index)
    {
        int middle_index;
        middle_index = (left_index + right_index + 1) / 2;
        if ((int)strncmp(substr, terms[middle_index].term, strlen(substr)) < 0) {right_index = middle_index - 1;}
        else {left_index = middle_index;}
    }
    return left_index;
}

void autocomplete(term** answer, int* n_answer, term* terms, int nterms, char* substr)
{
    int highest_match_index = highest_match(terms, nterms, substr);
    int lowest_match_index = lowest_match(terms, nterms, substr);
    *n_answer = highest_match_index - lowest_match_index + 1;
    *answer = (term*)malloc(*n_answer * sizeof(term));
    for (int i = lowest_match_index; i <= highest_match_index; i++)
    {
        (*answer)[i - lowest_match_index] = terms[i];
    }
    qsort(*answer, *n_answer, sizeof(term), reverse_weight_sorter);
}