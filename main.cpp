#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <stdlib.h>

#include <fstream>
#include <sstream>
#include <string> 


using namespace std;

#define mazeSizeX 41
#define mazeSizeY 61
#define robotSize 5
#define wallthick 1

void build_maze(int maze[mazeSizeX][mazeSizeY])
{
    // maze field
    for(int j = 0; j < mazeSizeY; j++)
    {
        for(int i = 0; i < mazeSizeX; i++)
        {
            maze[i][j] = 1;
        }
    }
    // adding walls
    // top and bottom walls
    for(int i = 0; i < mazeSizeX; i++)
    {
        for(int j = 0; j < wallthick; j++){
            maze[i][j] = 0;
            maze[i][mazeSizeY-j-1] = 0;
        }
    }
    //left and right walls
    for(int i = 0; i < mazeSizeY; i++)
    {
        for(int j = 0; j < wallthick; j++){
            maze[j][i] = 0;
            maze[mazeSizeX-j-1][i] = 0;
        }
    }
	//other walls
	for(int i = 37; i < mazeSizeX; i++)
	{
		maze[i][18] = 0;
	}
	for(int i = 34; i < mazeSizeX; i++)
	{
		maze[i][30] = 0;
	}
	for(int i = 37; i < mazeSizeX; i++)
	{
		maze[i][42] = 0;
	}
}

void build_cup(int maze[mazeSizeX][mazeSizeY], bool available_cups[24]){
	int cup[24][2] = {{1955/50, 1005/50},
						{1955/50, 1395/50},
						{1955/50, 1605/50},
						{1955/50, 1995/50},
						{1650/50, 1065/50},
						{1650/50, 1335/50},
						{1650/50, 1665/50},
						{1650/50, 1935/50},
						{1200/50, 300/50},
						{1200/50, 1270/50},
						{1200/50, 1730/50},
						{1200/50, 2700/50},
						{1080/50, 450/50},
						{1080/50, 2550/50},
						{800/50, 1100/50},
						{800/50, 1900/50},
						{510/50, 450/50},
						{510/50, 2550/50},
						{400/50, 300/50},
						{400/50, 950/50},
						{400/50, 2050/50},
						{400/50, 2700/50},
						{100/50, 670/50},
						{100/50, 2330/50}
	};
	/*int cup[0][2] = {1955/50, 1005/50};
    int cup2[2] = {1955/50, 1395/50};
    int cup3[2] = {1955/50, 1605/50};
    int cup4[2] = {1955/50, 1995/50};
    int cup5[2] = {1650/50, 1065/50};
    int cup6[2] = {1650/50, 1335/50};
    int cup7[2] = {1650/50, 1665/50};
    int cup8[2] = {1650/50, 1935/50};    
	int cup9[2] = {1200/50, 300/50};
    int cup10[2] = {1200/50, 1270/50};
    int cup11[2] = {1200/50, 1730/50};
    int cup12[2] = {1200/50, 2700/50};
    int cup13[2] = {1080/50, 450/50};
    int cup14[2] = {1080/50, 2550/50};
    int cup15[2] = {800/50, 1100/50};
    int cup16[2] = {800/50, 1900/50};
    int cup17[2] = {510/50, 450/50};
    int cup18[2] = {510/50, 2550/50};
    int cup19[2] = {400/50, 300/50};
    int cup20[2] = {400/50, 950/50};
    int cup21[2] = {400/50, 2050/50};
    int cup22[2] = {400/50, 2700/50};
    int cup23[2] = {100/50, 670/50};
    int cup24[2] = {100/50, 2330/50};*/
    
    for(int i =0; i<24; i++){
    	if(available_cups[i] == 1){
    		maze[cup[i][0]][cup[i][1]]=0;
		}
	}
    
    /*maze[cup1[0]][cup1[1]] = 0;
	maze[cup2[0]][cup2[1]] = 0;
	maze[cup3[0]][cup3[1]] = 0;
	maze[cup4[0]][cup4[1]] = 0;
	maze[cup5[0]][cup5[1]] = 0;
	maze[cup6[0]][cup6[1]] = 0;
	maze[cup7[0]][cup7[1]] = 0;
	maze[cup8[0]][cup8[1]] = 0;
	maze[cup9[0]][cup9[1]] = 0;
	maze[cup10[0]][cup10[1]] = 0;
	maze[cup11[0]][cup11[1]] = 0;
	maze[cup12[0]][cup12[1]] = 0;
	maze[cup13[0]][cup13[1]] = 0;
	maze[cup14[0]][cup14[1]] = 0;
	maze[cup15[0]][cup15[1]] = 0;
	maze[cup16[0]][cup16[1]] = 0;
	maze[cup17[0]][cup17[1]] = 0;
	maze[cup18[0]][cup18[1]] = 0;
	maze[cup19[0]][cup19[1]] = 0;
	maze[cup20[0]][cup20[1]] = 0;
	maze[cup21[0]][cup21[1]] = 0;
	maze[cup22[0]][cup22[1]] = 0;
	maze[cup23[0]][cup23[1]] = 0;
	maze[cup24[0]][cup24[1]] = 0;*/
}

class PosNode
{
public:
    int pos[2];
};

bool build_obstacles(int middlePoint[2], int wallThick, int maze[mazeSizeX][mazeSizeY], int weight, int goal[2]){
    int middlePointX = middlePoint[0];
    int middlePointY = middlePoint[1];
    int halfWallThick = (wallThick-1)/2;
    bool overlap = false;

    for(int j = middlePointY-halfWallThick; j <= middlePointY+halfWallThick; j++)
    {
        for(int i = middlePointX-halfWallThick; i <= middlePointX + halfWallThick; i++)
        {
            if(i == goal[0] && j == goal[1]){
                overlap = true;
                return true;
            }
        }
    }
    if(overlap == false){
        for(int j = middlePointY-halfWallThick; j <= middlePointY+halfWallThick; j++)
        {
            for(int i = middlePointX-halfWallThick; i <= middlePointX + halfWallThick; i++)
            {
                if(i>=0&&i<=mazeSizeX&&j>=0&&j<=mazeSizeY)
                {
                    if(maze[i][j] != 0){
                        maze[i][j] = weight;
                    }
                }
                if(i == goal[0] && j == goal[1]){
                    overlap = true;
                }
            }
        }
        return false;
    }
}

class Node
{
public:
    Node()
    {
        g = 0;
        h = 0;
        f = 0;
    }
    double g;
    double h;
    double f;
    double move_cost;
    int priority_stamp;
    vector<PosNode> path;

    int PosX()
    {
        return pos[0];
    }
    int PosY()
    {
        return pos[1];
    }
    void PrintPos()
    {
        cout << "Pos: (" << pos[0] << ", " << pos[1] << "\n";
    }
    void GivePos(int new_pos[2])
    {
        pos[0] = new_pos[0];
        pos[1] = new_pos[1];
    }
private:
    int pos[2];
};

void Up(int* new_pos, int pos[2])
{
    new_pos[0] = pos[0];
    new_pos[1] = pos[1];
    new_pos[1] -= 1;
}
void UpRight(int* new_pos, int pos[2])
{
    new_pos[0] = pos[0];
    new_pos[1] = pos[1];
    new_pos[0] += 1;
    new_pos[1] -= 1;
}
void Right(int* new_pos, int pos[2])
{
    new_pos[0] = pos[0];
    new_pos[1] = pos[1];
    new_pos[0] += 1;
}
void DownRight(int* new_pos, int pos[2])
{
    new_pos[0] = pos[0];
    new_pos[1] = pos[1];
    new_pos[0] += 1;
    new_pos[1] += 1;
}
void Down(int* new_pos, int pos[2])
{
    new_pos[0] = pos[0];
    new_pos[1] = pos[1];
    new_pos[1] += 1;
}
void DownLeft(int* new_pos, int pos[2])
{
    new_pos[0] = pos[0];
    new_pos[1] = pos[1];
    new_pos[0] -= 1;
    new_pos[1] += 1;
}
void Left(int*new_pos, int pos[2])
{
    new_pos[0] = pos[0];
    new_pos[1] = pos[1];
    new_pos[0] -= 1;
}
void UpLeft(int* new_pos, int pos[2])
{
    new_pos[0] = pos[0];
    new_pos[1] = pos[1];
    new_pos[0] -= 1;
    new_pos[1] -= 1;
}

bool OnObstacle(int new_pos[2], int maze[mazeSizeX][mazeSizeY])
{
	int middlePointX = new_pos[0];
	int middlePointY = new_pos[1];
	int halfRobotSize = (robotSize-1)/2;
	for(int j = middlePointY-halfRobotSize; j <= middlePointY+halfRobotSize; j++)
    {
        for(int i = middlePointX-halfRobotSize; i <= middlePointX + halfRobotSize; i++)
        {
            if(maze[i][j] == 0){
                return true;
            }
        }
    }
    return false;
}

bool isValid(int new_pos[2], int maze[mazeSizeX][mazeSizeY])
{
    if(new_pos[0] <=0 || new_pos[0]>= mazeSizeX-1)
    {
        return false;
    }
    if(new_pos[1] <=0 || new_pos[1]>= mazeSizeY-1)
    {
        return false;
    }
    /*if(maze[new_pos[0]][new_pos[1]] == 0)
    {
        return false;
    }*/
    if(OnObstacle(new_pos, maze))
    {
        return false;
    }
    else
    {
        return true;
    }
}

vector<Node> FindSuccessors(int pos[2], int maze[mazeSizeX][mazeSizeY])
{
    double strait = 1;
    double diagnal = sqrt(2);
    vector<Node> output;
    Node successor;
    int new_pos[2];
    // the priority should start from low cost movements to higher cost movements, since it goes through a priority queue!!
    // this up right down left(cost 1) upright downright downleft upleft(cost 1.4142) priority is crucial in promising a complete solution!!
    Up(new_pos, pos);
    if(isValid(new_pos, maze)==true)
    {
        successor.GivePos(new_pos);
        successor.move_cost = strait;
        output.push_back(successor);
    }
    Right(new_pos, pos);
    if(isValid(new_pos, maze)==true)
    {
        successor.GivePos(new_pos);
        successor.move_cost = strait;
        output.push_back(successor);
    }
    Down(new_pos, pos);
    if(isValid(new_pos, maze)==true)
    {
        successor.GivePos(new_pos);
        successor.move_cost = strait;
        output.push_back(successor);
    }
    Left(new_pos, pos);
    if(isValid(new_pos, maze)==true)
    {
        successor.GivePos(new_pos);
        successor.move_cost = strait;
        output.push_back(successor);
    }
    UpRight(new_pos, pos);
    if(isValid(new_pos, maze)==true)
    {
        successor.GivePos(new_pos);
        successor.move_cost = diagnal;
        output.push_back(successor);
    }
    DownRight(new_pos, pos);
    if(isValid(new_pos, maze)==true)
    {
        successor.GivePos(new_pos);
        successor.move_cost = diagnal;
        output.push_back(successor);
    }
    DownLeft(new_pos, pos);
    if(isValid(new_pos, maze)==true)
    {
        successor.GivePos(new_pos);
        successor.move_cost = diagnal;
        output.push_back(successor);
    }
    UpLeft(new_pos, pos);
    if(isValid(new_pos, maze)==true)
    {
        successor.GivePos(new_pos);
        successor.move_cost = diagnal;
        output.push_back(successor);
    }
    return output;
}

double HeuristicFunctionManhattan(Node start, Node goal)
{
    double cost = abs(start.PosX() - goal.PosX()) + abs(start.PosY() - goal.PosY());
    return cost;
}

double HeuristicFunctionDiagnal(Node start, Node goal)
{
    int strait = 1;
    double diagnal = sqrt(2);
    int dx = abs(start.PosX()-goal.PosX());
    int dy = abs(start.PosY()-goal.PosY());
    double cost = strait*(dx + dy) + (diagnal - 2*strait)*min(dx, dy);
    return cost;
}

double HeuristicFunctionExactDistance(Node start, Node goal){
    double cost = sqrt((start.PosX()-goal.PosX())*(start.PosX()-goal.PosX()) + (start.PosY()-goal.PosY())*(start.PosY()-goal.PosY()));
    cout << "cost: " << cost << "\n";
    return cost;
}

void PrintPath(vector<PosNode> p, vector<PosNode> q, int maze[mazeSizeX][mazeSizeY])
{
    cout << "path: ";
    if(p[0].pos[0] == -1000){
        cout << "(" << p[0].pos[0] << "," << p[0].pos[1] << ") \n";
    }
    else{
        for(unsigned int i = 0; i < p.size(); i++)
        {
            cout << "(" << p[i].pos[0] << "," << p[i].pos[1] << ") ";
            maze[p[i].pos[0]][p[i].pos[1]] = 99;  //print out path as 8

        }
    }
    cout << "\n";
    
    cout << "simplified path: ";
    if(q[0].pos[0] == -1000){
        cout << "(" << q[0].pos[0] << "," << q[0].pos[1] << ") \n";
    }
    else{
        for(unsigned int i = 0; i < q.size(); i++)
        {
            cout << "[" << q[i].pos[0] << "," << q[i].pos[1] << "], ";
            maze[q[i].pos[0]][q[i].pos[1]] = 39;  //print out path as 8

        }
    }
    cout << "\n";
}
void PMaze(int start[2], int goal[2], int maze[mazeSizeX][mazeSizeY])
{
	for(int j = mazeSizeY-1; j >= 0; j--)
    {
    	cout << "[";
        for(int i = 0; i <= mazeSizeX-2 ; i++)
        {	
        	cout << maze[i][j];
        	cout << ", ";
    	}
    	cout << maze[mazeSizeX - 1][j];
    	cout << "],";
	}
}

void PrintMaze(int start[2], int goal[2], int maze[mazeSizeX][mazeSizeY])
{
    if(start[0] > mazeSizeX-wallthick-1 || start[0] < wallthick || start[1] > mazeSizeY-wallthick-1 || start[1] < wallthick){
        return;
    }
    cout << "\n";
    maze[start[0]][start[1]] = 85;  //set maze start point as 85
    maze[goal[0]][goal[1]] = 50;  //set maze goal point as 89
    char cmaze[mazeSizeX][mazeSizeY];
    for(int j = mazeSizeY-1; j >= 0; j--)
    {
        for(int i = 0; i <= mazeSizeX-1 ; i++)
        {
            if(maze[i][j] == 0)
            {
                cmaze[i][j] = 'H';
            }
            else if(maze[i][j] == 88)
            {
                cmaze[i][j] = '#';
            }
            else if(maze[i][j] == 84)
            {
                cmaze[i][j] = '~';
            }
            else if(maze[i][j] == 1)
            {
                cmaze[i][j] = '.';
            }
            else if(maze[i][j] == 85)
            {
                cmaze[i][j] = 'S';
            }
            else if(maze[i][j] == 50)
            {
                cmaze[i][j] = 'G';
            }
            else if(maze[i][j] == 99)
            {
                cmaze[i][j] = '@';
            }
            else if(maze[i][j] == 39)
            {
                cmaze[i][j] = '!';
            }
            else{
                cmaze[i][j] = '*';
            }
            cmaze[40][60] = '@';
            cmaze[0][0] = '@';
            cout << cmaze[i][j];
            cout << " ";
        }
        cout << "\n";
    }
}

int maze_field_cost(int maze[mazeSizeX][mazeSizeY], int x, int y){
    int cost = 0;
    if(maze[x][y] != 1 && maze[x][y] != 0){
        cost = maze[x][y];
    }
    else{
        cost = 0;
    }
    return cost;
}

bool operator<(Node const& n1, Node const& n2)
{
    if(abs(n1.f-n2.f)<0.000001){
        return n1.priority_stamp > n2.priority_stamp;
    }
    return n1.f > n2.f;
}


vector<PosNode> AStar(int start_pos[2], int goal_pos[2], int maze[mazeSizeX][mazeSizeY])
{
    int priority_count = 0;
    int weight = 1;
    Node start, goal;
    start.GivePos(start_pos);
    goal.GivePos(goal_pos);
    priority_queue<Node> priority_q;

    PosNode curr_pos;
    curr_pos.pos[0] = -1000;
    curr_pos.pos[1] = -1000;
    Node fail;
    fail.path.push_back(curr_pos);

    bool visited[mazeSizeX][mazeSizeY] = {0};
    if(maze[goal_pos[0]][goal_pos[1]] == 0)
    {
        cout << "goal unreachable\n";
        return fail.path;
    }
    if(start_pos[0]<wallthick || start_pos[0]>mazeSizeX-wallthick-1 || start_pos[1]<wallthick || start_pos[1]>mazeSizeY-wallthick-1 || goal_pos[0]<wallthick || goal_pos[0]>mazeSizeX-wallthick-1 || goal_pos[1]<wallthick || goal_pos[1]>mazeSizeY-wallthick-1)
    {
        cout << "invalid input\n";
        return fail.path;
    }
    start.move_cost = 0;
    start.g = 0;
    start.h = HeuristicFunctionDiagnal(start, goal); //<----change method here
    start.f = start.g + start.h*weight;
    priority_count ++;
    start.priority_stamp = priority_count;
    priority_q.push(start);
    while(!priority_q.empty())
    {
        Node top_node = priority_q.top();
        PosNode pos;
        pos.pos[0] = top_node.PosX();
        pos.pos[1] = top_node.PosY();
        if(top_node.PosX() == goal.PosX() && top_node.PosY() == goal.PosY())
        {
            top_node.path.push_back(pos);
            return top_node.path;
        }
        visited[top_node.PosX()][top_node.PosY()] = true;
        priority_q.pop();
        vector<Node> successors = FindSuccessors(pos.pos, maze);
        for(unsigned int i = 0; i < successors.size(); i++)
        {
            Node succ = successors[i];
            succ.path = top_node.path;
            succ.g = succ.move_cost + top_node.g + maze_field_cost(maze, succ.PosX(), succ.PosY());
            if(!visited[succ.PosX()][succ.PosY()])
            {
                maze[succ.PosX()][succ.PosY()] = 84;
                succ.path.push_back(pos);
                succ.h = HeuristicFunctionDiagnal(succ, goal); //<----change method here
                succ.f = succ.g + succ.h*weight;
                priority_count ++;
                succ.priority_stamp = priority_count;
                priority_q.push(succ);
                visited[succ.PosX()][succ.PosY()] = true;

            }
        }
    }
    cout << "search fail\n";
    return fail.path;
}

vector<PosNode> bresenhams_line_alg(vector<PosNode> path, int maze[mazeSizeX][mazeSizeY])
{
    if(path[0].pos[0] == -1000){
        return path;
    }
    PosNode start = path.front();
    vector<PosNode> output;
    bool steep_swap = false;
    bool right_to_left_swap = false;
    for(unsigned int i = 1; i < path.size(); i++)
    {
        PosNode goal = path[i];
        bool steep = false;
        bool walkable = true;

        if(abs(goal.pos[1]-start.pos[1])>abs(goal.pos[0]-start.pos[0]))
        {
            steep = true;
        }
        if(steep)
        {
            swap(start.pos[0], start.pos[1]);
            swap(goal.pos[0], goal.pos[1]);
            steep_swap = true;
        }
        if(start.pos[0]>goal.pos[0])
        {
            swap(start.pos[0], goal.pos[0]);
            swap(start.pos[1], goal.pos[1]);
            right_to_left_swap = true;
        }

        int delta_x = goal.pos[0] - start.pos[0];
        int delta_y = abs(goal.pos[1] - start.pos[1]);
        int error = delta_x;
        int y_step;
        int y = start.pos[1];
        if(start.pos[1] < goal.pos[1])
        {
            y_step = 1;
        }
        else
        {
            y_step = -1;
        }
        for(int x=start.pos[0]; x<=goal.pos[0]; x++)
        {
            if(steep)
            {
                if(maze[y][x] == 0)
                {
                    walkable = false;
                }
            }
            else
            {
                if(maze[x][y] == 0)
                {
                    walkable = false;
                }
            }
            error -= 2*delta_y;
            if(error <= 0)
            {
                y += y_step;
                error += 2*delta_x;
            }
        }
        if(steep_swap == true){
            swap(start.pos[0], start.pos[1]);
            swap(goal.pos[0], goal.pos[1]);
            steep_swap = false;
        }
        if(right_to_left_swap == true){
            swap(start.pos[0], goal.pos[0]);
            swap(start.pos[1], goal.pos[1]);
            right_to_left_swap = false;
        }
        if(walkable == false)
        {
            output.push_back(path[i-1]);
            start = path[i-1];
        }

    }
    output.push_back(path.back());
    return output;
}

int get_x(vector<PosNode> path){
    PosNode a = path.front();
    int x = a.pos[0];
    return x;
}

int get_y(vector<PosNode> path){
    PosNode a = path.front();
    int y = a.pos[1];
    return y;
}

void prediction_of_movement(int maze[mazeSizeX][mazeSizeY],int obstacle_pos[2], int move_vector[2], int goal_p[2]){
    int prediction_ratio = 2;
    int prediction_point[2] = {obstacle_pos[0] + prediction_ratio*move_vector[0], obstacle_pos[1] + prediction_ratio*move_vector[1]};
    int start[2] = {obstacle_pos[0], obstacle_pos[1]};
    int goal[2] = {prediction_point[0], prediction_point[1]};
    PosNode pos;
    vector<PosNode> prediction;
    bool steep = false;
    bool walkable = true;
    if(abs(goal[1]-start[1])>abs(goal[0]-start[0]))
    {
        steep = true;
    }
    if(steep)
    {
        swap(start[0], start[1]);
        swap(goal[0], goal[1]);
    }
    if(start[0]>goal[0])
    {
        swap(start[0], goal[0]);
        swap(start[1], goal[1]);
    }
    int delta_x = goal[0] - start[0];
    int delta_y = abs(goal[1] - start[1]);
    int error = delta_x;
    int y_step;
    int y = start[1];
    if(start[1] < goal[1])
    {
        y_step = 1;
    }
    else
    {
        y_step = -1;
    }
    //cout << start[0] << " " << goal[0] << "\n";
    for(int x=start[0]; x<=goal[0]; x++)
    {
        if(steep == true)
        {
            //cout << "x: " << y << " y: " << x << "\n";
            if(maze[y][x] == 0)
            {
                walkable = false;
            }
            else{
                maze[y][x] = 2;
                pos.pos[0] = y;
                pos.pos[1] = x;
                prediction.push_back(pos);
            }
        }
        else
        {
            //cout << "x: " << x << " y: " << y << "\n";
            if(maze[x][y] == 0)
            {
                walkable = false;
            }
            else{
                maze[x][y] = 2;
                pos.pos[0] = x;
                pos.pos[1] = y;
                prediction.push_back(pos);
            }
        }
        error -= 2*delta_y;
        if(error <= 0)
        {
            y += y_step;
            error += 2*delta_x;
        }
    }
    int j = 100;
    int cost = 0;
    for(unsigned int i = prediction.size() -1; i > 0; i--)
    {
        //cout << "(" << prediction[i].pos[0] << ", " << prediction[i].pos[1] << ")\n";
        cost = prediction.size() - i;
        if(cost<=1){
            cost = 2;
        }
        build_obstacles(prediction[i].pos, robotSize, maze, cost, goal_p);
        j+=i*100;
    }
}

float move_degree(int start_pos[2], vector<PosNode> path){
    if(path[0].pos[0] == -1000){
        int output = -1000;
        return output;
    }
    PosNode start;
    start.pos[0] = start_pos[0];
    start.pos[1] = start_pos[1];
    PosNode goal = path[0];
    float pi = 3.1415926;
    int num = goal.pos[1] - start.pos[1];
    int den = goal.pos[0] - start.pos[0];
    float in_radius = 0;
    float in_degree = 0;
    if (num!=0 && den!=0){
        float radius = atan((float)num / den);
        if (num > 0 && den > 0){
            in_radius = radius;
        }
        else if (num > 0 && den < 0){
            in_radius = pi + radius;
        }
        else if (num < 0 && den < 0){
            in_radius = pi + radius;
        }
        else{
            in_radius = 2*pi + radius;
        }
    }
    else if (num == 0 && den > 0){
        in_radius = 0;
    }
    else if (num == 0 && den < 0){
        in_radius = pi;
    }
    else if (num > 0 and den == 0){
        in_radius = pi/2;
    }
    else if (num < 0 && den == 0){
        in_radius = 3*pi/2;
    }
    else{
        cout << "move degree error\n";
    }
    in_degree = in_radius * 180 / pi;
    return in_degree;
}

int big_to_small_maze(int big){
    int small = round((double)big/50);
    return small;
}

int main()
{
	int start_pos[2];
    start_pos[0] = big_to_small_maze(800);//<---my_pos_x
    start_pos[1] = big_to_small_maze(300);//<---my_pos_y
    int goal_pos[2];
    goal_pos[0] = big_to_small_maze(1800);//<---goap_x
    goal_pos[1] = big_to_small_maze(2800);//<---goap_y
	for(int i = 1; i <= 55; i+=2){
	    int maze[mazeSizeX][mazeSizeY];
	    //bool available_cups[24] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};//<---from somewhere
	    bool available_cups[24] = {0};//<---from somewhere
	    build_maze(maze);
	    build_cup(maze, available_cups);
	    int obstacle_a[2] = {0,0};
	    int obstacle_b[2] = {5000,5000};
	    int obstacle_c[2] = {0,0};
	    if(i<=33){
	    	obstacle_a[0] = (int)(1500-40*i)/50;  //<---from camera
	    	obstacle_a[1] = (int)(800+40*i)/50;
		    obstacle_c[0] = (int)(500+40*i)/50;//<---from camera
		    obstacle_c[1] = (int)(1800)/50;
		}
		else{
			obstacle_a[0] = (int)(1500-40*33)/50;  //<---from camera
	    	obstacle_a[1] = (int)(800+40*33)/50;
		    obstacle_c[0] = (int)(500+40*33)/50;//<---from camera
		    obstacle_c[1] = (int)(1800)/50;
		}
	    
	    
	    
	    int vec1[2] = {-3,3};
	    int vec2[2] = {3,0};
	    prediction_of_movement(maze, obstacle_a, vec1, goal_pos);
		prediction_of_movement(maze, obstacle_c, vec2, goal_pos);
		
	    bool blocked = false;
	    bool is_blocked_a = build_obstacles(obstacle_a, robotSize, maze, 0, goal_pos);
	    bool is_blocked_b = build_obstacles(obstacle_b, robotSize, maze, 0, goal_pos);
	    bool is_blocked_c = build_obstacles(obstacle_c, robotSize, maze, 0, goal_pos);
	    vector<PosNode> a = AStar(start_pos, goal_pos, maze);
		a.erase(a.begin());
	    vector<PosNode> b = bresenhams_line_alg(a, maze);
	    //PrintPath(a, maze);
	    PrintPath(a, b, maze); 
	    PrintMaze(start_pos, goal_pos, maze);
	    //cout << "degree: " << move_degree(start_pos, a) << "\n";//--->output degree!!
	    if(is_blocked_a || is_blocked_b || is_blocked_c){
	        blocked = true;
	        cout << "blocked\n";
	    }
	    
	    
	    ofstream mf("maze.txt");
	    if(mf.is_open()){
	    	cout << "open !!!";
	
	        for(int i = 0; i < 41; i++){
	            for(int j = 0; j < 61; j++){
	                std::string x;
	                x = std::to_string(maze[i][j]);
	                mf << x << " ";
	            }
	            mf << '\n';
	        }
	        
	        mf.close();
	    }
	    else cout << "can't open the file";
	    
	    start_pos[0] = a[1].pos[0];
	    start_pos[1] = a[1].pos[1];
	    system("pause");
        system("cls");
	} 
    
    
    return 0;
}

