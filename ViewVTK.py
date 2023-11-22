#!/usr/bin/env python
import vtk
import numpy as np
import vtkmodules.vtkInteractionStyle
# noinspection PyUnresolvedReferences
import vtkmodules.vtkRenderingOpenGL2
import vtkmodules.vtkCommonMath
from vtkmodules.vtkCommonColor import vtkNamedColors
from vtkmodules.vtkFiltersSources import vtkSphereSource, vtkCylinderSource
from vtkmodules.vtkIOImage import (
    vtkBMPWriter,
    vtkJPEGWriter,
    vtkPNGWriter,
    vtkPNMWriter,
    vtkPostScriptWriter,
    vtkTIFFWriter
)
from vtkmodules.vtkFiltersGeneral import vtkTransformPolyDataFilter
from vtkmodules.vtkCommonTransforms import vtkTransform
from vtkmodules.vtkRenderingCore import (
    vtkActor,
    vtkPolyDataMapper,
    vtkRenderWindow,
    vtkRenderWindowInteractor,
    vtkRenderer,
    vtkWindowToImageFilter
)
from vtkmodules.vtkCommonCore import (
    vtkMath
    )

data = np.genfromtxt("data.txt") #Modificar para datos con otros nombres

data[:,2] *= 3
def main():
    colors = vtkNamedColors()
    # Set the background color.
    bkg = map(lambda x: x / 255.0, [0, 0, 0, 255])
    colors.SetColor("BkgColor", *bkg)


    atoms=[]
    bonds=[]
    ren = vtkRenderer()
    renWin = vtkRenderWindow()
    renWin.AddRenderer(ren)
    iren = vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)
    for i in range(0,len(data)-1):
        #Se genera cada vez el átomo y el cilindro que representa el enlace. El último átomo no tiene enlace, así que se guarda aparte
        atom = vtkSphereSource()
        atom.SetCenter(data[i,0],data[i,1],data[i,2])
        r=0.05
        atom.SetRadius(r)
        atom.SetPhiResolution(100)
        atom.SetThetaResolution(100)
        atoms.append(atom)
        atomMapper = vtkPolyDataMapper()
        atomMapper.SetInputConnection(atom.GetOutputPort())
        
        #La visualización del cilindro sigue el tutorial en https://examples.vtk.org/site/Python/GeometricObjects/OrientedCylinder/
        bond=vtkCylinderSource()
        bond.SetResolution(15)
        start = data[i]
        end=data[i+1]
        x = end-start
        length = np.linalg.norm(x)
        z=[0,0,1]
        y=[0,1,0]

        vtkMath.Normalize(x)
        vtkMath.Cross(x, y, z)
        vtkMath.Normalize(z)
        vtkMath.Cross(z, x, y)
        matrix = vtkmodules.vtkCommonMath.vtkMatrix4x4()
        matrix.Identity()
        for i in range(0, 3):
            matrix.SetElement(i, 0, x[i])
            matrix.SetElement(i, 1, y[i])
            matrix.SetElement(i, 2, z[i])
        transform = vtkTransform()
        transform.Translate(start)  # translate to starting point
        transform.Concatenate(matrix)  # apply direction cosines
        transform.RotateZ(-90.0)  # align cylinder to x axis
        transform.Scale(r/5, length, r/5)
        transform.Translate(0, .5, 0)
        transformPD = vtkTransformPolyDataFilter()
        transformPD.SetTransform(transform)
        transformPD.SetInputConnection(bond.GetOutputPort())
        bondMapper = vtkPolyDataMapper()
    
        # The actor is a grouping mechanism: besides the geometry (mapper), it
        # also has a property, transformation matrix, and/or texture map.
        # Here we set its color and rotate it -22.5 degrees.
        bondActor =vtkActor()
        atomActor = vtkActor()
        atomActor.SetMapper(atomMapper)
        
        atomActor.GetProperty().SetColor(colors.GetColor3d("White"))
        bondMapper.SetInputConnection(bond.GetOutputPort())
        bondActor.SetUserMatrix(transform.GetMatrix())
        bondActor.GetProperty().SetColor(colors.GetColor3d("Yellow"))
        
        bondActor.SetMapper(bondMapper)
        # cylinderActor.RotateX(30.0)
        # cylinderActor.RotateY(-45.0)
    
        # Create the graphics structure. The renderer renders into the render
        # window. The render window interactor captures mouse events and will
        # perform appropriate camera or actor manipulation depending on the
        # nature of the events.
        
    
        # Add the actors to the renderer, set the background and size
        # ren.AddActor(cylinderActor)
        ren.SetBackground(colors.GetColor3d("BkgColor"))
        renWin.SetSize(300, 300)
        ren.AddActor(bondActor)
        ren.AddActor(atomActor)
        renWin.SetWindowName('CylinderExample')
    
        # This allows the interactor to initalize itself. It has to be
        # called before an event loop.
    iren.Initialize()

    # We'll zoom in a little by accessing the camera and invoking a "Zoom"
    # method on it.
    ren.ResetCamera()
    ren.GetActiveCamera().Zoom(1.5)
    renWin.Render()
    # Start the event loop.
    renWin.SetWindowName('ImageWriter')
    renWin.Render()

    ext = ['', '.png', '.jpg']
    filenames = list(map(lambda x: 'ImageWriter' + x, ext))
    filenames[0] = filenames[0] + '1'
    for f in filenames:
        WriteImage(f, renWin, rgba=False)
    iren.Start()


def WriteImage(fileName, renWin, rgba=True):
    '''
    Write the render window view to an image file.

    Image types supported are:
     BMP, JPEG, PNM, PNG, PostScript, TIFF.
    The default parameters are used for all writers, change as needed.

    :param fileName: The file name, if no extension then PNG is assumed.
    :param renWin: The render window.
    :param rgba: Used to set the buffer type.
    :return:
    '''

    import os

    if fileName:
        # Select the writer to use.
        path, ext = os.path.splitext(fileName)
        ext = ext.lower()
        if not ext:
            ext = '.png'
            fileName = fileName + ext
        if ext == '.bmp':
            writer = vtkBMPWriter()
        elif ext == '.jpg':
            writer = vtkJPEGWriter()
        elif ext == '.pnm':
            writer = vtkPNMWriter()
        elif ext == '.ps':
            if rgba:
                rgba = False
            writer = vtkPostScriptWriter()
        elif ext == '.tiff':
            writer = vtkTIFFWriter()
        else:
            writer = vtkPNGWriter()

        windowto_image_filter = vtkWindowToImageFilter()
        windowto_image_filter.SetInput(renWin)
        windowto_image_filter.SetScale(1)  # image quality
        if rgba:
            windowto_image_filter.SetInputBufferTypeToRGBA()
        else:
            windowto_image_filter.SetInputBufferTypeToRGB()
            # Read from the front buffer.
            windowto_image_filter.ReadFrontBufferOff()
            windowto_image_filter.Update()

        writer.SetFileName(fileName)
        writer.SetInputConnection(windowto_image_filter.GetOutputPort())
        writer.Write()
    else:
        raise RuntimeError('Need a filename.')

if __name__ == '__main__':
    main()
