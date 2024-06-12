#ifndef ENV_H
#define ENV_H

class Env {
public:
  Env();

  bool isRendering() const;
  float getScreenWidth() const;
  float getScreenHeight() const;
  float getDeltaT() const;

  void setScreenWidth(float);
  void setScreenHeight(float);
  void setDeltaT(float);
  void setRendering(bool);

private:
  float screenWidth;
  float screenHeight;
  float deltaT;

  bool rendering;
};

#endif // ENV_H
