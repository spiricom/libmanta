#ifndef _MANTACLIENT_H
#define _MANTACLIENT_H

#include <stdint.h>

class MantaClient
{
   public:
      virtual ~MantaClient() {}
      /* declare callbacks to be implemented by subclasses */
      virtual void PadEvent(int row, int column, int id, int value) {}
      virtual void SliderEvent(int id, int value) {}
      virtual void ButtonEvent(int id, int value) {}
      virtual void PadVelocityEvent(int row, int column, int id, int velocity) {}
      virtual void ButtonVelocityEvent(int id, int velocity) {}
      virtual void FrameEvent(uint8_t *frame) {}
      virtual void DebugPrint(const char *fmt, ...) {}
};
#endif /* _MANTACLIENT_H */
