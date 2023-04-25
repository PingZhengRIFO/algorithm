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
//7 9 44 30 23 73 72 78 58 49 
struct minHeap{
    vector<int> arr;
    void push(int t){
        arr.push_back(t);
        int p = arr.size()-1;
        while(true){  
            int f = (p-1)/2;
            if(arr[f] > arr[p]){
                swap(arr[f],arr[p]);
                p =f;
            }else{
                break;
            }
            if(f == 0) break;
        }
    }
    int pop(){
        int result = arr[0];
        arr[0] = arr[arr.size()-1];
        arr.pop_back();
        int p = 0;
        while(true){  
            int f1 = p*2 +1;
            if(f1 >= arr.size()) break;
            if(arr[f1] > arr[f1+1]){
                f1++;
            }
            if(arr[p] > arr[f1]){
                swap(arr[p],arr[f1]);
                p =f1;
            }else{
                break;
            }
        }
        return result;
        
    }
    bool empty(){
        return arr.empty();
    }
};
void heapSort(int arr[], int n){
    for(int i=1; i<n; i++){
        int p = i;
        while(true){  
            int f = (p-1)/2;
            if(arr[f] > arr[p]){
                swap(arr[f],arr[p]);
                p =f;
            }else{
                break;
            }
            if(f == 0) break;
        }
    }
}
void heapSortPop(){

}

void quick_sort(int arr[], int left, int right) {
    if(left >= right) return;
    int pivot = arr[left];
    int i = left;
    int j = right;
    while(i<j){
        while(i<j && arr[j] >=pivot){
            j--;
        }
        arr[i] = arr[j];
        while(i<j && arr[i] < pivot){
            i++;
        }
        arr[j] = arr[i];
    }
    arr[i] = pivot;
    quick_sort(arr, left, i-1);
    quick_sort(arr, i+1, right);


}
void BubbleSort(int arr[], int n) {
    bool finish = true;
    for(int i=0; i<n; i++){
        finish = true;
        for (int j= n-1; j>i; j--){
            if(arr[j] < arr[j -1]){
                swap(arr[j],arr[j-1]);
                finish = false;
            }
        }
        if(finish) return;
    }
}
void SelectSort(int arr[], int n) {
    for(int i=0; i<n; i++){
        int select_min = i;
        for(int j=i+1; j<n; j++){
            if(arr[j] < arr[select_min]){
                select_min = j;
            }
        }
        swap(arr[i], arr[select_min]);
    }
}
void shell_sort(int arr[], int n) {
    int gap = n/3;
    while(gap != 0){
        for(int i= gap; i<n; i++){
            int temp = arr[i];
            int j = i - gap;
            while(j>=0 && arr[j] > temp){
                arr[j+gap] = arr[j];
                j -=gap;
            }
            arr[j+gap] = temp;
        }
        gap /=3;
    }
}

int main() {
    int arr[10];
    for(int i =0; i<10; i++){
        arr[i] = rand() %100;
    }
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Before sorting: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    minHeap v;
    for(int i=0; i<n; i++){
        v.push(arr[i]);
    }
   // heapSort(arr, n);
    while(!v.empty()){
        cout<<v.pop()<<" ";
    }
    // cout << "After sorting: ";
    // for (int i = 0; i < n; i++) {
    
    //     cout << arr[i] << " ";
    // }
    cout << endl;

    return 0;
}

