#ifndef __SHAPEGROUP
#define __SHAPEGROUP
#include "ShadowBuffer.h"
#include "Shape.h"
#include "util.cpp"

class ShapeGroup {
protected:
    void projectTo2D(float offsetX, float offsetY);
    void splitAvailable(vector<vector<Line> > &Available, vector<Point> demand, ShadowBuffer& sb, Color c);
    void sortLayer();
    void scanLineFill3D(ShadowBuffer& sb);
    int findZMax(vector<Point> plane);
    bool findIntersection(Point p1, Point p2, int y, int &x, int &z);
    vector<vector<Line> > initAvailable(int x1, int x2);
    vector<Point> sortVector(vector<Point> v);
    
public:
    Color color;
    vector<Shape> shapes;
    vector<vector<Point> > pointToPrint;

    ShapeGroup(string objName, float offsetX, float offsetY, int scale);

    void draw(ShadowBuffer& sb, float offsetX, float offsetY);
    void drawClipped(ShadowBuffer& sb, Point min, Point max, float scale);
    void translate(float dX, float dY,float dZ);
    void scale(float scaleX, float scaleY, float scaleZ, float offsetX, float offsetY, float offsetZ);
    void rotateX(float degree, float offsetX, float offsetY, float offsetZ);
    void rotateY(float degree, float offsetX, float offsetY, float offsetZ);
    void rotateZ(float degree, float offsetX, float offsetY, float offsetZ);

    Point * getTipPoints();
};

#endif