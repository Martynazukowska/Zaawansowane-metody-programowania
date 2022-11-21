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

std::shared_ptr<MobileObj> Scene::operator [] (std::string &Name){
  return mapMobileObjects[Name];
}

std::shared_ptr<MobileObj> Scene::operator [] (char *sName){
  return mapMobileObjects[sName];
}

std::shared_ptr<MobileObj> Scene::TakeMobileObj(const char *sObjName){
  return mapMobileObjects[sObjName];
}

std::shared_ptr<MobileObj> Scene::TakeMobileObj(const std::string &rObjName){
  return mapMobileObjects[rObjName];
}
