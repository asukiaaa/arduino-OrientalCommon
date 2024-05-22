#pragma once
#include <rs485_asukiaaa.h>

namespace OrientalCommon_asukiaaa {
namespace StepMotorDirectOperation {

namespace Registers {
const uint16_t directDataOperationDataNumber = 0x0058;
const uint16_t directDataOperationType = 0x005a;
// const uint16_t directDataOperationTrigger = 0x0222;
const uint16_t directDataOperationPosition = 0x005c;
const uint16_t directDataOperationSpeed = 0x005e;
const uint16_t directDataOperationChangeRate = 0x0060;
const uint16_t directDataOperationStopRate = 0x0062;
const uint16_t directDataOperationCurrent = 0x0064;
const uint16_t directDataOperationTrigger = 0x0066;
const uint16_t directDataOperationForwardingDestination = 0x0068;
}  // namespace Registers

namespace DirectDataOperationTrigger {
const int32_t All = 1;
const int32_t Disable = 0;
const int32_t OperatingCurrentUpdate = -1;
const int32_t StoppingDecelationUpdate = -2;
const int32_t ChangeRateUpdate = -3;
const int32_t OperatingSpeedUpdate = -4;
const int32_t PositionUpdate = -5;
const int32_t OperationTypeUpdate = -6;
const int32_t OperationDataNumberUpdate = -7;
}  // namespace DirectDataOperationTrigger

namespace DirectOperationType {
const uint16_t NoSetting = 0;
const uint16_t AbsolutePositioning = 1;
const uint16_t IncrementalPositioningByCommandPosition = 2;
const uint16_t IncrementalPositioningbyFeedbackPosition = 3;
const uint16_t ContinuousOperationByPosition = 7;
const uint16_t WrapAbsolutePositioning = 8;
const uint16_t WrapProximityPositioning = 9;
const uint16_t WrapAbsolutePositioningFw = 10;
const uint16_t WrapAbsolutePositioningRv = 11;
const uint16_t WrapAbsolutePushMotion = 12;
const uint16_t WrapProximityPushMotion = 13;
const uint16_t WrapPushMotionFw = 14;
const uint16_t WrapPushMotionRv = 15;
const uint16_t ContinuousOperationBySpeed = 16;
const uint16_t ContinuousOperationByPush = 17;
const uint16_t ContinuousOperationByTorque = 18;
const uint16_t AbsolutePushMotion = 20;
const uint16_t IncrementalPushMotionByCommandPosition = 21;
const uint16_t IncrementalPushMotionByFeedbackPosition = 22;
}  // namespace DirectOperationType

struct DirectOperation {
  uint32_t dataNumber = 0;
  uint32_t operationType =
      DirectOperationType::IncrementalPositioningByCommandPosition;
  int32_t position = 0;
  int32_t speed = 1000;
  uint32_t changeRate = 1000000;
  uint32_t stopRate = 1000000;
  uint32_t current = 1000;
};

class Core {
 public:
  uint8_t writeDirectOperatonStopRate(
      uint32_t stopRate, bool changeDirectOperationTrigger = true) {
    if (changeDirectOperationTrigger) {
      auto error = writeDirectOperationTrigger(
          DirectDataOperationTrigger::StoppingDecelationUpdate);
      if (error != 0) {
        return error;
      }
    }
    return getModbus()->writeRegisterBy32t(
        getAddress(), Registers::directDataOperationStopRate, stopRate);
  }

  uint8_t writeDirectOperatonChangeRate(
      uint32_t changeRate, bool changeDirectOperationTrigger = true) {
    if (changeDirectOperationTrigger) {
      auto error = writeDirectOperationTrigger(
          DirectDataOperationTrigger::ChangeRateUpdate);
      if (error != 0) {
        return error;
      }
    }
    return getModbus()->writeRegisterBy32t(
        getAddress(), Registers::directDataOperationChangeRate, changeRate);
  }

  // uint8_t writeDirectOperatonTypeContinuousOperationBySpeed(
  //     bool changeDirectOperationTrigger = true) {
  //   if (changeDirectOperationTrigger) {
  //     auto error = writeDirectOperationTrigger(
  //         DirectDataOperationTrigger::OperationTypeUpdate);
  //     if (error != 0) {
  //       return error;
  //     }
  //   }
  //   return getModbus()->writeRegisterBy32t(
  //       getAddress(), Registers::directDataOperationType,
  //       DirectOperationType::ContinuousOperationBySpeed);
  // }

  uint8_t writeDirectOperatonType(uint32_t operationType,
                                  bool changeDirectOperationTrigger = true) {
    if (changeDirectOperationTrigger) {
      auto error = writeDirectOperationTrigger(
          DirectDataOperationTrigger::OperationTypeUpdate);
      if (error != 0) {
        return error;
      }
    }
    return getModbus()->writeRegisterBy32t(
        getAddress(), Registers::directDataOperationType, operationType);
  }

  uint8_t writeDirectOperationSpeed(int32_t speed,
                                    bool changeDirectOperationTrigger = true) {
    if (changeDirectOperationTrigger) {
      auto error = writeDirectOperationTrigger(
          DirectDataOperationTrigger::OperatingSpeedUpdate);
      if (error != 0) {
        return error;
      }
    }
    return getModbus()->writeRegisterBy32t(
        getAddress(), Registers::directDataOperationSpeed, speed);
  }

  uint8_t writeDirectOperationTrigger(uint32_t trigger) {
    return getModbus()->writeRegisterBy32t(
        getAddress(), Registers::directDataOperationTrigger, trigger);
  }

  uint8_t writeDirectOperation(DirectOperation operation) {
    uint32_t data[] = {operation.dataNumber,
                       operation.operationType,
                       (uint32_t)operation.position,
                       (uint32_t)operation.speed,
                       operation.changeRate,
                       operation.stopRate,
                       operation.current,
                       DirectDataOperationTrigger::All};
    return getModbus()->writeRegistersBy32t(
        getAddress(), Registers::directDataOperationDataNumber, data,
        sizeof(data) / sizeof(data[0]));
  }

  // uint8_t test() {
  //   uint32_t data[] = {
  //       0,    DirectOperationType::IncrementalPositioningByCommandPosition,
  //       8500, 2000,
  //       1500, 1500,
  //       1000, 1};
  //   return modbus->writeRegistersBy32t(address,
  //                                      Registers::directDataOperationDataNumber,
  //                                      data, sizeof(data) / sizeof(data[0]));
  // }

  // uint8_t writeDirectOperatoinWithTriggerConfig(
  //     bool changeDirectOperationTrigger, uint32_t trigger,
  //     uint8_t (*fnWrite)()
  // ) {
  //   if (changeDirectOperationTrigger) {
  //     auto error = writeDirectOperationTrigger(trigger);
  //     if (error != 0) {
  //       return error;
  //     }
  //     return fnWrite();
  //   }
  // }

 private:
  virtual rs485_asukiaaa::ModbusRtu::Central *getModbus();
  virtual uint8_t getAddress();
};

}  // namespace StepMotorDirectOperation
}  // namespace OrientalCommon_asukiaaa
