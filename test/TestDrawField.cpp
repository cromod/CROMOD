/** 
 * @file TestDrawField.cpp
 * @brief Test to draw field
 * @author cromod
 * @date september 2015
 */

#include <mgl2/glut.h>
#include <mgl2/mgl.h>
#include <iostream>
#include "GradField.hpp"
#include "Exception.hpp"


using namespace Cromod::GeomAPI ;
using namespace Cromod::FieldAPI ;
using namespace Cromod::Tools ;
using namespace std ;

void mgls_prepare2d(mglData *a)
{
    double listVal[13][2] = {{200.,-100.},{200.,50.},{150.,100.},{100.,100.},{100.,200.},{-100.,200.},{-100.,100.},
                                         {-200.,100.},{-200.,-100.},{-100.,-100.},{-100.,-200.},{100.,-200.},{100.,-100.}};
    vector<Point> listPoints;
    for(int i=0; i<13; i++) {
        Point point(listVal[i],2);
        listPoints.push_back(point);
    }
    Polygon polygon(listPoints);
    
    Mesh mesh;
    mesh.setPolygon(polygon);
    mesh.setStep(10.);
    mesh.setInitGrid();
    mesh.detectNode();
    
    double ptA[] = {200.,50.};
    double ptB[] = {150.,100.};
    Point pointA(ptA,2);
    Point pointB(ptB,2);
    Segment segment(pointA,pointB);
    vector<Segment> listExit;
    listExit.push_back(segment);
    
    cout << "Building the field of distance..." << endl;
    DistField distfield(mesh,listExit);
    cout << "Plot the field of distance..." << endl;
    register long i,j,n=100,m=100,i0;
    a->Create(n,m);
    double x,y;
    for(i=0;i<n;i++)  for(j=0;j<m;j++)
    {
        x = 200.*(static_cast<double>(2*i)/static_cast<double>(n)-1.);
        y = 200.*(static_cast<double>(2*j)/static_cast<double>(m)-1.);
        i0 = i+n*j;
        double dist = distfield.interpolate(x,y)[0];
        if(dist < VAL_INFINITY) a->a[i0] = dist;
        else a->a[i0] = 0.;
    }
}

int draw(mglGraph *gr)
{
    mglData a(200,200,1);  mgls_prepare2d(&a);
    gr->SetRanges(-200,200,-200,200,0,500);
    
    gr->SubPlot(1,1,0);  gr->Title("Density");
    gr->Box();  gr->Dens(a);

    //gr->SubPlot(1,1,0); gr->Title("Surf plot (default)");
    //gr->Light(true);  gr->Rotate(50,60);  gr->Box();  gr->Surf(a);
    
    return 0;
}

int main(int argc,char **argv)
{
  mglGLUT gr(draw,"Graph of distance field");
  return 0;
}