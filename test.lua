print("test.lua")

function foo()
    local country = Country.new(0, "australia")
    print(country:GetName())
    local territory = Territory.new()
    print(territory)
    territory:SetOwner(1)
    local owner = territory:GetOwner()
    print(owner)

    territory:ChangeResource(0, 10.0)
    print("Resource name")

    print("Z 1")
    local n = Resource.GetResourceShortName(1)
    print("Z 2")
    print(n)
    print("Z 3")
end

print("a")
print(pcall(foo))
print("b")
