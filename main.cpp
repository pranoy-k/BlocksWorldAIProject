#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <queue>
#include <set>
using namespace std;



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
    bool found = false;
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

	vector<Node> successor(Node p_state)
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
		return n_states;
	}

	Node prob_gen(Node &p_state)
	{
	    srand (time(NULL));
		int num1 = rand()%50;
		//cout<<"The num1 value is "<<num1<<endl;
		//int num1 = 10;

		for(int i = 0; i < num1; i++)
		{

			vector<Node> s_states = successor(p_state);
			srand (time(NULL));
            int num2 = rand()%s_states.size();
			p_state = s_states[num2];
			//print_Node(p_state);
		}

		return p_state;
	}

	void print_Node(Node p_state)
    {
        //cout<<endl<<"The Graph is as follows"<<endl;
        for(unsigned int i=0; i< p_state.g.size(); i++)
        {
            //cout<<"IT CAME HERE PRANOY";
            for(unsigned int j=0; j< p_state.g[i].size(); j++)
            {
                cout<<p_state.g[i][j]<<"\t";
            }
            if(p_state.g[i].size() == 0)
                cout<<"___"<<endl;
            else
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

Node bfs(Node blocksWorld)
{
    queue <Node> frontier;
    vector <Node> explored;

    Node t_node = blocksWorld;
    t_node.found = false;

    if(blocksWorld.goal_test(blocksWorld))
    {
        blocksWorld.found = true;
        return blocksWorld;
    }

    frontier.push(blocksWorld);

    while(!frontier.empty())
    {
        Node _state = frontier.front();
        frontier.pop();

        explored.insert(_state);
        vector<Node> succ = _state.successor(_state);
        for(unsigned int i=0; i < succ.size();i++)
        {
            if(explored.find(succ[i]) == explored.end() && fr_vec.find(succ[i]) == fr_vec.end())
            {
                if(succ[i].goal_test(succ[i]))
                {
                    succ[i].found = true;
                    return succ[i];
                }
                frontier.push(succ[i]); fr_vec.insert(succ[i]);
            }

        }

    }

    return t_node;
}
/*
bool operator< (const Node &left, const Node &right)
{
    return left.x < right.x;
}
*/
int main()
{
    Node blocksWorld(3, 5);

    cout<<"Return of goal state "<<blocksWorld.goal_test(blocksWorld)<<endl;
    //blocksWorld.print_Node(blocksWorld);

    blocksWorld = blocksWorld.prob_gen(blocksWorld);
    blocksWorld.print_Node(blocksWorld);
    cout<<endl<<"Return of goal state "<<blocksWorld.goal_test(blocksWorld)<<endl;
    //blocksWorld.print_Node(blocksWorld);

    //bfs(blocksWorld);
    return 0;
}
