/*
  Shell 排序（Shell Sort），也称为缩小增量排序（Diminishing Increment Sort），是插入排序的一种改进版，是一种高效的插入排序算法。它通过将待排序的序列分割成若干个子序列，对每个子序列进行插入排序，从而使整个序列在插入排序的基础上得到了更高效的优化。

  Shell 排序的主要思想是，先将待排序序列分成若干个子序列，对每个子序列进行插入排序，然后逐步缩小子序列的长度，最终使整个序列变为一个有序序列。具体实现时，我们需要选择一个递减的间隔序列，对于每个间隔进行一次插入排序，直到间隔为1，也就是对整个序列进行一次插入排序。

  下面是 Shell 排序的具体实现步骤：

  选择一个递减的间隔序列 $gap_1, gap_2, gap_3, \cdots, gap_k$，其中 $gap_i > gap_{i+1}$，且 $gap_k = 1$。
  对于每个间隔 $gap_i$，将序列分成若干个子序列，每个子序列的长度为 $gap_i$。
  对于每个子序列，进行插入排序。
  重复步骤2和3，直到间隔为1，也就是对整个序列进行一次插入排序。

*/
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <math.h>
#include <vector>
#include <stack>
#include <cstring>
#include <iostream>
using namespace std;

void shell_sort(int arr[], int n) {
    int gap = n / 2; // 初始间隔为 n/2
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int key = arr[i];
            int j = i - gap;
            while (j >= 0 && key < arr[j]) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = key;
        }
        gap /= 2; // 缩小间隔
    }
}

int main() {
    int arr[100];
    for(int i =0; i<100; i++){
        arr[i] = rand() %100;
    }
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Before sorting: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    shell_sort(arr, n);

    cout << "After sorting: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}

