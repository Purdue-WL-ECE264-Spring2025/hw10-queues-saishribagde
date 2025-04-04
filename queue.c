#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) 
{
    uint64_t serialized_state = serialize(state);
    insert_at_tail(&(q->data), serialized_state);
}

struct game_state dequeue(struct queue *q) 
{ 
    uint64_t serialized_state = remove_from_head(&(q->data));
    struct game_state dequeued_state = deserialize(serialized_state); 
    return dequeued_state;
}

int number_of_moves(struct game_state start) 
{ 
    struct queue q = {0};
    struct linked_list visited_state = {0};

    enqueue(&q, start);
    insert_at_head(&visited_state, serialize(start));

    while(q.data.head != NULL)
    {
        struct game_state current = dequeue(&q);

        //checks for if the current state is solved or not
        int solved = 0;
        int order = 1;
        int expected = 1;
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
                    else if(current.tiles[i][j] == order)
                    {
                        order++;
                    }
                }
            }
        }

        if(solved == expected)
        {
            free_list(visited_state);
            free_list(q.data);
            return current.num_steps;
        }

        struct game_state next = current;
        
        //move up
        next = current;
        move_up(&next);

        if(next.num_steps != current.num_steps)
        {
            int seen = 0;
            struct list_node *cursor = visited_state.head;
            while(cursor != NULL)
            {
                if(cursor->value == serialize(next))
                {
                    seen = 1;
                    break;
                }
            }

            if(seen == 0)
            {
                enqueue(&q, next);
                insert_at_head(&visited_state, serialize(next));
            }
  
        }

        //move down
        next = current;
        move_down(&next);

        if(next.num_steps != current.num_steps)
        {
            int seen = 0;
            struct list_node *cursor = visited_state.head;
            while(cursor != NULL)
            {
                if(cursor-> value == serialize(next))
                {
                    seen = 1;
                    break;
                }
            }

            if(seen == 0)
            {
                enqueue(&q, next);
                insert_at_head(&visited_state, serialize(next));
            }
  
        }

        //move right
        next = current;
        move_right(&next);

        if(next.num_steps != current.num_steps)
        {
            int seen = 0;
            struct list_node *cursor = visited_state.head;
            while(cursor != NULL)
            {
                if(cursor-> value == serialize(next))
                {
                    seen = 1;
                    break;
                }
            }

            if(seen == 0)
            {
                enqueue(&q, next);
                insert_at_head(&visited_state, serialize(next));
            }
  
        }

        // move left
        next = current;
        move_left(&next);

        if(next.num_steps != current.num_steps)
        {
            int seen = 0;
            struct list_node *cursor = visited_state.head;
            while(cursor != NULL)
            {
                if(cursor-> value == serialize(next))
                {
                    seen = 1;
                    break;
                }
            }

            if(seen == 0)
            {
                enqueue(&q, next);
                insert_at_head(&visited_state, serialize(next));
            }
  
        }
    }

    free_list(q.data);
    free_list(visited_state);
    return -1;

}
