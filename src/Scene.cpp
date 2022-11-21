#include "Scene.hh"


// bool Scene::FindMobileObject (std::string name, std::shared_ptr<MobileObj> & tempMobileObject)
// {
//     std::map<std::string, std::shared_ptr<MobileObj>>::iterator it;
    
//     it = mapMobileObjects.find(name);
    
//     if(it == mapMobileObjects.end())
//     {
//         std::cout << "Nie znaleziono obiektu: " << name << std::endl;
//         return false;
//     }

//     tempMobileObject = it->second;
    
//     return true;
// }

Scene::Scene(){
}

Scene::~Scene(){
}

void Scene::AddMobileObject(std::shared_ptr<MobileObj> handler)
{
    mapMobileObjects.insert(std::make_pair(handler->GetName(), handler));
}
