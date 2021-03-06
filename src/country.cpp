#include "country.h"
#include <algorithm>
#include <cassert>
#include <sstream>
#include "stockpile.h"
#include "territory.h"
#include "world.h"

Country::Country()
    : name_("invalid")
    , id_(0)
    , dissent_(0.0f)
{
    stockpile_ = std::make_shared<Stockpile>();
}

Country::Country(Id id, const std::string& name)
    : name_(name)
    , id_(id)
    , dissent_(0.0f)
{
    stockpile_ = std::make_shared<Stockpile>();
}

const std::string& Country::GetName() const
{
    return name_;
}

Stockpile* Country::GetStockpile()
{
    return stockpile_.get();
}

void Country::AddFactory()
{
    Factory f;
    f.SetStockpile(stockpile_);
    factories_.push_back(f);
}

void Country::RemoveFactory()
{
    if(!factories_.empty())
    {
        factories_.resize(factories_.size() - 1);
    }
}
uint32_t Country::GetFactoryCount() const
{
    return factories_.size();
}

Factory* Country::GetFactory(uint32_t idx)
{
    assert(idx < factories_.size());
    return &factories_[idx];
}

#if 0
const Factory* Country::GetFactory(uint32_t idx) const
{
    assert(idx < factories_.size());
    return &factories_[idx];
}
#endif

void Country::AddTerritory(uint32_t territory_id)
{
    territories_.insert(territory_id);
    
    auto world = World::GetWorldStrong();
    auto territory = world->GetTerritory(territory_id);
    for(auto itr = territory->ResourcesBegin(); itr!=territory->ResourcesEnd(); ++itr)
    {
        if(!territory->GetResourceIsProduced(itr->first))
        {
            stockpile_->AddResource(itr->first, territory->GetResource(itr->first));
        }
    }
}

void Country::RemoveTerritory(uint32_t territory_id)
{
    auto world = World::GetWorldStrong();
    auto territory = world->GetTerritory(territory_id);
    for(auto itr = territory->ResourcesBegin(); itr!=territory->ResourcesEnd(); ++itr)
    {
        if(!territory->GetResourceIsProduced(itr->first))
        {
            stockpile_->GetResource(itr->first, territory->GetResource(itr->first));
        }
    }

    territories_.erase(territory_id);
}

const std::set<uint32_t>& Country::GetTerritories() const
{
    return territories_;
}

RecipePtr Country::FindRecipeForResource(ResourceId id)
{
#define DEBUG_FIND_RECIPE 1
#if DEBUG && DEBUG_FIND_RECIPE
#define LOG(msg, ...)                                           \
    printf("%c[1;33m[Country::FindRecipeForResource] : ", 27);  \
    printf(msg, __VA_ARGS__);                                   \
    printf("%c[0m\n", 27);

#else
#define LOG(msg, ...)
#endif
    auto world = World::GetWorldStrong();

    LOG("Asked to produce %s", Resource::GetResourceShortName(id).c_str());
    // We want to produce some good and we have X factories
    auto target_recipes = world->GetRecipesForResource(id);   
    RecipePtr target_recipe;

    std::vector< ResourceCount<uint64_t>> shortfalls; 
    if(target_recipes.size() == 0)
    {
        printf("We have been asked to produce '%s' but there is not a way to produce that.\n",
               Resource::GetResourceShortName(id).c_str());
        return target_recipe;
    }

    // find a recipe with the output of what we are trying to build.
    RecipePtr candidate_recipe;
    uint32_t output_amount = 0;
    for(uint32_t ii=0; ii<target_recipes.size(); ++ii)
    {
        if(factories_[0].CanProduceRecipe(target_recipes[ii]))
        {
            LOG("Found a recipe '%s' to produce %s.", target_recipes[ii]->GetName().c_str(), Resource::GetResourceShortName(id).c_str());
            uint64_t recipe_output = target_recipes[ii]->ComputeOutputQty(id);
            if(output_amount < recipe_output)
            {
                output_amount = recipe_output;
                candidate_recipe = target_recipes[ii];
            }
        }
        else 
        {
            LOG("Recipe '%s' to produce %s has a shortfall.", target_recipes[ii]->GetName().c_str(), Resource::GetResourceShortName(id).c_str());
            shortfalls.push_back(factories_[0].ComputeResourceShortfall(target_recipes[ii]));
        }
    }
    
    if(candidate_recipe)
    {
        return candidate_recipe;
    }
    
    auto lessfunc = [id] (const ResourceCount<uint64_t>& l, const ResourceCount<uint64_t>& r) -> bool{
        if(r[id] > 0) return true;
        else return (l.ComputeTotal() < r.ComputeTotal());
    };
    
    std::sort(shortfalls.begin(), shortfalls.end(), lessfunc); 
    
    // we were not able to find a recipe to produce the item directly, so find the
    // recipe with the fewest missing components and try to produce those instead
    if(shortfalls.size() > 0 && shortfalls[0][id] == 0)
    {
        // now with the least shortfall set, return a recipe to produce
        target_recipe = FindRecipeForResource(shortfalls[0].ComputeLargestType());
    }
    return target_recipe;
#undef LOG
}

void Country::GatherResources()
{
    auto world = World::GetWorldStrong();

    // get resources from our territories
    for(uint32_t territory_id : territories_)
    {
        auto territory = world->GetTerritory(territory_id);
        for(auto itr=territory->ResourcesBegin(); itr!=territory->ResourcesEnd(); ++itr)
        {
            if(territory->GetResourceIsProduced(itr->first))
            {
                //printf("Stockpiling resource: %s\n", Resource::GetResourceShortName(itr->first).c_str());
                stockpile_->AddResource(itr->first, territory->GetResource(itr->first));
            }
        }
    }
    
    // get what the factories made
    for(auto &factory: factories_)
    {
        factory.DeliverResources();
    }
    
    static const ResourceId energy_id     = Resource::GetResourceByShortName("energy");
    static const ResourceId lubricants_id = Resource::GetResourceByShortName("lubricants");
    static const ResourceId steel_id      = Resource::GetResourceByShortName("steel");
    static const ResourceId manpower_id   = Resource::GetResourceByShortName("manpower");
    static const ResourceId foodstuffs_id = Resource::GetResourceByShortName("foodstuffs");
    static const ResourceId machines_id   = Resource::GetResourceByShortName("machines");
    
    //TODO: plan what the factories should produce and set up for that
    factories_[0].SetRecipe(FindRecipeForResource(energy_id));
    factories_[1].SetRecipe(FindRecipeForResource(lubricants_id));
    factories_[2].SetRecipe(FindRecipeForResource(steel_id));
    //factories_[2].SetRecipe(FindRecipeForResource(resource_machines));
    //factories_[3].SetRecipe(FindRecipeForResource(resource_machines));
    for(uint32_t ii=2; ii<factories_.size(); ++ii)
    {
        if(stockpile_->GetResourceQuantity(manpower_id) * 3 > stockpile_->GetResourceQuantity(foodstuffs_id))
        {
            factories_[ii].SetRecipe(FindRecipeForResource(foodstuffs_id));
        }
        else
        {
            factories_[ii].SetRecipe(FindRecipeForResource(machines_id));
        }
    }

#define DEBUG_FACTORY 0
#if DEBUG
    printf("[Country: %s]\n", name_.c_str());
    stockpile_->Debug();
#if DEBUG_FACTORY
    for(auto &factory: factories_)
    {
        factory.Debug();
    }
#endif
#endif
}

void Country::ProduceResources()
{
    // do stuff here
    for(auto &factory: factories_)
    {
        factory.GatherResources();
    }

    // do stuff here
    for(auto &factory: factories_)
    {
        factory.Produce(1.0f - dissent_);
    }
    
}

void Country::SimulateDomestic()
{
    static const ResourceId manpower_id   = Resource::GetResourceByShortName("manpower");
    static const ResourceId foodstuffs_id = Resource::GetResourceByShortName("foodstuffs");
    // Each manpower that is in the pool will need 1 foodstuff per day to survive
    // when a foodstuf deficit exists, the population may decrease and dissent may increase
    uint32_t total_manpower = stockpile_->GetResourceQuantity(manpower_id);
    uint32_t total_foodstuffs = stockpile_->GetResourceQuantity(foodstuffs_id);
    if(total_foodstuffs < total_manpower)
    {
        dissent_ += 0.01f;
        
        if(total_foodstuffs < 0.9f * total_manpower)
        {
            dissent_ += 0.015f;
        }
        
        if(total_foodstuffs < 0.8f * total_manpower)
        {
            stockpile_->GetResource(manpower_id, 0.01f * total_manpower);
            dissent_ += 0.055f;
        }
    }
    
    dissent_ = std::min(dissent_, 1.0f);
#if DEBUG
    printf("[Country::SimulateDomestic Dissent: %f]\n", dissent_);
#endif    
    stockpile_->GetResource(foodstuffs_id, std::min(total_manpower, total_foodstuffs));
}

bool Country::ReadInstance(Node* node)
{
    assert(node);
    
    if(node)
    {
        name_ = ExtractStringAttribute(node, "name");
        id_ = ExtractIntegerAttribute(node, "id");
        dissent_ = ExtractRealAttribute(node, "dissent");
        
        auto stockpile = FindChildNode(node, "stockpile");
        if(stockpile)
        {
            stockpile_->ReadInstance(stockpile);
        }
        
        uint64_t factories = ExtractIntegerAttribute(node, "factories");
        factories_.resize(factories);
        for(auto& factory:factories_)
        {
            factory.SetStockpile(stockpile_);
        }

        Node* territories = FindChildNode(node, "territories");
        std::stringstream ss;
        ss << ExtractStringAttribute(territories, "controlled");
        uint64_t territory = 0;
        while(ss>>territory)
        {
            //printf("Country controls %lu\n",territory);
            territories_.insert(territory);
        }
        
        return true;
    }
    return false;
}

bool Country::WriteInstance(Node* node)
{
    assert(node);
    
    if(node)
    {
        node = CreateChildNode(node, "country");
        AppendStringAttribute(node, "name", name_);
        AppendIntegerAttribute(node, "id", id_);
        AppendRealAttribute(node, "dissent", dissent_);
        AppendIntegerAttribute(node, "factories", factories_.size());
        stockpile_->WriteInstance(node);
        
        Node* territories = CreateChildNode(node, "territories");
        std::stringstream ss;
        for(auto territory : territories_)
        {
            ss<<" "<<territory;
        }

        AppendStringAttribute(territories, "controlled", ss.str().c_str());
    
        return true;
    }
    
    return false;
}