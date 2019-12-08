import java.util.*;
import java.lang.*;
import java.io.*;
import java.lang.System;

class Que2 {
    public static void main(String[] args) throws java.lang.Exception {
        double startTime = System.nanoTime();
        
        System.out.print("Enter the Array size : ");
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int my_arr[] = new int[n];

        System.out.print("Enter the Array elements : ");
        
        for (int i = 0; i < n; i++) {
            my_arr[i] = in.nextInt();
        }

        int tree[] = new int[4 * n + 1];
        int tree2[] = new int[4 * n + 1];
        int tree3[] = new int[4 * n + 1];

        making_sum_trees(my_arr, tree, 0, n - 1, 1);
        makemaxtree(my_arr, tree2, 0, n - 1, 1);
        makemintree(my_arr, tree3, 0, n - 1, 1);

        System.out.println("Enter the operation index : ");

        while (true) {
            int choice;
            int i, j;
            System.out.print(
                    "1. Get Minimum Value :\n2. Get Maximum Value :\n3. Get Sum : \n4. Add 4 to each element : \n5. Exit\nIndex : ");
            choice = in.nextInt();

            if (choice == 5) {
                calledDecor();
                double endTime = System.nanoTime();
                double totalTime = endTime - startTime;
                System.out.println("\nExecution Time is :" + totalTime/1000000000+" seconds");
                break;
            }

            System.out.print("Also enter the index range : ");
            i = in.nextInt();
            j = in.nextInt();
            if (choice == 1) {
                calledDecor();
                System.out.println("Minimum value from "+i+" to "+j+" is " + minimum_query(tree3, 1, 0, n - 1, i, j));
            } else if (choice == 2) {
                calledDecor();
                System.out.println("Maximum value  from "+i+" to "+j+" is " + maximum_query(tree2, 1, 0, n - 1, i, j));
            } else if (choice == 3) {
                calledDecor();
                System.out.println("Sum is " + querysum(tree, 1, 0, n - 1, i, j));
            } else if (choice == 4) {
                calledDecor();
            }

        }

    }

    public static void making_sum_trees(int my_arr[], int tree[], int start, int end, int index) {

        if (start == end) {
            tree[index] = my_arr[start];
            return;
        }
        calledDecor();
        making_sum_trees(my_arr, tree, start, (start + end) / 2, 2 * index);
        making_sum_trees(my_arr, tree, (start + end) / 2 + 1, end, 2 * index + 1);
        tree[index] = tree[2 * index] + tree[2 * index + 1];
        return;

    }

    public static void makemintree(int my_arr[], int tree[], int start, int end, int index) {

        if (start == end) {
            tree[index] = my_arr[start];
            return;
        }
        calledDecor();
        makemintree(my_arr, tree, start, (start + end) / 2, 2 * index);
        makemintree(my_arr, tree, (start + end) / 2 + 1, end, 2 * index + 1);
        tree[index] = tree[2 * index] > tree[2 * index + 1] ? tree[2 * index + 1] : tree[2 * index];
        return;

    }

    public static void makemaxtree(int my_arr[], int tree[], int start, int end, int index) {

        if (start == end) {
            tree[index] = my_arr[start];
            return;
        }
        calledDecor();
        makemaxtree(my_arr, tree, start, (start + end) / 2, 2 * index);
        makemaxtree(my_arr, tree, (start + end) / 2 + 1, end, 2 * index + 1);
        tree[index] = tree[2 * index] < tree[2 * index + 1] ? tree[2 * index + 1] : tree[2 * index];
        return;

    }

    public static int querysum(int tree[], int index, int s, int e, int qs, int qe) {

        if (qs > e || qe < s)
            return 0;
        else if (qs <= s && qe >= e)
            return tree[index];
        else {
            int mid = (s + e) / 2;
            return querysum(tree, 2 * index, s, mid, qs, qe) + querysum(tree, 2 * index + 1, mid + 1, e, qs, qe);
        }

    }

    public static int minimum_query(int tree[], int index, int s, int e, int qs, int qe) {

        calledDecor();
        if (qs > e || qe < s)
            return Integer.MAX_VALUE;
        else if (qs <= s && qe >= e)
            return tree[index];
        else {
            int mid = (s + e) / 2;
            return minimum_query(tree, 2 * index, s, mid, qs, qe) > minimum_query(tree, 2 * index + 1, mid + 1, e, qs, qe)
                    ? minimum_query(tree, 2 * index + 1, mid + 1, e, qs, qe)
                    : minimum_query(tree, 2 * index, s, mid, qs, qe);
        }

    }

    public static int maximum_query(int tree[], int index, int s, int e, int qs, int qe) {

        calledDecor();
        if (qs > e || qe < s)
            return Integer.MIN_VALUE;
        else if (qs <= s && qe >= e)
            return tree[index];
        else {
            int mid = (s + e) / 2;
            return maximum_query(tree, 2 * index, s, mid, qs, qe) < maximum_query(tree, 2 * index + 1, mid + 1, e, qs, qe)
                    ? maximum_query(tree, 2 * index + 1, mid + 1, e, qs, qe)
                    : maximum_query(tree, 2 * index, s, mid, qs, qe);
        }
    }

    public static void calledDecor(){}

}
