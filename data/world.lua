--world.lua
function setup()
    print("Running world.lua!")
end

function OnSimulateImp()
    print("today is " .. World.GetIntProperty("day"))
    
    local world = World.GetWorldStrong()

    local country = world:GetCountry(0)
    
    print(country:GetName() .. " has " .. country:GetFactoryCount() .. " factories.")
    country:GetStockpile():Debug()
    
    local territory = world:GetTerritory(1)
    print(territory)
    print(territory:GetName())
end

function OnSimulate()
    print(pcall(OnSimulateImp))
end

print(pcall(setup))
