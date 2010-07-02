//
// ofxParticleEmitter.h
//
// Copyright (c) 2010 71Squared, ported to Openframeworks by Shawn Roske
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef _OFX_PARTICLE_EMITTER
#define _OFX_PARTICLE_EMITTER

#include "ofMain.h"
#include "ofxXmlSettings.h"

// Structure that defines the elements which make up a color
typedef struct {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;
} Color4f;

// Structure that defines a vector using x and y
typedef struct {
	GLfloat x;
	GLfloat y;
} Vector2f;

// Particle type
enum kParticleTypes 
{
	kParticleTypeGravity,
	kParticleTypeRadial
};

// Structure that holds the location and size for each point sprite
typedef struct 
{
	GLfloat x;
	GLfloat y;
	GLfloat size;
	Color4f color;
} PointSprite;

// Structure used to hold particle specific information
typedef struct 
{
	Vector2f	position;
	Vector2f	direction;
    Vector2f	startPos;
	Color4f		color;
	Color4f		deltaColor;
    GLfloat		radialAcceleration;
    GLfloat		tangentialAcceleration;
	GLfloat		radius;
	GLfloat		radiusDelta;
	GLfloat		angle;
	GLfloat		degreesPerSecond;
	GLfloat		particleSize;
	GLfloat		particleSizeDelta;
	GLfloat		timeToLive;
} Particle;

#define MAXIMUM_UPDATE_RATE 90.0f	// The maximum number of updates that occur per frame

class ofxParticleEmitter 
{
	
public:
	
	ofxParticleEmitter();
	~ofxParticleEmitter();
	
	bool	loadFromXml( const std::string& filename );
	void	update();
	void	draw( int x = 0, int y = 0 );
	void	exit();
	
protected:
	
	void	parseParticleConfig();
	void	setupArrays();
	
	ofxXmlSettings*	settings;
	
	int				emitterType;
	ofImage*		texture;												
	Vector2f		sourcePosition, sourcePositionVariance;			
	GLfloat			angle, angleVariance;								
	GLfloat			speed, speedVariance;	
    GLfloat			radialAcceleration, tangentialAcceleration;
    GLfloat			radialAccelVariance, tangentialAccelVariance;
	Vector2f		gravity;	
	GLfloat			particleLifespan, particleLifespanVariance;			
	Color4f			startColor, startColorVariance;						
	Color4f			finishColor, finishColorVariance;
	GLfloat			startParticleSize, startParticleSizeVariance;
	GLfloat			finishParticleSize, finishParticleSizeVariance;
	GLint			maxParticles;
	GLint			particleCount;
	GLfloat			emissionRate;
	GLfloat			emitCounter;	
	GLfloat			elapsedTime;
	GLfloat			duration;
    
	int				blendFuncSource, blendFuncDestination;
	
	//////////////////// Particle ivars only used when a maxRadius value is provided.  These values are used for
	//////////////////// the special purpose of creating the spinning portal emitter
	GLfloat			maxRadius;						// Max radius at which particles are drawn when rotating
	GLfloat			maxRadiusVariance;				// Variance of the maxRadius
	GLfloat			radiusSpeed;					// The speed at which a particle moves from maxRadius to minRadius
	GLfloat			minRadius;						// Radius from source below which a particle dies
	GLfloat			rotatePerSecond;				// Numeber of degress to rotate a particle around the source pos per second
	GLfloat			rotatePerSecondVariance;		// Variance in degrees for rotatePerSecond
	
	//////////////////// Particle Emitter iVars
	bool			active, useTexture;
	GLint			particleIndex;	// Stores the number of particles that are going to be rendered
	
	
	///////////////////// Render
	GLuint			verticesID;		// Holds the buffer name of the VBO that stores the color and vertices info for the particles
	Particle*		particles;		// Array of particles that hold the particle emitters particle details
	PointSprite*	vertices;		// Array of vertices and color information for each particle to be rendered
	
};

#endif