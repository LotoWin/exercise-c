#include<stdio.h>
#include <stdlib.h>

typedef struct Cargo {
  int weight;
  int value;
  struct Cargo *next;
} Cargo;
typedef Cargo* CargoNode;

CargoNode Append(CargoNode head, int weight, int value) {
  CargoNode current = head;
  if(head == NULL) {
    head = (CargoNode)malloc(sizeof(Cargo));
    head->weight = weight;
    head->value = value;
    head->next = NULL;
  } else {
    while(current->next != NULL) {
      current = current->next;
    }
    current->next = (CargoNode)malloc(sizeof(Cargo));
    current = current->next;
    current->weight = weight;
    current->value = value;
    current->next = NULL;
  }
  return head;
}

// find maximum integer
int Max(int a, int b) {
    return (a > b) ? a : b;
}

// find nth item weight
int CargoWeight(CargoNode head, int index) {
  CargoNode current = head;
  for(int i=0; i<index-1; i++) {
    current = current->next;
  }
  return current->weight;
}

// find nth item value
int CargoValue(CargoNode head, int index) {
  CargoNode current = head;
  for(int i=0; i<index-1; i++) {
    current = current->next;
  }
  return current->value;
}

int CargoKnapsack(int max_wt, CargoNode head, int number) {
  if (number == 0 || max_wt == 0)
    return 0;
  // exclude the nth item if weight > max_wt
  if (CargoWeight(head, number-1) > max_wt)
    return CargoKnapsack(max_wt, head, number-1);
  // Find the maximum
  // 1) nth item included
  // 2) nth item not included
  else
    return Max(CargoValue(head, number) + CargoKnapsack(max_wt-CargoWeight(head, number), head, number-1),
                   CargoKnapsack(max_wt, head, number-1));
}

int main() {
  CargoNode cargos = NULL;
  int number, max_weight, weight, value;
  scanf("%d", &number);
  scanf("%d", &max_weight);
  for (int i=0; i<number; i++) {
    scanf("%d", &weight);
    scanf("%d", &value);
    cargos = Append(cargos, weight, value);
  }
  printf("%d", CargoKnapsack(max_weight, cargos, number));
  free(cargos);
  return 0;
}