/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: Mace.cxx,v $
  Language:  C++
  Date:      $Date: 2002/11/08 19:04:55 $
  Version:   $Revision: 1.2 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkActor.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRegressionTestImage.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkRenderer.h"
#include "vtkSphereSource.h"
#include "vtkAutoInit.h" 
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

#pragma comment(lib, "vtkCommonCore-9.0d.lib")
#pragma comment(lib, "vtkFiltersCore-9.0d.lib")
#pragma comment(lib, "vtkFiltersSources-9.0d.lib")
#pragma comment(lib, "vtkCommonExecutionModel-9.0d.lib")
#pragma comment(lib, "vtkRenderingCore-9.0d.lib")
#pragma comment(lib, "vtkTestingRendering-9.0d.lib")
#pragma comment(lib, "vtkRenderingOpenGL2-9.0d.lib")
#pragma comment(lib, "vtkInteractionStyle-9.0d.lib")

int main(int argc, char *argv[])
{
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);
    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

    vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetThetaResolution(8);
    sphere->SetPhiResolution(8);
    vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
    sphereMapper->SetInputConnection(sphere->GetOutputPort());
    vtkActor *sphereActor = vtkActor::New();
    sphereActor->SetMapper(sphereMapper);

    vtkConeSource *cone = vtkConeSource::New();
    cone->SetResolution(6);

    vtkGlyph3D *glyph = vtkGlyph3D::New();
    glyph->SetInputConnection(sphere->GetOutputPort());
    glyph->SetSourceConnection(cone->GetOutputPort());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleModeToScaleByVector();
    glyph->SetScaleFactor(0.25);

    vtkPolyDataMapper *spikeMapper = vtkPolyDataMapper::New();
    spikeMapper->SetInputConnection(glyph->GetOutputPort());

    vtkActor *spikeActor = vtkActor::New();
    spikeActor->SetMapper(spikeMapper);

    renderer->AddActor(sphereActor);
    renderer->AddActor(spikeActor);
    renderer->SetBackground(1, 1, 1);
    renWin->SetSize(300, 300);

    // interact with data
    renWin->Render();

    int retVal = vtkRegressionTestImage(renWin);

    if (retVal == vtkRegressionTester::DO_INTERACTOR)
    {
        iren->Start();
    }
    // Clean up
    renderer->Delete();
    renWin->Delete();
    iren->Delete();
    sphere->Delete();
    sphereMapper->Delete();
    sphereActor->Delete();
    cone->Delete();
    glyph->Delete();
    spikeMapper->Delete();
    spikeActor->Delete();

    return !retVal;
}
