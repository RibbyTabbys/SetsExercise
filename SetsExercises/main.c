#include <stdio.h>
#include "SetsExercise.h"

int main()
{
    struct set_table *table = set_table_new(7);
    if (!table)
    {
        printf("Failed to create table\n");
        return 1;
    }

    set_insert(table, "key1", strlen("key1"));
    set_insert(table, "key2", strlen("key2"));
    set_insert(table, "key3", strlen("key3"));
    set_insert(table, "key4", strlen("key4"));
    set_insert(table, "key5", strlen("key5"));
    set_insert(table, "key6", strlen("key6"));
    set_insert(table, "key7", strlen("key7"));

    if (!set_insert(table, "key1", strlen("key1")))
    {
        printf("Failed to insert duplicate key\n");
    }

    struct set_node *search_result = set_search(table, "key2", strlen("key2"));
    if (search_result)
    {
        printf("Key found: %s\n", search_result->key);
    }
    else
    {
        printf("Key not found\n");
    }

    if (set_remove(table, "key2", strlen("key2")))
    {
        printf("Key removed successfully\n");
    }
    else
    {
        printf("Key not found for removal\n");
    }

    print_table(table);

    free_table(table);

    return 0;
}
