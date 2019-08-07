#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

#define MaxSize 10

void shuffle(vector<int> & arr)
{
    for (int i=arr.size()-1;i>0;--i)
    {
        swap(arr[i], arr[rand() % (i+1)]);
    }
}

int main(void)
{
    srand(time(NULL));

    vector<int> arr(MaxSize);
    for (int i=0;i<arr.size();++i){
        arr[i] = i;
    }
    
    shuffle(arr);

    for(int num : arr){
        cout<<num<<' ';
    }
    cout<<endl;

    return 0;
}