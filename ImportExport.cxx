/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: ImportExport.cxx,v $
  Language:  C++
  Date:      $Date: 2002/08/08 13:54:44 $
  Version:   $Revision: 1.8 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkImageData.h"
#include "vtkImageViewer.h"
#include "vtkInformation.h"
#include "vtkAutoInit.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2);

#pragma comment(lib, "vtkCommonCore-9.0d.lib")
#pragma comment(lib, "vtkCommonDataModel-9.0d.lib")
#pragma comment(lib, "vtkInteractionImage-9.0d.lib")
#pragma comment(lib, "vtkRenderingOpenGL2-9.0d.lib")

int main(int argc, char *argv[])
{
    vtkImageData *image = vtkImageData::New();
    vtkInformation *info = vtkInformation::New();
    image->SetDimensions(256, 256, 1);
    image->SetScalarType(VTK_FLOAT, info);
    image->AllocateScalars(info);

    float *ptr = static_cast<float*>(image->GetScalarPointer());

    for (int y = 0; y < 256; ++y)
    {
        for (int x = 0; x < 256; ++x)
        {
            *ptr++ = 10.0 * sin(0.1 * x) * sin(0.1 * y);
        }
    }

    vtkImageViewer *viewer = vtkImageViewer::New();
    viewer->SetInputData(image);
    viewer->SetColorWindow(20.0);
    viewer->SetColorLevel(0.0);

    viewer->Render();

    Sleep(5000);
    image->Delete();
    viewer->Delete();
    info->Delete();

    return 0;
}



