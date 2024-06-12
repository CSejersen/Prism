#include "env.h"

Env::Env() {
  rendering = false;
  screenWidth = 1600;
  screenHeight = 900;
}

// GETTERS
bool Env::isRendering() const { return rendering; }
float Env::getScreenWidth() const { return screenWidth; }
float Env::getScreenHeight() const { return screenHeight; }
float Env::getDeltaT() const { return deltaT; }

// SETTERS
void Env::setScreenWidth(float w) { screenWidth = w; }
void Env::setScreenHeight(float h) { screenHeight = h; }
void Env::setDeltaT(float t) { deltaT = t; }
void Env::setRendering(bool b) { rendering = b; }
