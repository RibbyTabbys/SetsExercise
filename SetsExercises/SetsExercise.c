#include "SetsExercise.h"
#include <stdio.h>

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 8463;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

struct set_table *set_table_new(const size_t hashmap_size)
{
    struct set_table *table = malloc(sizeof(struct set_table));
    if (!table)
    {
        return NULL;
    }
    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(struct set_node *));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}

void print_table(struct set_table *table)
{
    for (size_t i = 0; i < table->hashmap_size; i++)
    {
        struct set_node *node = table->nodes[i];
        printf("Index %zu: ", i);
        while (node)
        {
            printf("%s -> ", node->key);
            node = node->next;
        }
        printf("NULL\n");
    }
}

void free_table(struct set_table *table)
{
    if (!table)
    {
        return;
    }

    for (size_t i = 0; i < table->hashmap_size; i++)
    {
        struct set_node *current = table->nodes[i];
        while (current)
        {
            struct set_node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->nodes);
    free(table);
}

struct set_node *set_search(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    struct set_node *current = table->nodes[index];

    while (current)
    {
        if (current->key_len == key_len && strncmp(current->key, key, key_len) == 0)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

int set_insert(struct set_table *table, const char *key, const size_t key_len)
{
    if (set_search(table, key, key_len))
    {
        return 0;
    }

    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    struct set_node *head = table->nodes[index];

    struct set_node *new_item = malloc(sizeof(struct set_node));
    if (!new_item)
    {
        return 0;
    }
    new_item->key = key;
    new_item->key_len = key_len;
    new_item->next = head;
    table->nodes[index] = new_item;

    return 1;
}

int set_remove(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    struct set_node *head = table->nodes[index];
    struct set_node *prev = NULL;
    struct set_node *current = head;

    while (current)
    {
        if (current->key_len == key_len && strncmp(current->key, key, key_len) == 0)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                table->nodes[index] = current->next;
            }
            free(current);
            return 1; 
        }
        prev = current;
        current = current->next;
    }

    return 0;
}
