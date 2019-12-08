/**
 * @file nqueens.cpp
 * @author Hemant
 * @brief This program find different positions of n queens on a chessboard such that they are non-attacking to each other
 * @version 0.1
 * @date 2019-09-03
 *
 * @copyright Copyright (c) 2019
 *
 */
#include<iostream>
using namespace std;


int flag = 0;


/**
 * @brief This method tells whether the given position is safe or not
 * @param i as x index of queen
 * @param j as y index of queen
 * @param board where queens are placed
 * @param Number of queens
 *
 * @return boolean regarding whether queen at given position is attacked by any other queen or not
 */
bool is_attacked(int i, int j, int **board, int N){
	for (int pointer=0; pointer <N; pointer++) {
		if (board[i][pointer] == 1) return true;
	}

	for (int pointer=0; pointer <N; pointer++) {
		if (board[pointer][j] == 1) return true;
	}

	int p=i,q=j;

	if(p==N-1){
			p=N-q-1;
			q=0;
		}
	else if(q==N-1){
			q=N-p-1;
			p=0;
		}
	else{
		p=(p+1)%N;
		q=(q+1)%N;}

	while(p!=i && q!=j){
		if(board[p][q]==1) return true;
		if(p==N-1){
			p=N-q-1;
			q=0;
		}
		else if(q==N-1){
			q=N-p-1;
			p=0;
		}else{
		p=(p+1)%N;
		q=(q+1)%N;}
	}

	if(p==N-1 || q==0){
			p=p+q;
			q=p-q;
			p=p-q;
		}
	else{
		p=(p+1)%N;
		q=(q-1+N)%N;}

	while(p!=i && q!=j){
		if(board[p][q]==1) return true;
		if(p==N-1 || q==0){
			p=p+q;
			q=p-q;
			p=p-q;
		} else{
		p=(p+1)%N;
		q=(q-1+N)%N;}
	}

	return false;
}


/**
 * @brief This prints all possible ways (if any) of placing n-queens such that they are non-attacking
 * @param board where queens are placed
 * @param size of chessboard
 * @param number of queen to be placed
 * @param i as x index of queen
 * @param j as y index of queen
 *
 */
void N_queen(int **board, int N, int number_of_queens, int next_i, int next_j){
	if(number_of_queens==0){
		flag++;
		cout<<"Solution "<<flag<<" is :"<<endl;
		for (int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}
		cout<<endl;
	}

	for (int i=next_i; i<N; i++){
		for(int j= i==next_i?next_j:0; j<N; j++){
			if (is_attacked(i,j,board,N)){}
			else{
				board[i][j]=1;
				N_queen(board, N, number_of_queens-1, i, j);
				board[i][j]=0;
			}
		}
	}
}

/**
 * @brief This is the main driver function
 *
 * @return 0
 */
int main()
{
	int N;
	cout<<"Enter size of chessboard : ";
	cin>>N;
	cout<<"\n";
	int **board;
	board = new int *[N];
	for(int i = 0; i <N; i++)
	    board[i] = new int[N];

	N_queen(board, N, N, 0, 0);
	cout<<"Number of Solutions possible are : "<<flag<<endl<<endl;

	return 0;
}
