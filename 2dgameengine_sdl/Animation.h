#ifndef ANIMATION_N
#define ANIMATION_H

class Animation {
public:
	unsigned int index;
	unsigned int numFrames;
	unsigned int animationSpeed;
	Animation() {};
	Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed) {
		this->index = index;
		this->numFrames = numFrames;
		this->animationSpeed = animationSpeed;
	};
};

#endif