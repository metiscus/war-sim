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
    
    if country:GetName() == "Australia" then
        print "Australia is producing armor plates"
        local fc = country:GetFactoryCount()
        local factory = country:GetFactory(fc-1)
        local plates = Resource.GetResourceByShortName("armor_plates")
        local recipe = world:GetFirstRecipeForResource(plates)
        --factory:SetRecipe(recipe)
    end
    
    
    local territory = world:GetTerritory(1)
    print(territory)
    print(territory:GetName())
end

function OnSimulate()
    print(pcall(OnSimulateImp))
end

print(pcall(setup))
