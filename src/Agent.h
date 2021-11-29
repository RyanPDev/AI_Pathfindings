#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Path.h"
#include "Vector2D.h"
#include "utils.h"
#include "Graph.h"
#include "Pathfinding.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "Greedy.h"
#include "AStar.h"

class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent* agent, float dtime) {};
	};
	Pathfinding* pathfinding;
	Vector2D* currentGoal;

private:
	SteeringBehavior* steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	// Pathfinding
	int currentTargetIndex;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Texture* sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;
	Vector2D cell2pix(Vector2D cell)
	{
		int offset = CELL_SIZE / 2;
		return Vector2D(cell.x * CELL_SIZE + offset, cell.y * CELL_SIZE + offset);
	}

public:
	Agent(Graph);
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	Path path;
	Graph graph;
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setBehavior(SteeringBehavior* behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	int getCurrentTargetIndex();
	int getPathSize();
	Vector2D getPathPoint(int idx);
	void clearPath();
	void update(float dtime, SDL_Event* event);
	void draw();
	bool loadSpriteTexture(char* filename, int num_frames = 1);

	void ChooseNewGoal(std::vector<Vector2D*> coins);

};