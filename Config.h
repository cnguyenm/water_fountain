#pragma once
class Config
{
public:
	
	// time between frame, in msec
	static const double DELTA_TIME ; 

	// const gravity force, take 9.8 for now
	static const double GRAVITY_FORCE;

	// how much a cube will bounce back when hitting
	static const double ELASTIC_CONST;
};

