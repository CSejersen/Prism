#ifndef FFMPEG_H
#define FFMPEG_H

#include <cstddef>
#include <memory>

class ffmpeg {
public:
  static ffmpeg *startRendering(std::size_t width, std::size_t height,
                                std::size_t fps);
  bool sendFrameFlipped(void *data, std::size_t width, std::size_t height);
  bool endRendering();

private:
  ffmpeg() = default;

  // Disable copy and assignment
  ffmpeg(const ffmpeg &) = delete;
  ffmpeg &operator=(const ffmpeg &) = delete;

  int videoFifo;
  pid_t childPid;
};

#endif // FFMPEG_H
