/**
 * @file Que2.cpp
 * @author Hemant
 * @brief This program works on different types of trees
 * @version 0.1
 * @date 2019-08-20
 *
 * @copyright Copyright (c) 2019
 *
 */
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief datastructure Node of linked list
 *
 */
struct Node
{
  int data;
  Node *next;
};

/**
 * @brief this method counts the number of triplets
 *
 * @param number of entries
 * @param array containing the numbers to be inserted
 */
void countTriplets(int n, int a[])
{
  int count = 0;
  for (int i = 0; i < n; i++){
    Node *head = new Node;
    head->data = a[i];
    Node *ptr1 = head;
    Node *ptr2 = head;
    for (int j = i + 1; j < n; j++){
      Node *root = new Node;
      root->data = a[j] ^ ptr1->data;
      ptr1 = root;
      Node *ptr3 = root;
      ptr2->next = ptr3;
      ptr2 = ptr2->next;
    }
    int counter = 0;
    while (head != NULL){
      if (head->data == 0){
        count += counter;
      }
      counter++;
      head = head->next;
    }
  }
  cout << count << endl;
}

/**
 * @brief printing the triplets with the help of dynamic programming
 *
 * @param number of ebtries
 * @param array containing the entries
 */
void printTriplets(int n, int a[]){
  for (int i = 0; i < n; i++){
    Node *head = new Node;
    head->data = a[i];
    Node *ptr1 = head;
    Node *ptr2 = head;
    vector<pair<int, int>> mydata;
    for (int j = i + 1; j < n; j++){
      Node *root = new Node;
      root->data = a[j] ^ ptr1->data;
      ptr1 = root;
      Node *ptr3 = root;
      ptr2->next = ptr3;
      ptr2 = ptr2->next;
    }
    int counter = 0;
    while (head != NULL){
      if (head->data == 0){
        for (int l = 0; l < counter; l++)
          mydata.push_back(make_pair(i + l + 1 + 1, counter + i + 1));
      }
      counter++;
      head = head->next;
    }
    sort(mydata.begin(), mydata.end());
    for (int k = 0; k < mydata.size(); k++)
      cout << "(" << i+1 << ", " << mydata[k].first << ", " << mydata[k].second << ")" << endl;
  }
}

/**
 * @brief main driving program
 *
 */
int main()
{
  clock_t time;
  time = clock();
  int n;
  cout << "Enter the length of array : ";
  cin >> n;
  cout << "Insert the "<<n<<" entries : ";
  int a[n];
  for (int i = 0; i < n; i++)
    cin >> a[i];

  cout<<"Numbers of triplets are : \n";
  countTriplets(n, a);
  cout<<endl;
  cout<<"The triplets are : \n";
  printTriplets(n, a);
  time = clock() - time;
  double total_time = ((double)time) / CLOCKS_PER_SEC;
  printf("\nTime taken :%f seconds\n", total_time);

  return 0;
}
