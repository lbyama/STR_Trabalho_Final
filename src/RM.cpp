#include <RM.h>

void RM_sort(TaskStruct* tasks, int numTasks) {
  // Implementação do algoritmo de ordenação ( Bubble Sort)
  for (int i = 0; i < numTasks - 1; i++) {
    for (int j = 0; j < numTasks - i - 1; j++) {
      if (tasks[j].period > tasks[j + 1].period) {
        TaskStruct temp = tasks[j];
        tasks[j] = tasks[j + 1];
        tasks[j + 1] = temp;
      }
    }
  }
}
