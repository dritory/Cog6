#pragma once
class Player {
public:
	Player();
	~Player();

	//tile coords
	bool build(int x, int y, int z);

	void Update();
};

