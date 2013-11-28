/// VTK
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkAxesActor.h"

#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"

/// MyObjects
#include "Constants.h"
#include "Point3D.h"
#include "Plan.h"


/// C++ required
#include <iostream>	//For COUT, ...
#include <fstream>	//For Files
#include <sstream>	//
#include <string>	//
#include <list>		//

using namespace std;

void drawBuildings(vtkRenderer *renMain, vtkRenderer *renPerson, vtkRenderer *renCampus){
	
	ifstream infile("map.txt");
	string line,c1,c2,c3,c4,c5,c6,c7,c8;
	while (std::getline(infile, line)){
		istringstream iss(line);
		if(!(iss >> c1)){ 
			cout << "Error READING map.txt! END!\nPress any key..." <<endl;
			getchar();
			break;
		};
		if (c1.substr(0,1).compare("#")==0){
			//cout << "comentario" << endl;
		}else{
			if(!(iss >> c2 >> c3 >> c4 >> c5 >> c6 >> c7 >> c8)){ 
				cout << "Error READING map.txt! END!\nPress any key..." <<endl;
				getchar();
				break;
			};
			cout << c1 << "\tPosX: " << c2 << "\tPosY: " << c3 << "\tPosZ: " << c4 << "\tAngX: " << c5 << "\tAngY: " << c6 << "\tAngZ: " << c7 << "\tFileMap: " << c8 << endl;

			vtkConeSource *cone = vtkConeSource::New();
			vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
			coneMapper->SetInput( cone->GetOutput() );
			vtkActor *coneActor = vtkActor::New();
			coneActor->SetMapper( coneMapper );
			coneActor->SetPosition(std::stod(c2),std::stod(c3),std::stod(c4));
			renMain->AddActor( coneActor );
			renPerson->AddActor( coneActor );
			renCampus->AddActor( coneActor );
			

			
			//ren1->Render();
			cout << "-" << std::stod(c2) << "-" << endl;

		}
	}
}

int main( )
{
	Constants *constants=new Constants();
	constants->getMainWindowWidth();

	//testing
	//vtkConeSource *cone = vtkConeSource::New();
	//vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
	//coneMapper->SetInput( cone->GetOutput() );
	//vtkActor *coneActor = vtkActor::New();
	//coneActor->SetMapper( coneMapper );
	//vtkRenderer *ren1= vtkRenderer::New();
	//ren1->AddActor( coneActor );
	//vtkRenderWindow *renWin = vtkRenderWindow::New();
	//renWin->AddRenderer( ren1 );
	/////////////////////////////////


	//Create a render
	vtkRenderer *renMain= vtkRenderer::New();
	vtkRenderer *renPerson= vtkRenderer::New();
	vtkRenderer *renCampus= vtkRenderer::New();

	//Load MAP
	drawBuildings(renMain, renPerson, renCampus);
	
	//Draw AXeS
	vtkAxesActor *actorAxesMain = vtkAxesActor::New();
	renMain->AddActor(actorAxesMain);
	renPerson->AddActor(actorAxesMain);
	renCampus->AddActor(actorAxesMain);

	//Create 3 Render Window
	vtkRenderWindow *renWinMain = vtkRenderWindow::New();
	vtkRenderWindow *renWinPerson = vtkRenderWindow::New();
	vtkRenderWindow *renWinCampus = vtkRenderWindow::New();

	//Resize 3 Render Windows
	renWinMain->SetSize(constants->getMainWindowWidth(),constants->getMainWindowHeight());
	renWinPerson->SetSize(constants->getPersonWindowWidth(),constants->getPersonWindowHeight());
	renWinCampus->SetSize(constants->getCampusWindowWidth(),constants->getCampusWindowHeight());
	
	//Change Window Name
	renWinMain->Render();
	renWinMain->SetWindowName("Main Window");
	renWinPerson->Render();
	renWinPerson->SetWindowName("Person View");
	renWinCampus->Render();
	renWinCampus->SetWindowName("Campus Camera");

	renWinMain->AddRenderer(renMain);
	renWinPerson->AddRenderer(renPerson);
	renWinCampus->AddRenderer(renCampus);

	//set Cameras
	renMain->GetActiveCamera()->SetPosition(constants->getMainCameraPositionX(),constants->getMainCameraPositionY(),constants->getMainCameraPositionZ());
	renMain->GetActiveCamera()->SetFocalPoint(constants->getMainCameraFocalPointX(),constants->getMainCameraFocalPointY(),constants->getMainCameraFocalPointZ());
	renCampus->GetActiveCamera()->SetPosition(constants->getCampusCameraPositionX(),constants->getCampusCameraPositionY(),constants->getCampusCameraPositionZ());
	renCampus->GetActiveCamera()->SetFocalPoint(constants->getCampusCameraFocalPointX(),constants->getCampusCameraFocalPointY(),constants->getCampusCameraFocalPointZ());
	renPerson->GetActiveCamera()->SetPosition(constants->getPersonCameraPositionX(),constants->getPersonCameraPositionY(),constants->getPersonCameraPositionZ());
	renPerson->GetActiveCamera()->SetFocalPoint(constants->getPersonCameraFocalPointX(),constants->getPersonCameraFocalPointY(),constants->getPersonCameraFocalPointZ());

	//Create Interactor for with one
	vtkRenderWindowInteractor *irenMain = vtkRenderWindowInteractor::New();
	irenMain->SetRenderWindow(renWinMain);
	irenMain->Initialize();
	

	vtkRenderWindowInteractor *irenPerson = vtkRenderWindowInteractor::New();
	irenPerson->SetRenderWindow(renWinPerson);
	irenPerson->Initialize();
	

	vtkRenderWindowInteractor *irenCampus = vtkRenderWindowInteractor::New();
	irenCampus->SetRenderWindow(renWinCampus);
	irenCampus->Initialize();
	
	irenMain->Start();
	irenPerson->Start();
	irenCampus->Start();

	irenMain->Delete();
	irenPerson->Delete();
	irenCampus->Delete();
	renWinMain->Delete();
	renWinPerson->Delete();
	renWinCampus->Delete();
	constants->~Constants();
	cout << "END!\nPress Any key to exit!" <<endl;
	getchar();
	return 0;
}

