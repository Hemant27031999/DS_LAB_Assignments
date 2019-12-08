/**
 * @file Que2.cpp
 * @author Hemant 
 * @brief 
 * @date 2019-10-08
 * 
 * 
 */
#include <iostream>
#include <bits/stdc++.h> 
#include <string>

using namespace std;

/**
 * @brief A single Node of Binomial heap(tree)
 * 
 */
struct Node
{
    int n;
    int degree;
    Node* parent;
    Node* child;
    Node* sibling;
};

/**
 * @brief The main Binomial Heap
 * 
 */
class BinomialHeap
{
    private:
        Node *H;
        Node *Hr;
        int count;
    public:
        Node* Initializeheap();
        void Binomial_link(Node*, Node*);
        Node* Create_Node(int);
        Node* Union(Node*, Node*);
        Node* Insert(Node*, Node*);
        Node* Merge(Node*, Node*);
        void Display(Node*);
        void PrintTree(Node*, int);
        string MakeGraph(Node*, int , string);

        BinomialHeap()
        {
            H = Initializeheap();
            Hr = Initializeheap();
            int count = 1;
        }
};
 

/*
 * @brief this method initialize heap by returning a null pointer to Node
 * @return pointer to the null Node created
*/
Node* BinomialHeap::Initializeheap()
{
    Node* np;
    np = NULL;
    return np;
}


/*
 * @brief binomial link joins two Nodes(trees)
 * @param Node with larger value in it
 * @param Node with smaller value in it
*/
void BinomialHeap::Binomial_link(Node* y, Node* z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}


/*
 * @brief create_Node makes a Node and insert value inside it
 * @param the value to be stored
 * @return pointer to the created Node
*/
Node* BinomialHeap::Create_Node(int k)
{
    Node* p = new Node;
    p->n = k;
    return p;
}


/*
 * @brief inserting a Node in binomial heap
 * @param pointer to the first Node of base heap
 * @param Node to be inserted
 * @return pointer to the first Node of base heap
*/
Node* BinomialHeap::Insert(Node* H, Node* x)
{
    Node* H1 = Initializeheap();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = Union(H, H1);
    return H;
}
 
/*
 * @brief merging two binomial trees
 * @param first binomial tree
 * @param second binomial tree
 * @return pointer to the final base Node
*/
Node* BinomialHeap::Union(Node* H1, Node* H2)
{
    Node *H = Initializeheap();
    H = Merge(H1, H2);
    if (H == NULL)
        return H;
    Node* prev_x;
    Node* next_x;
    Node* x;
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL)
    {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL)
            && (next_x->sibling)->degree == x->degree))
        {
            prev_x = x;
            x = next_x;
        }
        else
	    {
            if (x->n <= next_x->n)
            {
                x->sibling = next_x->sibling;
                Binomial_link(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                Binomial_link(x, next_x);
                x = next_x;
            }
	    }
        next_x = x->sibling;
    }
    return H;
}
/*
 * @brief function to split a string against a delimiter provided
 * @param string to be devided
 * @param delimeter against which the string will be divided
 * @return vector containing the divided string
*/
Node* BinomialHeap::Merge(Node* H1, Node* H2)
{
    Node* H = Initializeheap();
    Node* y;
    Node* z;
    Node* a;
    Node* b;
    y = H1;
    z = H2;
    if (y != NULL)
    {
        if (z != NULL)
        {
            if (y->degree <= z->degree)
                H = y;
            else if (y->degree > z->degree)
                H = z;
        }
        else
            H = y;
    }
    else
        H = z;
    while (y != NULL && z != NULL)
    {
        if (y->degree < z->degree)
        {
            y = y->sibling;
        }
        else if (y->degree == z->degree)
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        }
        else
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}


/*
 * @brief display all the Nodes of binomial heap
 * @param pointer to the first Node of base heap
*/
void BinomialHeap::Display(Node* H)
{
	int i = 0;
	int level = 0;
    if (H == NULL)
    {
        cout<<"The Heap is empty"<<endl;
    }
    Node* p;
    p = H;

    while (p != NULL)
    {
    	cout<<i<<" : ";
        PrintTree(p, level);
        p = p->sibling;
        i++;
        cout<<endl;
    }

    cout<<endl;
}


/*
 * @brief display all the Nodes of binomial tree
 * @param pointer to the first Node of base heap
 * @param level of node
*/
void BinomialHeap::PrintTree(Node* h, int level){
	while (h) 
	{ 
		cout << h->n << " "; 
		PrintTree(h->child, level + 1); 
		if(level != 0)
			h = h->sibling; 
		else
			return;
	} 
}


string BinomialHeap::MakeGraph(Node* h, int parentKey, string out){
	Node* p=h->child;
	while(p != NULL){
		out += to_string(parentKey) + " -- " + to_string(p->n) + "\n";
		// cout<<to_string(parentKey) + " -- " + to_string(p->n) + "\n";
		p = p->sibling;
	}

	p=h->child;
	while(p != NULL){
		out = MakeGraph(p, p->n, out);
		p = p->sibling;
	}

	return out;
}



int main()
{
    int n, m, l, i, count, temp, len;
    string out="";
    BinomialHeap bh;
    Node* p;
    Node *H;
    int take_note = 0;
    Node* point;
    H = bh.Initializeheap();
    string out_main;
	out_main = "graph output {\n\n";
    char ch;
    FILE *fptr;
    char *char_array_out;

    while (1)
    {
        cout<<"\n----------------------------"<<endl;
        cout<<"Operations on Binomial heap"<<endl;
        cout<<"----------------------------"<<endl;
        cout<<"1)Insert Element one by one in heap"<<endl;
        cout<<"2)Enter the elements continuously"<<endl;
        cout<<"3)Display Heap"<<endl;
        cout<<"4)Display Graph"<<endl;
        cout<<"5)Exit"<<endl;
        cout<<"Enter Your Choice: ";
        cin>>l;
        switch(l)
        {
        case 1:
            cout<<"Enter the element : ";
            cin>>m;
            p = bh.Create_Node(m);
            H = bh.Insert(H, p);
            break;
        case 2:
        	cout<<"Enter the number of elements you will insert : ";
        	cin>>count;
        	for(int i=0; i<count; i++){
        		cin>>temp;
        		p = bh.Create_Node(temp);
        		H = bh.Insert(H, p);
        	}
        	break;
        case 3:
            cout<<"The Heap is: "<<endl;
            bh.Display(H);
            break;
        case 4:
        	point = H;
        	take_note = 0;
        	out_main += "";
        	while(point){
        		take_note++;
        		out = "subgraph g" + to_string(take_note) + " {\n";
        		out += to_string(point->n) + " \n";
        		out = bh.MakeGraph(point, point->n, out);
        		out += "}\n\n";
        		out_main += out;
        		point = point->sibling;
        	}
            out_main += "}\n";

            len = out_main.length();
			char_array_out = new char[len+1];
			strcpy(char_array_out, out_main.c_str());
			fptr = fopen("Graph.dot","w");

			if(fptr == NULL)
		    {
		      printf("Error!");   
		      exit(1);             
		    }

		    fprintf(fptr,"%s",char_array_out);
		    fclose(fptr);

            cout<<out_main<<endl;
            break;
        case 5:
            exit(1);
        default:
            cout<<"Wrong Choice";
	  }
    }
    return 0;
}