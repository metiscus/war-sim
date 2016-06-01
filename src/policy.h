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

enum PolicyType
{
    policy_first = 0,
    policy_war_economy = policy_first,
    
    
    
    policy_count
};

class Policy
{
    //!\brief war_economy controls the resource prioritization of weapons production
    //std::map<PolicyType, PolicySetting> policies_;

private:
    
public:
    
    
    
};
