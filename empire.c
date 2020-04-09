// Copyright 2020, Sarat Poluri, All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NO_ROUTE INT_MAX

int read_time(FILE *fp);
int find_least_time(int** empire_map, int empire_size);

typedef struct times
{
  int time;
  int unVisitedCity;
}citytimes;

int mark_least_time_city(citytimes *time_taken, int empire_size);

/*typedef struct Node
{
int city;
struct Node *next;
}List ;*/


int main(int argc, char *argv[])
{
  FILE *fp;
  fp = fopen(argv[1],"r");
  int least_time = -1;
  int empire_size = -1;
  int i,j;
  int **empire_map;
  
  empire_size = read_value(fp);

  empire_map = (int**)malloc(sizeof(int*)*empire_size);
  for(i=0;i<empire_size;i++)
  {
    empire_map[i] = (int*)malloc(sizeof(int)*empire_size);
  }


  for(i=0;i<empire_size;i++)
  {
    for(j=0;j<empire_size;j++)
    {
      if(i<=j)
      {
        empire_map[i][j] = NO_ROUTE;
      }
      else
      {
         empire_map[i][j] = read_value(fp);
      }
    }
  }

  printf ("The minimum time required to send out the message to all the cities in the empire is %d\n",find_least_time(empire_map, empire_size));

  for(i=0;i<empire_size;i++)
  {
    free(empire_map[i]);
  }
  free(empire_map);
  fclose(fp);
}

int read_value(FILE *fp)
{
  char input_char, char_string[64];
  int char_count = 0;
  while(1)
  {
    input_char = fgetc(fp);
    if(input_char != EOF && input_char != ' ' && input_char != '\n')
    {
      char_string[char_count] = input_char;
      char_count++;
    }
    else
    {
      break;
    }
  }
  char_string[char_count] = '\0';
  if(char_count == 1 && char_string[0] == 'x')
  {
    return NO_ROUTE;
  }
  return atoi(char_string);
}

int find_least_time(int** empire_map, int empire_size)
{
  //List *list = NULL, *head;
  citytimes *time_taken;
  int  i, least_time = -1;
  int  list_size, least_city;
  list_size = empire_size;
  /*list = (List*)malloc(sizeof(List));
  list->city = 0;
  list->next = NULL;
  head = list;
  for(i = 1; i<empire_size;i++)
  {
    list->next = (List*)malloc(sizeof(List));
    list = list->next;
    list->city = i;
  }*/
  time_taken = (citytimes*)malloc(sizeof(citytimes)*empire_size);


  for(i=0;i<empire_size;i++)
  {
     time_taken[i].time = NO_ROUTE;
     time_taken[i].unVisitedCity = 1;
  }
 
  time_taken[0].time = 0;
  while(list_size > 0)
  {
    least_city = mark_least_time_city(time_taken, empire_size);
    printf ("least time city %d\n",least_city);
    list_size--;
    for(i=0;i<empire_size;i++)
    {
        if(i != least_city)
        {
          int travelTime = empire_map[least_city][i] == NO_ROUTE ? empire_map[i][least_city] : empire_map[least_city][i];
          if(travelTime != NO_ROUTE && time_taken[least_city].time + travelTime< time_taken[i].time)
          {
            time_taken[i].time = time_taken[least_city].time + travelTime;
          }
        }
    }
  }
  for(i=0;i<empire_size;i++)
  {
    if(least_time < time_taken[i].time)
      least_time = time_taken[i].time;
  }
  free(time_taken);
  return least_time;
}

int mark_least_time_city(citytimes *time_taken, int empire_size)
{
  int minTime = NO_ROUTE, minTimeCity = -1,i;
  for(i=0;i<empire_size;i++)
  {
    if(time_taken[i].unVisitedCity == 1)
    {
       if(minTime>time_taken[i].time)
       {
         minTime = time_taken[i].time;
         minTimeCity = i;
       }
    }
  }
  time_taken[minTimeCity].unVisitedCity = 0;
  return minTimeCity;
}
