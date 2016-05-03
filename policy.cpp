#include "policy.h"

PolicySetting::PolicySetting() 
    : value_(0.0f) 
{ 
    ;
}

float PolicySetting::GetValue() const
{ 
    return value_; 
}

void PolicySetting::SetValue(const float& value) 
{ 
    value_ = std::max(0.f, std::min(1.f, value));
}

void PolicySetting::ChangeValue(const float& value)
{
    value_ = std::max(0.f, std::min(1.f, value_ + value));
}

///////////////////////////////////////////////////////////////////////////////