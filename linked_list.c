#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value)
{
  struct list_node *node_n = malloc(sizeof(struct list_node));
  if(!node_n)
  {
    return NULL;
  }

  node_n->value = value;
  node_n->next = NULL;

  return node_n;
} 

void insert_at_head(struct linked_list *list, size_t value) 
{
  struct list_node *node = new_node(value);

  if(!node)
  {
    return;
  }

  node->next = list->head;
  list->head = node;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  struct list_node *node = new_node(value);

  if(!node)
  {
    return;
  }

  if(list->head == NULL)
  {
    list->head = node;
    return;
  }
  
  struct list_node *current = list->head;
  while(current->next != NULL)
  {
    current = current->next;
  }

  current->next = node;
}

size_t remove_from_head(struct linked_list *list) 
{ 
  if(list->head == NULL)
  {
    return 0;
  } 

  struct list_node *temp = list->head;
  size_t value_head = temp->value;
  list->head = temp->next;
  free(temp);
  return value_head; 
}

size_t remove_from_tail(struct linked_list *list) 
{
  if(list->head == NULL)
  {
    return 0;
  } 

  struct list_node *current_node = list->head;
  struct list_node *previous_node = NULL;

  while(current_node->next != NULL)
  {
    previous_node = current_node;
    current_node = current_node->next;
  }

  size_t value_tail = current_node->value;
  free(current_node);

  if(previous_node)
  {
    previous_node->next = NULL;
  }
  else
  {
    list->head = NULL;
  }

  return value_tail;
}

void free_list(struct linked_list list) 
{
  struct list_node *current = list.head;
  while(current != NULL)
  {
    struct list_node *temp = current;
    current = current->next;
    free(temp);
  }

  list.head = NULL;
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
