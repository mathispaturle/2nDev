#include <iostream>
#include <string>
#include <sstream> 
#include <streambuf>
#include <vector>

#include "../../GameProject/dep/inc/XML/rapidxml.hpp"
#include "../../GameProject/dep/inc/XML/rapidxml_utils.hpp"
#include "../../GameProject/dep/inc/XML/rapidxml_iterators.hpp"
#include "../../GameProject/dep/inc/XML/rapidxml_print.hpp"


struct Enemy {

	std::string name;
	int vitality;
	int damageAttack;
	int defense;
	float frequencyAttack;
	int experience;

};

int main() {

	std::vector<Enemy> enemies;
	//Creación de un documento para poder leer su contenido
	rapidxml::xml_document<> doc;
	std::ifstream file("../../GameProject/res/files/config.xml"); 
	std::stringstream buffer;
	
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str()); doc.parse<0>(&content[0]);

	//Ejemplo: Imprimiendo la información de la raíz del documento
	std::cout << "Nombre de la raiz: " << doc.first_node()->name() << "\n\n"<< std::endl; 
	//std::cout << "Value: " << doc.first_node()->value() << std::endl;

	//Ejemplo: Imprimiendo para todos los eldleiuementos "book" del documento su valor (text content) (no se están considerando a los atributos)
	rapidxml::xml_node<> *pRoot = doc.first_node();

	Enemy e;

	for (rapidxml::xml_node<> *pNode = pRoot->first_node("enemy"); pNode; pNode = pNode->next_sibling()) {
		e.name = pNode->first_attribute("name")->value();
		e.vitality = std::stoi(pNode->first_attribute("vitality")->value());
		e.damageAttack = std::stoi(pNode->first_attribute("damageAttack")->value());
		e.defense = std::stoi(pNode->first_attribute("defense")->value());
		e.frequencyAttack = std::stof(pNode->first_attribute("frequencyAttack")->value());
		e.experience = std::stoi(pNode->first_attribute("experience")->value());

		enemies.push_back(e);
	}

	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {

		std::cout << "- Name: " << it->name << std::endl;
		std::cout << "- Vitality: " << it->vitality << std::endl;
		std::cout << "- Damage Attack: " << it->damageAttack << std::endl;
		std::cout << "- Defense: " << it->defense << std::endl;
		std::cout << "- Frequency Attack: " << it->frequencyAttack << std::endl;
		std::cout << "- Experience: " << it->experience << std::endl;
		std::cout <<"=============================================\n"<< std::endl;
	}

	system("pause");
	return 0;
}
