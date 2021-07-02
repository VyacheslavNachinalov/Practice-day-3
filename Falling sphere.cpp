#include <iostream>
#include <cmath>

float const gravity = -9.8f;
float const deltaTime = 0.1f;

using namespace std;

struct Node {
	float time;
	float h;
	float v;
	float const a = gravity;
	Node *next;
};

void init (Node *node, float high)
{
	node->time = 0;
	node->h = high;
	node->v = 0;
	node->next = NULL;
}
void show(Node* head) 
{
	Node *print = head;
	while (print != NULL)
	{
		cout <<"{" << print->time << "; " << print->h <<"; "<<print->v<<"; "<< print->a<<"}"<<endl;
		print = print->next;
	}
	cout << endl;
}

void pushParameters(Node* head) 
{
	Node* moment = head;
	while (moment->next != NULL) moment = moment->next;
	moment->next = new Node;
	moment->next->time = moment->time + deltaTime;
	moment->next->h = moment->h + (moment->v * deltaTime) + (gravity*deltaTime*deltaTime/2);
	moment->next->v = moment->v + gravity * deltaTime; 
	moment->next->next = NULL;
} 
	
float collision(Node *head, float high,float lossPercent, float timeOfCollision)
{
	Node *end = head;
	while(end->next != NULL)
	{
		end = end->next;
	}
	end->time = timeOfCollision;
	end->h = 0;
	end->v = sqrt(2*(-gravity)*high) * sqrt((100-lossPercent)/100);
	return end->v;
}

int testEmulation()
{
	Node *head = new Node;
	float high = 10.0f;
	float lossPercent = 90;
	float timeOfCollision = sqrt(2.0*high/(-gravity));
	cout << timeOfCollision << endl;
	init(head,high);
	float time = 0;
	while (high > 0.001)
	{
		while (time < timeOfCollision - deltaTime)
		{
			pushParameters(head);
			time +=deltaTime;
		}
		float v = collision(head,high,lossPercent,timeOfCollision);
		time = timeOfCollision;
		float t = v/(-gravity);
		high = v*t +gravity*t*t/2;
		timeOfCollision += 2*t;
	}
	show(head);
	Node *end = head;
	while (end->next != NULL)
	{
		if (end->h < 0)
		{
			cout << "Ball in earth";
			return -1;
		}
		end = end->next;
	}
	return 0;
}

int main()
{
	testEmulation();
	if (testEmulation() == 0)
	{
		cout << "Test is OK";
	}
	else cout << "Test is Fail";
}

