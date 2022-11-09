#include "testy.hh"

Testy::Testy()
{
    cout<<endl;
    cout<<"Testy"<<endl;
    Lib.CreateCmd("Move");
    Lib.CreateCmd("Rotate");
    Lib.CreateCmd("Pause");
    Lib.CreateCmd("Set");
    cout<<endl;

}

Testy::~Testy()
{
}

void Testy::Czytwanie_wartości_wtyczek()
{
  wskazik=Lib["Move"]->get_Cmd();
  wskazik1=Lib["Rotate"]->get_Cmd();
  wskazik2=Lib["Pause"]->get_Cmd();
  wskazik3=Lib["Set"]->get_Cmd();
}

void Testy::Wskazniki_i_wartosci()
{
  std::cout<<Lib["Move"]->getCmdName() <<"\n";
  wskazik->PrintSyntax();
  wskazik->PrintCmd();
  cout<<endl;

  std::cout<<Lib["Rotate"]->getCmdName()<<"\n";
  wskazik1->PrintSyntax();
  wskazik1->PrintCmd();
  cout<<endl;

  std::cout<<Lib["Pause"]->getCmdName()<<"\n";
  wskazik2->PrintSyntax();
  wskazik2->PrintCmd();
  cout<<endl;

  std::cout<<Lib["Set"]->getCmdName()<<"\n";
  wskazik3->PrintSyntax();
  wskazik3->PrintCmd();
  cout<<endl;
  cout<<endl;
}

void Testy::Czytaj_pierwsze_zpliku(istringstream &file)
{
    // string Name;
    // &file >> Name;
    // Interp4Command *tmp = Lib[Name]->get_Cmd();
    // tmp->ReadParams(&file);
    // tmp->PrintSyntax();
    // tmp->PrintCmd();
    // delete tmp;
}