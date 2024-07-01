#ifndef SET_EXERCISE_H
#define SET_EXERCISE_H

#include <stdlib.h>
#include <string.h>

struct set_node
{
    const char *key;
    size_t key_len;
    struct set_node *next;
};

struct set_table
{
    struct set_node **nodes;
    size_t hashmap_size;
};

struct set_table *set_table_new(const size_t hashmap_size);
void print_table(struct set_table *table);
void free_table(struct set_table *table);
int set_insert(struct set_table *table, const char *key, const size_t key_len);
struct set_node *set_search(struct set_table *table, const char *key, const size_t key_len);
int set_remove(struct set_table *table, const char *key, const size_t key_len);

#endif //SET_EXERCISE_H
