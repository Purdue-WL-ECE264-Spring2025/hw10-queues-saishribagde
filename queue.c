#include "queue.h"
#include "tile_game.h"
static bool in_visited(struct linked_list tocheckin, struct game_state next_state);

void enqueue(struct queue *q, struct game_state state) 
{
    size_t serialized_state = serialize(state);
    insert_at_tail(&(q->data), serialized_state);
}

struct game_state dequeue(struct queue *q) 
{ 
    size_t serialized_state = remove_from_head(&(q->data));
    struct game_state dequeued_state = deserialize(serialized_state); 
    return dequeued_state;
}

int number_of_moves(struct game_state start) 
{ 
    struct queue q;
    struct linked_list visited_state = {0};

    enqueue(&q, start);
    insert_at_head(&visited_state, serialize(start));

    while(q.data.head != NULL)
    {
        struct game_state current = dequeue(&q);

        //checks for if the current state is solved or not
        int solved = 0;
        int order = 1;
        if(current.tiles[3][3] == 0)
        {
            solved = 1;
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(i == 3 && j == 3)
                    break;

                    if(current.tiles[i][j] != order)
                    {
                        solved = 0;
                        break;
                    }
                    else
                    {
                        order++;
                    }
                }
            }
        }

        if(solved==1)
        {
            free_list(visited_state);
            free_list(q.data);
            return current.num_steps;
        }

        struct game_state next = current;
        
        //move up
        next = current;
        if ((next.empty_row!=3))
        {
            move_up(&next);
            if(in_visited(visited_state, next) == 0)
            {
                enqueue(&q, next);
                insert_at_head(&visited_state, serialize(next));
            }
            
        }
        
        next = current;
        if(next.empty_row != 0)
        {
            move_down(&next);
            if(in_visited(visited_state, next) == 0)
            {
                enqueue(&q, next);
                insert_at_head(&visited_state, serialize(next));
            }
        }

        next = current;
        if(next.empty_col != 0)
        {
            move_right(&next);
            if(in_visited(visited_state, next) == 0)
            {
                enqueue(&q, next);
                insert_at_head(&visited_state, serialize(next));
            }
        }
        
        next = current;
        if(next.empty_col != 3)
        {
            move_left(&next);
            if(in_visited(visited_state, next) == 0)
            {
                enqueue(&q, next);
                insert_at_head(&visited_state, serialize(next));
            };
        }
        

        // if(next.num_steps != current.num_steps)
        // {
        //     int seen = 0;
        //     struct list_node *cursor = visited_state.head;
        //     if(invisited(cursor, next) == 0)
        //     {
        //         enqueue(&q, next);
        //         insert_at_head(&visited_state, serialize(next));
        //     }
        //     // while(cursor != NULL)
        //     // {
        //     //     if(cursor->value == serialize(next))
        //     //     {
        //     //         seen = 1;
        //     //         break;
        //     //     }
        //     // }
        // }

        //move down
        // next = current;
        // move_down(&next);

        // if(next.num_steps != current.num_steps)
        // {
        //     int seen = 0;
        //     struct list_node *cursor = visited_state.head;
        //     while(cursor != NULL)
        //     {
        //         if(cursor-> value == serialize(next))
        //         {
        //             seen = 1;
        //             break;
        //         }
        //     }

        //     if(seen == 0)
        //     {
        //         enqueue(&q, next);
        //         insert_at_head(&visited_state, serialize(next));
        //     }
  
        // }

        // //move right
        // next = current;
        // move_right(&next);

        // if(next.num_steps != current.num_steps)
        // {
        //     int seen = 0;
        //     struct list_node *cursor = visited_state.head;
        //     while(cursor != NULL)
        //     {
        //         if(cursor-> value == serialize(next))
        //         {
        //             seen = 1;
        //             break;
        //         }
        //     }

        //     if(seen == 0)
        //     {
        //         enqueue(&q, next);
        //         insert_at_head(&visited_state, serialize(next));
        //     }
  
        // }

        // // move left
        // next = current;
        // move_left(&next);

        // if(next.num_steps != current.num_steps)
        // {
        //     int seen = 0;
        //     struct list_node *cursor = visited_state.head;
        //     while(cursor != NULL)
        //     {
        //         if(cursor-> value == serialize(next))
        //         {
        //             seen = 1;
        //             break;
        //         }
        //     }

        //     if(seen == 0)
        //     {
        //         enqueue(&q, next);
        //         insert_at_head(&visited_state, serialize(next));
        //     }
  
        //}
    }

    free_list(q.data);
    free_list(visited_state);
    return -1;

}

static bool in_visited(struct linked_list tocheckin, struct game_state next_state)
{
    bool seen = 0;
    struct list_node *cursor = tocheckin.head;
    while(cursor != NULL)
    {
        if(cursor-> value == serialize(next_state))
        {
            seen = 1;
            break;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return seen;
}
