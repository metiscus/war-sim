#pragma once

#include <algorithm>
#include <cstdint>

class PolicySetting
{
private:
    float value_;

public:
    PolicySetting();
    
    float GetValue() const;
    void SetValue(const float& value);
    void ChangeValue(const float& value);
};

class Policy
{
    //!\brief war_economy controls the resource prioritization of weapons production
    PolicySetting war_economy;
    PolicySetting army_infantry_focus;
    PolicySetting army_artillery_focus;
    PolicySetting army_armor_focus;
    PolicySetting navy_escort_focus;
    PolicySetting navy_capital_focus;

private:
    
public:
    
    
    
};
