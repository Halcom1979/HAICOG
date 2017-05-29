#include "SystemBase.h"

SystemBase::SystemBase(const std::string & name)
: mName(name)
{

}

const std::string &SystemBase::name() const
{
  return mName;
}
