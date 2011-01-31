/* forward-declare libusb types so we don't need to include the
 * whole header file */

#include <stdint.h>

typedef struct libusb_transfer libusb_transfer;
typedef struct libusb_context libusb_context;
typedef struct libusb_device_handle libusb_device_handle;

class MantaUSB
{
   public:
      MantaUSB(void);
      virtual ~MantaUSB(void);
      bool IsConnected(void);
      void Connect(int serialNumber = 0);
      void HandleEvents(void);
      bool IsTransmitting(void);

   protected:
      void WriteFrame(uint8_t *frame);
      virtual void FrameReceived(int8_t *frame) = 0;
      static const int OutPacketLen = 16;
      static const int InPacketLen = 64;

   private:
      static const int Interface = 0;
      static const int EndpointIn = 0x81; /* endpoint 0x81 address for IN */
      static const int EndpointOut = 0x02; /* endpoint 1 address for OUT */
      static const int Timeout = 5000; /* timeout in ms */
      static const int VendorID = 0x2424;
      static const int ProductID = 0x2424;

      void BeginReadTransfer(libusb_transfer *transfer);
      void BeginQueuedTransfer(libusb_transfer *transfer);

      int SerialNumber;
      static int DeviceCount;
      static libusb_context *LibusbContext;
      libusb_device_handle *DeviceHandle;
      volatile bool OutTransferInProgress;
      volatile bool OutTransferQueued;
      bool TransferError;
      uint8_t QueuedOutFrame[OutPacketLen];
      uint8_t ReceivedFrame[InPacketLen];
      
      friend void MantaOutTransferCompleteHandler(struct libusb_transfer *transfer);
      friend void MantaInTransferCompleteHandler(struct libusb_transfer *transfer);
};
