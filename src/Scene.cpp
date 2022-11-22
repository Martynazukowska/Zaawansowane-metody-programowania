#include "Scene.hh"

Scene::Scene(){
}

Scene::~Scene(){
}


void Scene::AddMobileObject(Configuration *pConfig)
{
  for(unsigned long int i = 0; i < pConfig->GetObjVector().size(); ++i) 
  {
    std::shared_ptr<MobileObj> tmp = std::make_shared<MobileObj>();
    tmp->SetPosition_m(pConfig->GetObjVector()[i].GetPosition_m());
    tmp->SetName(pConfig->GetObjVector()[i].GetName().c_str());
    tmp->SetAng_Yaw_deg(pConfig->GetObjVector()[i].GetAng_Yaw_deg());
    mapMobileObjects[tmp->GetName()] = tmp;
  }
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
