#pragma once
class Constants
{
public:
	Constants(void);
	~Constants(void);

	//TODO: Use Plan Object! //////////////////////////////////
	double getMainWindowWidth(void){ return 1920/2; }; //Largura
	double getMainWindowHeight(void){ return 1080/2; }; //Altura
	double getPersonWindowWidth(void){ return 1920/4; }; //Largura
	double getPersonWindowHeight(void){ return 1080/4; }; //Altura
	double getCampusWindowWidth(void){ return 1920/4; }; //Largura
	double getCampusWindowHeight(void){ return 1080/4; }; //Altura
	///////////////////////////////////////////////////////////

	//TODO: USE Point3D! //////////////////////////////////////
	//MAIN CAMERA
	double getMainCameraPositionX(void){ return 00.00; }; //Vista de frente
	double getMainCameraPositionY(void){ return 00.00; };
	double getMainCameraPositionZ(void){ return 10.00; };
	double getMainCameraFocalPointX(void){ return 00.00; };
	double getMainCameraFocalPointY(void){ return 00.00; };
	double getMainCameraFocalPointZ(void){ return 00.00; };
	//Campus CAMERA
	double getCampusCameraPositionX(void){ return 10.00; }; //Vista de Cima
	double getCampusCameraPositionY(void){ return 10.00; };
	double getCampusCameraPositionZ(void){ return 10.00; };
	double getCampusCameraFocalPointX(void){ return 00.00; };
	double getCampusCameraFocalPointY(void){ return 00.00; };
	double getCampusCameraFocalPointZ(void){ return 00.00; };
	//Person CAMERA
	double getPersonCameraPositionX(void){ return 10.00; }; //Vista de Lado
	double getPersonCameraPositionY(void){ return 00.00; };
	double getPersonCameraPositionZ(void){ return 00.00; };
	double getPersonCameraFocalPointX(void){ return 00.00; };
	double getPersonCameraFocalPointY(void){ return 00.00; };
	double getPersonCameraFocalPointZ(void){ return 00.00; };
	///////////////////////////////////////////////////////////

	



	//TODO ... ERROR Fuck C++!
	//Plan& getMainWindowSize(void);
	
	
};

