/// VTK
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkAxesActor.h"
#include "vtkOBJReader.h"
#include "vtkPlaneSource.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkJPEGReader.h"
#include "vtkLight.h"
#include "vtkCommand.h"

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

/*Callback for the interaction*/

class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New() 
    { return new vtkMyCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void* calldata)
    {
      vtkRenderer *renderer = (vtkRenderer *) (caller);
      //printf("\nCoords= %f %f %f",renderer->GetActiveCamera()->GetPosition()[0], renderer->GetActiveCamera()->GetPosition()[1], renderer->GetActiveCamera()->GetPosition()[2]);
	  cout << "~";
    }
};

/*Callback for the interaction*/

void drawBuildings(vtkRenderer *renMain, vtkRenderer *renPerson, vtkRenderer *renCampus){
	
	ifstream infile("map.txt");
	string line,c1,c2,c3,c4,c5,c6,c7,c8,c9;
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
			if(!(iss >> c2 >> c3 >> c4 >> c5 >> c6 >> c7 >> c8 >> c9)){ 
				cout << "Error READING map.txt! END!\nPress any key..." <<endl;
				getchar();
				break;
			};
			cout << c1 << "\tPosX: " << c2 << "\tPosY: " << c3 << "\tPosZ: " << c4 << "\tAngX: " << c5 << "\tAngY: " << c6 << "\tAngZ: " << c7 << "\tFileMap: " << c8 << "\tFileTexture: " << c9 << endl;

			//vtkConeSource *cone = vtkConeSource::New();
			//vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
			//coneMapper->SetInput( cone->GetOutput() );
			//vtkActor *coneActor = vtkActor::New();
			//coneActor->SetMapper( coneMapper );
			//coneActor->SetPosition(std::stod(c2),std::stod(c3),std::stod(c4));
			//renMain->AddActor( coneActor );
			//renPerson->AddActor( coneActor );
			//renCampus->AddActor( coneActor );
			
			vtkOBJReader *objReader = vtkOBJReader::New();
			objReader->SetFileName(c8.c_str());
			objReader->Update();
			vtkPolyDataMapper *objMapper = vtkPolyDataMapper::New();
			objMapper->SetInput ( objReader->GetOutput() );
			vtkActor *objActor = vtkActor::New();
			objActor->SetMapper(objMapper);
			objActor->SetPosition(stod(c2),stod(c3),stod(c4));
			objActor->SetOrientation(stod(c5),stod(c6),stod(c7));
			if(c9.substr(0,1).compare("?")!=0){
				vtkJPEGReader *JPGReader = vtkJPEGReader::New();
				JPGReader->SetFileName(c9.c_str());
				vtkTexture *aText = vtkTexture::New();
				aText->SetInput( (vtkDataObject*) JPGReader->GetOutput() );
				objActor->SetTexture(aText);
			}
			renMain->AddActor( objActor );
			renPerson->AddActor( objActor );
			renCampus->AddActor( objActor );


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
	renMain->SetBackground(0.4,0.4,0.4);
	renPerson->SetBackground(0.4,0.4,0.4);
	renCampus->SetBackground(0.4,0.4,0.4);

	//Load MAP
	drawBuildings(renMain, renPerson, renCampus);

	//Load Person (a men)
	vtkOBJReader *objReader = vtkOBJReader::New();
	objReader->SetFileName("objects/Man.obj");
	objReader->Update();
	vtkPolyDataMapper *objMapper = vtkPolyDataMapper::New();
	objMapper->SetInput ( objReader->GetOutput() );
	vtkActor *objActor = vtkActor::New();
	objActor->SetMapper(objMapper);
	objActor->SetPosition(constants->getPersonCameraPositionX(),constants->getPersonCameraPositionY(),constants->getPersonCameraPositionZ());
	//objActor->SetOrientation(constants->getPersonCameraFocalPointX(),constants->getPersonCameraFocalPointY(),constants->getPersonCameraFocalPointZ());
	objActor->SetOrientation(0,-90,0);
	renMain->AddActor( objActor );
	renPerson->AddActor( objActor );
	renCampus->AddActor( objActor );

	//Draw Groud
	vtkPlaneSource *plane = vtkPlaneSource::New();
	//plane->SetPoint1(0.0,0.0,0.0);
	//plane->SetPoint2(2.0,0.0,2.0);
	plane->SetNormal(0.0,1.0,0.0);
	vtkPolyDataMapper *planeMapper = vtkPolyDataMapper::New();
	planeMapper->SetInput(plane->GetOutput());
	vtkActor *planeActor = vtkActor::New();
	planeActor->SetMapper( planeMapper );
	
	vtkJPEGReader *JPGReader = vtkJPEGReader::New();
	JPGReader->SetFileName("textures/ground.jpg");
	
	vtkTexture *aText = vtkTexture::New();
	aText->SetInput( (vtkDataObject*) JPGReader->GetOutput() );
	planeActor->SetTexture(aText);

	renMain->AddActor(planeActor);
	renPerson->AddActor(planeActor);
	renCampus->AddActor(planeActor);
	

	
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
	renMain->GetActiveCamera()->SetViewUp(0,1,0);
	renCampus->GetActiveCamera()->SetPosition(constants->getCampusCameraPositionX(),constants->getCampusCameraPositionY(),constants->getCampusCameraPositionZ());
	renCampus->GetActiveCamera()->SetFocalPoint(constants->getCampusCameraFocalPointX(),constants->getCampusCameraFocalPointY(),constants->getCampusCameraFocalPointZ());
	renCampus->GetActiveCamera()->SetViewUp(0,1,0);
	renPerson->GetActiveCamera()->SetPosition(constants->getPersonCameraPositionX(),constants->getPersonCameraPositionY()+constants->getManHeight(),constants->getPersonCameraPositionZ());
	renPerson->GetActiveCamera()->SetFocalPoint(constants->getPersonCameraFocalPointX(),constants->getPersonCameraFocalPointY()+constants->getManHeight(),constants->getPersonCameraFocalPointZ());
	renPerson->GetActiveCamera()->SetViewUp(0,1,0);

	//CREATE LIGHTs
	vtkLight *lightMain = vtkLight::New();
	vtkLight *lightPerson = vtkLight::New();
	vtkLight *lightCampus = vtkLight::New();
	vtkLight *light4ALL = vtkLight::New();
	lightMain->SetColor(1,1,1);
	lightPerson->SetColor(1,1,1);
	lightCampus->SetColor(1,1,1);
	light4ALL->SetColor(1,1,1);
	lightMain->SetFocalPoint(renMain->GetActiveCamera()->GetFocalPoint());
	lightPerson->SetFocalPoint(renPerson->GetActiveCamera()->GetFocalPoint());
	lightCampus->SetFocalPoint(renCampus->GetActiveCamera()->GetFocalPoint());
	lightMain->SetPosition(renMain->GetActiveCamera()->GetPosition());
	lightPerson->SetPosition(renPerson->GetActiveCamera()->GetPosition());
	lightCampus->SetPosition(renCampus->GetActiveCamera()->GetPosition());
	light4ALL->SetPosition(5,10,5);
	light4ALL->SetFocalPoint(5,0,5);
	renMain->AddLight(lightMain);
	renPerson->AddLight(lightPerson);
	renCampus->AddLight(lightCampus);
	renMain->AddLight(light4ALL);
	renPerson->AddLight(light4ALL);
	renCampus->AddLight(light4ALL);


	//Create Interactor for with one window
	vtkRenderWindowInteractor *irenMain = vtkRenderWindowInteractor::New();
	irenMain->SetRenderWindow(renWinMain);
	irenMain->Initialize();
	
	vtkRenderWindowInteractor *irenPerson = vtkRenderWindowInteractor::New();
	irenPerson->SetRenderWindow(renWinPerson);
	irenPerson->Initialize();
	
	vtkRenderWindowInteractor *irenCampus = vtkRenderWindowInteractor::New();
	irenCampus->SetRenderWindow(renWinCampus);
	irenCampus->Initialize();
	
	//Create Observer
	vtkMyCallback *mo1 = vtkMyCallback::New();
	renMain->AddObserver(vtkCommand::EndEvent,mo1);
	//renMain->AddObserver(vtkCommand::AnyEvent,mo1);
	mo1->Delete();

	irenMain->Start();
	irenPerson->Start();
	irenCampus->Start();

	//DELETE...
	
	planeActor->Delete();
	plane->Delete();
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

