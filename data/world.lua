--world.lua
function setup()
    print("Running world.lua!")
end

function OnSimulate()
    print("today is ",  World.GetIntProperty("day"))
    
    local world = World.GetWorldStrong()
    print(world)
    local territory = world:GetTerritory(1)
    print(territory)
    print(territory:GetName())
end

print(pcall(setup))
