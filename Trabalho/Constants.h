#pragma once
class Constants
{
public:
	int getMainWindowWidth(void){ return 1920/4; }; //Largura
	int getMainWindowHeight(void){ return 1080/4; }; //Altura
	int getPersonWindowWidth(void){ return 1920/8; }; //Largura
	int getPersonWindowHeight(void){ return 1080/8; }; //Altura
	int getCampusWindowWidth(void){ return 1920/8; }; //Largura
	int getCampusWindowHeight(void){ return 1080/8; }; //Altura
	Constants(void);
	~Constants(void);
	
};

