--world.lua
function setup()
    print("Running world.lua!")
end

function OnSimulate()
    print("today is ",  World.GetIntProperty("day"))
end

print(pcall(setup))
