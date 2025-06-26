#pragma once
#include <rs485_asukiaaa.h>

namespace OrientalCommon_asukiaaa {
namespace BLx {

class Base {
 public:
  virtual void begin(unsigned long baudrate,
                     unsigned long config = SERIAL_8E1) = 0;
  virtual void beginWithoutModbus() = 0;
  virtual uint8_t writeLock() = 0;
  virtual uint8_t writeStop() = 0;
  virtual uint8_t writeSpeed32t(int32_t speed) = 0;

  virtual uint8_t readAlarmU32t(uint32_t *alarm) = 0;
  virtual uint8_t readLoadTorquePercent(float *torquePercent) = 0;
  virtual uint8_t readFeedbackSpeed32t(int32_t *speed) = 0;
  virtual uint8_t writeSetupConfigIfNeeded() = 0;

  virtual rs485_asukiaaa::ModbusRtu::Central *getModbus() = 0;
  virtual uint32_t getRpmMin() = 0;
  virtual uint32_t getRpmMax() = 0;
};

}  // namespace BLx
}  // namespace OrientalCommon_asukiaaa
