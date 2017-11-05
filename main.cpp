#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <queue>
#include <set>
using namespace std;


int h_value;
/**
Node Class for representing the states in the BlocksWorld.
g is our graph
n_b is the number of blocks
n_d is the number of dashes
*/
class Node
{
public:
    vector< vector<char> > g;
    int n_d; int n_b;
    int cost = 0;
    int t_cost=0;
    bool found = false;
    Node *head;
    Node(int n_d, int n_b)
    {
        vector<char> temp;
        this->n_d = n_d;
        this->n_b = n_b;
        for(int i=0; i < n_d; i++)
            g.push_back(temp);

        for(char t = 'A'; t < 'A' + n_b; t++)
        {
            g[0].push_back(t);
        }
    }

    vector<Node> successor( Node &p_state)
    {
        vector<Node> n_states;
        //cout<<"\nThe current state is \n";
        //print_Node(p_state);
        //cout<<endl;
        for(unsigned int i=0; i< p_state.g.size(); i++)
        {
            if(p_state.g[i].size() != 0)
            {

                Node t_state = p_state;
                char p = t_state.g[i].back();
                t_state.g[i].pop_back();
                //print_Node(t_state);
                for(unsigned int j=0; j< p_state.g.size(); j++)
                {
                    //cout<<"\nThe successor states are for this state are"<<endl;
                    if(j != i)
                    {
                        //cout<<"\n j"<<j<<endl;
                        t_state.g[j].push_back(p);
                        //cout<<endl<<"Modified t_state";
                        //print_Node(t_state);
                        //cout<<endl;
                        n_states.push_back(t_state);
                        t_state.g[j].pop_back();
                    }
                }
            }
        }
        for(unsigned int i=0; i< n_states.size(); i++)
        {
            n_states[i].head = &p_state;
            n_states[i].cost = p_state.cost + 1;
        }
        return n_states;
    }

    Node prob_gen(Node &p_state)
    {
        srand (time(NULL));
        //srand(10);
        int num1 = rand()%100;
        //cout<<"The num1 value is "<<num1<<endl;
        //int num1 = 10;

        for(int i = 0; i < num1; i++)
        {

            vector<Node> s_states = successor(p_state);
            //srand (time(NULL));
            int num2 = rand()%s_states.size();
            p_state = s_states[num2];
        }

        return p_state;
    }

    void print_Node(Node p_state)
    {
        //cout<<"\nThe t_cost of the Node is: "<<p_state.t_cost<<endl;

        for(unsigned int i=0; i< p_state.g.size(); i++)
        {
            cout<<i<<"  |  ";
            for(unsigned int j=0; j< p_state.g[i].size(); j++)
            {
                cout<<"\t"<<p_state.g[i][j];
            }
                cout<<endl;

        }

    }

    bool goal_test(Node p_state)
    {
        int size = p_state.g[0].size();
        if(size == this->n_b)
        {
            for( int i=0; i< size; i++)
            {
                if(p_state.g[0][i] != 'A'+i )
                    return 0;
            }
            return 1;
        }
        return 0;
    }
};

bool compare_Nodes(Node a, Node b)
{
    for(int i=0 ; i<a.n_d; i++)
    {
        if(a.g[i].size() != b.g[i].size())
            return false;
        else
        {
            for(unsigned int j=0; j < a.g[i].size(); j++)
                if(a.g[i][j] != b.g[i][j])
                    return false;

        }

    }
    return true;
}

Node bfs(Node blocksWorld)
{
    queue <Node> frontier;
    vector <Node> explored;

    Node t_node = blocksWorld;
    t_node.found = false;
    cout<<endl<<endl<<"Enter the BFS"<<endl<<endl;
    if(blocksWorld.goal_test(blocksWorld))
    {
        blocksWorld.found = true;
        return blocksWorld;
    }

    frontier.push(blocksWorld);
    int it=0;
    while(!frontier.empty())
    {
        Node _state = frontier.front();
        frontier.pop();
        //cout<<endl;
        //_state.print_Node(_state);
        //cout<<endl<<"The iteration number is \t: "<<it<<endl;
        explored.push_back(_state);
        vector<Node> succ = _state.successor(_state);
        for(unsigned int i=0; i < succ.size();i++)
        {
            bool cond1 = false;
            bool cond2 = false;
            for(unsigned int j=0; j < explored.size();j++)
            {
                if(compare_Nodes(explored[j], succ[i]))
                {
                    cond1 = true; break;
                }
            }
            queue <Node> t_f = frontier;
            for(unsigned int j=0; j < frontier.size();j++)
            {

                if(compare_Nodes(t_f.front(), succ[i]))
                {
                    cond2 = true; break;
                }
                t_f.pop();
            }
            if(!cond1 && !cond2)
            {
                if(succ[i].goal_test(succ[i]))
                {
                    succ[i].found = true;
                    cout<<endl<<"The number of iterations for BFS is \t: "<<it<<endl;
                    return succ[i];
                }
                frontier.push(succ[i]);
            }

        }
    it++;
    }

    return t_node;
}

int h(Node a)
{
//    int n_d; int n_b;
//    n_d = a.n_d;
//    n_b = a.n_b;

    int h0=0;
    char t = 'A';
    for(unsigned int i=0; i< a.g[0].size(); i++)
        {
            if(a.g[0][i] != t)
                h0= h0+2;
            t++;
        }
    //////////////////////////////////
    int h1=0;
    t = 'A';
    for(unsigned int i=0; i< a.g[0].size(); i++)
        {
            if(a.g[0][i] != t)
                h1= h1+2;
            t++;
        }
        if(a.g[0].size() < a.n_b)
        {
            h1= h1 + 2*(a.n_b - a.g[0].size());
        }
    ///////////////////////////////////
    int h2 = 0;
    for(unsigned int i=1; i< a.g.size(); i++)
        h2 = h2 + a.g[i].size();
    ///////////////////////////////////
    int h3 = h1 + h2;
    ///////////////////////////////////
    int h4 = 0;

    for(unsigned int i=1; i< a.g.size(); i++)
    {
        for(unsigned int j=0; j< a.g[i].size(); j++)
        {
            h4+=(a.g[i].size()-1-j+a.g[i][j]-'A');
        }
    }
    t = 'A';
    for(unsigned int i=0; i< a.g[0].size(); i++)
        {
            if(a.g[0][i] != t)
                h4= h4+2;
            t++;
        }
    //////////////////////////////////
    int h5=0;
    if(a.g[0].size() == 0)
        h5+=a.n_b;
    else
    {
        t = 'A';
        unsigned int i=0;
        int c = 0;
        for(unsigned int i=0; i< a.g[0].size(); i++)
        {
                if(a.g[0][i] == t)
                    {
                        c++;
                        h5-=3;
                    }
                else
                    break;
        }
        for(unsigned int i=c; i< a.g[0].size(); i++)
        {
                if(a.g[0][i] != t)
                    h5+=1;
                    t++;
        }
//        for(unsigned int i=1; i< a.g.size(); i++)
//        {
//            for(unsigned int j=0; j< a.g[i].size(); j++)
//            {
//                h5+=2*(a.g[i].size()-1-j+a.g[i][j]-'A');
//            }
//        }
        for(unsigned int i=1; i< a.g.size(); i++)
        {
            h5+= 2*a.g[i].size();
        }
    }
    //////////////////////////////////
    if(h_value == 0)
    {
        return h0;
    }
    else if (h_value == 1)
    {

        return h1;
    }
    else if (h_value == 2 )
    {
        return h2;
    }
    else if (h_value == 3)
        return h3;
    else if (h_value == 4)
        return h4;
    else if (h_value == 5)
        return h5;
    else
        return 0;
}

bool operator<(const Node& l, const Node& r)
{
  return l.t_cost > r.t_cost;
}

void print_Pqueue(priority_queue <Node, vector<Node> > frontier)
{
    cout<<"\nThe Priority Queue is :::::\n";
    while (!frontier.empty())
    {
        Node h = frontier.top();
        //h.print_Node(h);
        //cout<<"The corrosponding cost is "<<frontier.top().cost;
        frontier.pop();
        cout<<endl;
    }
    cout<<endl;
}

Node aStar(Node blocksWorld)
{
    Node t_node = blocksWorld;

    //auto cmp = []( left, Node right) { return (left.cost) < (right.cost);};

    priority_queue <Node, vector<Node> > frontier;
    vector <Node> explored;


    t_node.found = false;

    if(blocksWorld.goal_test(blocksWorld))
    {
        blocksWorld.found = true;
        return blocksWorld;
    }
    blocksWorld.cost = 0;
    blocksWorld.t_cost = 0 + h(blocksWorld);

    cout<<"\nThe starting state is \n";
    blocksWorld.print_Node(blocksWorld);
    cout<<endl<<endl<<"Enter the A Star"<<endl<<endl;
    frontier.push(blocksWorld);
    int it=0;
    //cout<<"\nIt came here PRANOY 1\n";

    while(!frontier.empty())
    {
        Node _state = frontier.top();
        frontier.pop();
        //cout<<(_state.t_cost - _state.cost)<<endl;
        //cout<<endl<<"The present state is \n";
        //_state.print_Node(_state);
        //cout<<"\nIt came here PRANOY 2\n";
        explored.push_back(_state);
        vector<Node> succ = _state.successor(_state);
        for(unsigned int i=0; i < succ.size();i++)
        {
            bool cond1 = false;
            bool cond2 = false;
            for(unsigned int j=0; j < explored.size();j++)
            {
                if(compare_Nodes(explored[j], succ[i]))
                {
                    cond1 = true; break;
                }
            }
            priority_queue <Node> t_f = frontier;
            for(unsigned int j=0; j < frontier.size();j++)
            {

                if(compare_Nodes(t_f.top(), succ[i]))
                {
                    cond2 = true; break;
                }
                t_f.pop();
            }
            //cout<<"\nIt came here PRANOY 3\n";
            if(!cond1 && !cond2)
            {
                if(succ[i].goal_test(succ[i]))
                {
                    succ[i].found = true;
                    cout<<endl<<"The number of iterations for aSTAR is \t: "<<it<<endl;
                    cout<<endl<<"The max queue length for aSTAR is \t: "<<frontier.size()<<endl;
                    cout<<"\nThe goal state is \n\n";
                    succ[i].print_Node(succ[i]);


                    return succ[i];

                }
                succ[i].t_cost = succ[i].cost + h(succ[i]);
                frontier.push(succ[i]);
            }

        }

        if(it%50==0 && it!=0)
            cout<<endl;
        else if(it!=0)
        {
            cout<<".";
            //cout<<endl<<"iter\t"<<it<<",\t queue="<<frontier.size()<<",\t f=g+h="<<_state.t_cost<<",\t depth="<<_state.cost<<endl;
        }

    it++;
    if(it == 1500)
    {
      cout<<"\n Reached max limit braking off";
      break;
    }

    //print_Pqueue(frontier);

    }

    //cout<<endl<<"\n t_node pa aa gaya yaar The number of iterations for aSTAR is \t: "<<it<<endl;
    return t_node;
}




int main()
{
    int n_stacks;
    int n_blocks;
    cout<<"\nEnter the number of stacks::\t";
    cin>>n_stacks;
    cout<<"\nEnter the number of blocks::\t";
    cin>>n_blocks;
    Node blocksWorld(n_stacks, n_blocks);

    blocksWorld = blocksWorld.prob_gen(blocksWorld);

    //cout<<endl<<"Return of goal state "<<blocksWorld.goal_test(blocksWorld)<<endl;
    //blocksWorld.print_Node(blocksWorld);
    //Node temp = bfs(blocksWorld);
    //cout<<"The value returned by bfs is "<<temp.found;
    //cout<<endl<<"The final state returned by BFS is as follows"<<endl;
    //temp.print_Node(temp);

    do
    {
        cout<<"\nEnter the hueristic value, The available options are 0,1,2,3,4,5 ::\t";
        cin>>h_value;
        cout<<endl;
    }
    while(h_value<0 || h_value>5);
    cout<<"\n";
    aStar(blocksWorld);
    //cout<<"\n";
    //bfs(blocksWorld);



    return 0;
}
