# Autocomplete Functionality Implementation

This project implements a fast and efficient autocomplete functionality in C. It processes large datasets containing terms and their associated importance weights to provide quick suggestions based on a query string. The system uses advanced techniques such as binary search and sorting to optimize performance. This project is part of ESC190 (Data Structures and Algorithms) at the University of Toronto.

## Features
- **Case-sensitive query matching**: Matches terms that start with the query string (e.g., `"Eng"` matches `"EngSci"` but not `"engaged"`).
- **Efficient data handling**: Reads, processes, and stores large numbers of terms.
- **Binary search**: Locates the first and last matching terms in lexicographic order in `O(log(n))` time.
- **Weighted sorting**: Ranks matching terms by their associated weights for better suggestions.
- **Dynamic memory allocation**: Efficiently handles memory for large datasets.

## File Structure
The program uses the following key functions:

1. **`read_in_terms`**: Reads terms from a file, sorts them lexicographically, and dynamically allocates memory.
2. **`lowest_match`**: Finds the first term in lexicographic order that matches the query string.
3. **`highest_match`**: Finds the last term in lexicographic order that matches the query string.
4. **`autocomplete`**: Provides a ranked list of matching terms sorted by weight in non-increasing order.

## Functions

### `read_in_terms`
```c
void read_in_terms(term **terms, int *pnterms, char *filename);
```
- Reads terms and weights from the input file.
- Sorts terms lexicographically.
- Allocates memory dynamically.

### `lowest_match`
```c
int lowest_match(term *terms, int nterms, char *substr);
```
- Finds the index of the first term matching the query string.
- Time complexity: `O(log(n))`.

### `highest_match`
```c
int highest_match(term *terms, int nterms, char *substr);
```
- Finds the index of the last term matching the query string.
- Time complexity: `O(log(n))`.

### `autocomplete`
```c
void autocomplete(term **answer, int *n_answer, term *terms, int nterms, char *substr);
```
- Generates a ranked list of matching terms sorted by weight.

## Implementation Details

### Struct Definition
```c
typedef struct term {
    char term[200];
    double weight;
} term;
```
- Represents a term with a string (max length 200) and a weight.

### Sorting
- Uses `qsort` for both lexicographic and weight-based sorting.

### Binary Search
- Efficiently locates matching terms using `lowest_match` and `highest_match`.

## Testing

### Example Test
```c
void test_read_in_terms();
```
- Verifies the functionality of `read_in_terms`.

To add more tests, modify the `test_*` functions or write new ones.
