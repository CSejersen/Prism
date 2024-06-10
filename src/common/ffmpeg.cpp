#include "ffmpeg.h"
#include "raylib.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using std::size_t;

ffmpeg *ffmpeg::startRendering(std::size_t width, std::size_t height,
                               std::size_t fps) {
  // TODO: implement audio rendering
  const char *prism_video_path = "./prism_video";

  if (mkfifo(prism_video_path, 0600) < 0) {
    if (errno != EEXIST) {
      TraceLog(LOG_ERROR, "ffmpeg: Could not create fifo file %s: %s",
               prism_video_path, strerror(errno));
      return nullptr;
    } else {
      TraceLog(LOG_WARNING, "ffmpeg: Fifo file %s already exists",
               prism_video_path);
    }
  }

  // create a child process that will later run the ffmpeg cli tool
  pid_t child = fork();
  if (child < 0) {
    TraceLog(LOG_ERROR, "ffmpeg: Could not fork a child: %s", strerror(errno));
  }

  if (child == 0) {

    /* // Redirect stdout and stderr to /dev/null */
    /* int devNull = open("/dev/null", O_WRONLY); */
    /* if (devNull == -1) { */
    /*   TraceLog(LOG_ERROR, "ffmpeg: Could not open /dev/null: %s", */
    /*            strerror(errno)); */
    /*   exit(1); */
    /* } */

    /* dup2(devNull, STDOUT_FILENO); */
    /* dup2(devNull, STDERR_FILENO); */
    /* close(devNull); */

    char resolution[64];
    snprintf(resolution, sizeof(resolution), "%zux%zu", width, height);
    char framerate[64];
    snprintf(framerate, sizeof(framerate), "%zu", fps);
    // replace child process image with ffmpeg
    int ret = execlp("ffmpeg", "ffmpeg", "-loglevel", "verbose", "-y",

                     "-f", "rawvideo", "-pix_fmt", "rgba", "-s", resolution,
                     "-r", framerate, "-i", prism_video_path,

                     "-c:v", "libx264", "-vb", "2500k", "-c:a", "aac", "-ab",
                     "200k", "-pix_fmt", "yuv420p", "output.mp4",

                     NULL);

    if (ret < 0) {
      TraceLog(LOG_ERROR,
               "FFMPEG CHILD: could not run ffmpeg as a child process: %s",
               strerror(errno));
      exit(1);
    }
  }

  int video_fifo = open(prism_video_path, O_WRONLY);
  if (video_fifo < 0) {
    TraceLog(LOG_ERROR, "ffmpeg: Could not open fifo file %s: %s",
             prism_video_path, strerror(errno));
  }

  // Return a unique pointer to the ffmpeg instance
  ffmpeg *ffmpeg_instance = new ffmpeg();
  ffmpeg_instance->childPid = child;
  ffmpeg_instance->videoFifo = video_fifo;
  return ffmpeg_instance;
}

bool ffmpeg::sendFrameFlipped(void *data, std::size_t width,
                              std::size_t height) {
  for (size_t y = height; y > 0; --y) {
    if (write(videoFifo, (uint32_t *)data + (y - 1) * width,
              sizeof(uint32_t) * width) < 0) {
      TraceLog(LOG_ERROR, "FFMPEG: failed to write into ffmpeg pipe: %s",
               strerror(errno));
      return false;
    }
  }
  return true;
}

bool ffmpeg::endRendering() {
  SetTraceLogLevel(LOG_INFO);
  if (close(videoFifo) < 0) {
    TraceLog(
        LOG_WARNING,
        "FFMPEG: could not close write end of the pipe on the parent's end: %s",
        strerror(errno));
  }

  for (;;) {
    int wstatus = 0;
    if (waitpid(childPid, &wstatus, 0) < 0) {
      TraceLog(LOG_ERROR,
               "FFMPEG: could not wait for ffmpeg child process to finish: %s",
               strerror(errno));
      return false;
    }

    if (WIFEXITED(wstatus)) {
      int exit_status = WEXITSTATUS(wstatus);
      if (exit_status != 0) {
        TraceLog(LOG_ERROR, "FFMPEG: ffmpeg exited with code %d", exit_status);
        return false;
      }

      return true;
    }

    if (WIFSIGNALED(wstatus)) {
      TraceLog(LOG_ERROR, "FFMPEG: ffmpeg got terminated by %s",
               strsignal(WTERMSIG(wstatus)));
      return false;
    }
  }
}
