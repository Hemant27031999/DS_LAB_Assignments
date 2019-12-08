/**
 * @file Que1.cpp
 * @author Hemant
 * @version 0.1
 * @date 2019-09-03
 *
 * @copyright Copyright (c) 2019
 *
 */
#include <iostream>
#include <unordered_map>

using namespace std;


/**
 * @brief This main method takes in array, makes a hashtable for storing the cumulative sum and then find the longest subarray with given sum
 *
 * @return 0
 */
int main()
{	cout<<"Enter length of array : ";
	int N;
	cin>>N;
	cout<<"Enter the array : "<<endl;
	int a[N];
	int sum=0;
	unordered_map<int, int> collect;
	for (int i = 0; i < N; i++){
		cin>>a[i];
		sum+=a[i];
		collect[sum] = i;
	}
	cout<<"Enter sum to search for : ";
	int n;
	cin>>n;
	int index_i, index_j, length=0;
	sum = 0;

	for(int i=0; i<N; i++){
		if(!(collect.find(sum+n) == collect.end())){
			if((collect[sum+n]-i+1)>length){
				length = collect[sum+n]-i+1;
				index_i = i;
				index_j = collect[sum+n];
			}
		}
		sum+=a[i];
	}

	if(!length==0)
		cout<<"Length of longest subarray is "<<length<<"\nIndex from "<<index_i<<" to "<<index_j<<endl;
	else
		cout<<"Not Found"<<endl;
		
	return 0;
}

