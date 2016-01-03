#include "Node.h"
#include "../Permutator/PermutationGenerator.h"

#define MAX_TAKEABLE_COINS 3

Node::Node(Node* par, size_t coins, int value) : parent(par), value(value), coins(coins), board(coins, true)
{  }

int Node::evaluate(bool max)
{
	return evaluateRec(parent, max);
}

int Node::evaluateRec(Node* current, bool max)
{
	for (auto child : current->children)
	{
		if (current->value == NO_VALUE || (max && child->value > current->value) || (!max && child->value < current->value))
			current->value = child->value;
	}

	if (current->parent == NULL)
		return current->value;

	return evaluateRec(current->parent, !max);
}


bool Node::getAvailableMoves(std::vector<Node*>& moves) const
{
	moves.clear();
	Permutations permutations;
	bool gotSomething = false;

	for (int i = 0; i < MAX_TAKEABLE_COINS; ++i)
	{
		Node* node = NULL;
		PermutationGenerator::generate(permutations, i + 1, board);
		if (permutations.size())
			gotSomething = true;

		for (auto permutation : permutations)
		{
			node = new Node(const_cast<Node *>(this), coins, value + 1);
			node->board = permutation;
			moves.push_back(node);
		}
	}
	return gotSomething;
}
