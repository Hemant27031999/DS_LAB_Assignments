
/**
 * @file prims.cpp
 * @author Hemant 
 * @brief 
 * @date 2019-09-23
 * 
 */
#include <iostream>
#include <time.h>
#include <map> 
using namespace std;


/*
 * the main driving program
*/
int main()
{
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	int e1,e2;
	int a,b;
	int max;
	map<int, int> poly1;
	map<int, int> poly2; 

	cout<<"Enter number of terms in first polynomial : ";
	cin>>e1;
	cout<<"Enter the Coefficient and Power :"<<endl;
	for(int i=0; i<e1; i++){
		cin>>a;
		cin>>b;
		poly1[b]=a;
	}

	cout<<"Enter number of terms in second polynomial : ";
	cin>>e2;
	cout<<"Enter the Coefficient and Power :"<<endl;
	for(int i=0; i<e2; i++){
		cin>>a;
		cin>>b;
		poly2[b]=a;
	}

	max = (e1>e2)?e1:e2;

	cout<<"After addition :"<<endl;
	cout<<"Coefficients        Power"<<endl;

	for(int i=0;i<max;i++){
		cout<<poly1[i]+poly2[i]<<"                   "<<i<<endl;
	}

	cout<<"After multiplication :"<<endl;
	cout<<"Coefficients        Power"<<endl;

	int cum = 0;
	for(int i=0; i<=e1+e2-2; i++){
		cum = 0;
		for(int j=0; j<=i; j++){
			cum += poly1[j]*poly2[i-j];
		}
		cout<<cum<<"                   "<<i<<endl;
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	cout<<"Time Taken : "<<cpu_time_used<<endl;
	return 0;
}