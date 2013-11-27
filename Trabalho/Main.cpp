/// VTK
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

#include "vtkConeSource.h"

/// MyObjects
#include "Constants.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"

/// C++ required
#include <iostream>
using namespace std;

int main( )
{
	Constants *constants=new Constants();
	constants->getMainWindowWidth();

	//testing
	vtkConeSource *cone = vtkConeSource::New();
	vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInput( cone->GetOutput() );
	vtkActor *coneActor = vtkActor::New();
	coneActor->SetMapper( coneMapper );
	vtkRenderer *ren1= vtkRenderer::New();
	ren1->AddActor( coneActor );
	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer( ren1 );
	/////////////////////////////////
	
	//Create 3 Render Window
	vtkRenderWindow *renWinMain = vtkRenderWindow::New();
	vtkRenderWindow *renWinPerson = vtkRenderWindow::New();
	vtkRenderWindow *renWinCampus = vtkRenderWindow::New();

	//Resize 3 Render Windows
	renWinMain->SetSize(constants->getMainWindowWidth(),constants->getMainWindowHeight());
	renWinPerson->SetSize(constants->getPersonWindowWidth(),constants->getPersonWindowHeight());
	renWinCampus->SetSize(constants->getCampusWindowWidth(),constants->getCampusWindowHeight());
	

	renWinMain->AddRenderer(ren1);
	renWinPerson->AddRenderer(ren1);
	renWinCampus->AddRenderer(ren1);

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