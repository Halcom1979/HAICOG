#ifndef SYSLOCATIONSBODY_H
#define SYSLOCATIONSBODY_H

#include "System/GenericEquipmentSlots.h"

enum EquipmentSlotsBody {
  Head      = (1 << 0),
  Body      = (1 << 1),
  LeftLeg   = (1 << 2),
  RightLeg  = (1 << 3),
  LeftArm   = (1 << 4),
  RightArm  = (1 << 5),
  LeftHand  = (1 << 6),
  RightHand = (1 << 7),
  Shoes     = (1 << 8),
  Hands     = LeftHand | RightHand,
  Arms      = LeftArm | RightArm,
  Legs      = LeftLeg | RightLeg,
  BodyAll   = Head | Body | Legs | Arms | Hands | Shoes
};

class SysEquipmentSlotsBody :
    public GenericEquipmentSlots<EquipmentSlotsBody,9>
{
  public:
    SysEquipmentSlotsBody()
    : GenericEquipmentSlots("SystemBody")
    {}
};

#endif // SYSLOCATIONSBODY_H
