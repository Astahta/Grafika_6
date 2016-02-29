#include "ShapeGroup.h"

ShapeGroup::ShapeGroup(string objName, float offsetX, float offsetY, int scale) {
    Util util;
    map<string, vector<Point> > point = util.readObject("point3d.txt");
    vector<vector<Point> > points = util.convertPoint(point, objName, offsetX, offsetY, 0, scale,  scale, scale);

    for (int j = 0; j < points.size(); j++) {
        Shape shape(points[j]);
        shape.color= Color(225,0,0);
        shapes.push_back(shape);
        // cout<<j<<endl;
        // for(int i = 0; i < points[j].size(); i++){
        //     cout<<i<<". x: "<<points[j][i].x<<" y; "<<points[j][i].y<<" z: "<<points[j][i].z<<endl;
        // }
    }
}

void ShapeGroup::draw(ShadowBuffer& sb, float offsetX, float offsetY) {
    /*for (int i = 0; i < shapes.size(); i++) {
        // shapes[i].draw(sb);
        Color c(225,225,0);
        shapes[i].drawBorder(c, sb);
    }*/
    setPointToDraw(offsetX,offsetY);
    scanLineFill3D(sb);

    /*for (int j = 0; j < pointToPrint.size(); j++) {
        Color c = Color(j*j*4,j*20,250-j*15);
        for(int i=0; i< pointToPrint[j].size(); i++){
            vector<Point> p;
            if(i==pointToPrint[j].size()-1){
                p.push_back(pointToPrint[j][i]);
                p.push_back(pointToPrint[j][0]);
        
            }else{
                p.push_back(pointToPrint[j][i]);
                p.push_back(pointToPrint[j][i+1]);
            }
            Line line(p);
            line.color = c;
            line.draw(sb);
        }
    }*/
}

void ShapeGroup::drawView(ShadowBuffer& sb) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].drawView(sb);
    }
}

void ShapeGroup::translate(float dX, float dY, float dZ) {
    for (int i = 0; i < shapes.size(); i++) {
        for (int j=0; j<shapes[i].points.size();j++){
             shapes[i].points[j].translation(dX, dY, dZ);


  //pembulatan
             shapes[i].points[j].setX(roundf(shapes[i].points[j].x * 100) / 100);
             shapes[i].points[j].setY(roundf(shapes[i].points[j].y * 100) / 100);
             shapes[i].points[j].setZ(roundf(shapes[i].points[j].z * 100) / 100);
        }
    }
}

void ShapeGroup::scale(float scaleX, float scaleY, float scaleZ, float offsetX, float offsetY, float offsetZ) {
    translate(offsetX*(-1),offsetY*(-1), offsetZ*(-1));
    for (int i = 0; i < shapes.size(); i++) {
        for (int j=0; j<shapes[i].points.size();j++){
             shapes[i].points[j].scale(scaleX, scaleY, scaleZ);

                 //pembulatan
             shapes[i].points[j].setX(roundf(shapes[i].points[j].x * 100) / 100);
             shapes[i].points[j].setY(roundf(shapes[i].points[j].y * 100) / 100);
             shapes[i].points[j].setZ(roundf(shapes[i].points[j].z * 100) / 100);
        }
    }
    translate(offsetX,offsetY, offsetZ);
}

void ShapeGroup::rotateX(float degree, float offsetX, float offsetY, float offsetZ) {
    translate(offsetX*(-1),offsetY*(-1), offsetZ*(-1));
    for (int i = 0; i < shapes.size(); i++) {
        for (int j=0; j<shapes[i].points.size();j++){
             shapes[i].points[j].rotateX(degree);

                 //pembulatan
             shapes[i].points[j].setX(roundf(shapes[i].points[j].x * 100) / 100);
             shapes[i].points[j].setY(roundf(shapes[i].points[j].y * 100) / 100);
             shapes[i].points[j].setZ(roundf(shapes[i].points[j].z * 100) / 100);
        }
    }
    translate(offsetX,offsetY, offsetZ);
}

void ShapeGroup::rotateY(float degree, float offsetX, float offsetY, float offsetZ) {
    translate(offsetX*(-1),offsetY*(-1), offsetZ*(-1));
    for (int i = 0; i < shapes.size(); i++) {
        for (int j=0; j<shapes[i].points.size();j++){
             shapes[i].points[j].rotateY(degree);

                 //pembulatan
             shapes[i].points[j].setX(roundf(shapes[i].points[j].x * 100) / 100);
             shapes[i].points[j].setY(roundf(shapes[i].points[j].y * 100) / 100);
             shapes[i].points[j].setZ(roundf(shapes[i].points[j].z * 100) / 100);
        }
    }
    translate(offsetX,offsetY, offsetZ);
}

void ShapeGroup::rotateZ(float degree, float offsetX, float offsetY, float offsetZ) {
    translate(offsetX*(-1),offsetY*(-1), offsetZ*(-1));
    for (int i = 0; i < shapes.size(); i++) {
        for (int j=0; j<shapes[i].points.size();j++){
             shapes[i].points[j].rotateZ(degree);

                 //pembulatan
             shapes[i].points[j].setX(roundf(shapes[i].points[j].x * 100) / 100);
             shapes[i].points[j].setY(roundf(shapes[i].points[j].y * 100) / 100);
             shapes[i].points[j].setZ(roundf(shapes[i].points[j].z * 100) / 100);
        }
    }
    translate(offsetX,offsetY, offsetZ);
}

void ShapeGroup::clip(Point min, Point max, float scale) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].clip(min,max,scale);
    }
}



Point * ShapeGroup::getTipPoints() {
    Point * tipPoints = shapes[0].getTipPoints();

    for (int i = 1; i < shapes.size(); i++) {
        Point * tp = shapes[i].getTipPoints();
        if (tipPoints[0].x > tp[0].x) {
            tipPoints[0].x = tp[0].x;
        }

        if (tipPoints[0].y > tp[0].y) {
            tipPoints[0].y = tp[0].y;
        }

        if (tipPoints[1].x < tp[1].x) {
            tipPoints[1].x = tp[1].x;
        }

        if (tipPoints[1].y < tp[1].y) {
            tipPoints[1].y = tp[1].y;
        }
    }

    return tipPoints;
}

int ShapeGroup::findZMax(vector<Point> plan){
    int max= -99;
    for(int x=0;x< plan.size();x++){
        if(max< plan[x].z)
            max= plan[x].z;
    }
    return max;
}

void ShapeGroup::sortLayer(){
    int i, j, numLength = pointToPrint.size();
     vector<Point> key;
     for(j = 1; j < numLength; j++)    // Start with 1 (not 0)
    {
           key = pointToPrint[j];
           for(i = j - 1; (i >= 0) && (findZMax(pointToPrint[i]) > findZMax(key)); i--)   // Smaller values move up
          {
                 pointToPrint[i+1] = pointToPrint[i];
          }
         pointToPrint[i+1] = key;    //Put key into its proper location
     }
}

void ShapeGroup::setPointToDraw(float offsetX, float offsetY){
    pointToPrint.clear();
    //cout<<"CEK"<<endl;
    for(int i=0; i<shapes.size(); i++){
        vector<Point> temp;
        //cout<<i<<endl;
        for(int j=0; j<shapes[i].points.size(); j++){
            float newX = (offsetX + (shapes[i].points[j].x - offsetX) * pow((1.01),shapes[i].points[j].z * 0.1));
            float newY = (offsetY + (shapes[i].points[j].y - offsetY) * pow((1.01),shapes[i].points[j].z * 0.1));
            Point p(newX, newY, shapes[i].points[j].z );
            //cout<<j<<" x: "<<newX<<" y: "<<newY<<endl;
            temp.push_back(p);
        }
        pointToPrint.push_back(temp);
    }
    /*for (int i = 0; i < pointToPrint.size(); i++){
        cout<<i<<endl;
        for(int j = 0; j < pointToPrint[i].size();j++){
            cout<<j<<" x: "<<pointToPrint[i][j].x<<" y: "<<pointToPrint[i][j].y<<" z: "<<pointToPrint[i][j].z<<endl;
        }
    }*/
    //sortLayer();
}

vector<Point> ShapeGroup::sortVector(vector<Point> v) {

     int i, j, numLength = v.size();
     Point key;
     for(j = 1; j < numLength; j++)    // Start with 1 (not 0)
    {
           key = v[j];
           for(i = j - 1; (i >= 0) && (v[i].x > key.x); i--)   // Smaller values move up
          {
                 v[i+1] = v[i];
          }
         v[i+1] = key;    //Put key into its proper location
     }
     return v;
}

bool ShapeGroup::findIntersection(Point p1, Point p2, int y, int &x, int &z) {
    if(p1.y==p2.y)
        return false;
    x = (p2.x-p1.x)*(y-p1.y)/(p2.y-p1.y) + p1.x;
    z = 0;
    bool isInsideEdgeX;
    bool isInsideEdgeY;
    if(p1.x < p2.x) 
        isInsideEdgeX = (p1.x <= x) && (x <= p2.x);
    else 
        isInsideEdgeX = (p2.x <= x) && (x <= p1.x);

    if(p1.y < p2.y)
        isInsideEdgeY = (p1.y <= y) && (y <= p2.y);
    else
        isInsideEdgeY = (p2.y <= y) && (y <= p1.y);

    return isInsideEdgeX && isInsideEdgeY;
}


void ShapeGroup::splitAvailable(vector<vector<Line> > &Available, vector<Point> demand, ShadowBuffer& sb, Color c){
    vector<Line> available= Available[Available.size() - 1];

    for(int j=0; j<demand.size();j+=2){
        //int j=0;
        vector<Line> newAvailable;
        for(int i= 0; i < available.size(); i++ ){
            if(available[i].getPoint2().x<=available[i].getPoint1().x){//sudah tidak ada slot
                newAvailable.push_back(available[i]);   
                break;
            }
            if(demand[j].x > available[i].getPoint2().x){//demand berada di kanan available
                newAvailable.push_back(available[i]); 
                break;
            }
            if(demand[j+1].x < available[i].getPoint1().x){ //demand di kiri available
                newAvailable.push_back(available[i]); 
                continue;
            }
            if((available[i].getPoint1().x <= demand[j].x)&&(demand[j+1].x <= available[i].getPoint2().x)){ //demand berada di tengah
                Line split1(available[i].getPoint1(), Point(demand[j].x-1, available[i].getPoint1().y,0));

                Line split2(Point(demand[j+1].x+1,available[i].getPoint2().y,0), available[i].getPoint2());

                newAvailable.push_back(split1);
                newAvailable.push_back(split2);

                if (j+1 < demand.size()) {
                    Line line(demand[j], demand[j+1]);
                    line.color = c;
                    line.draw(sb);
                }

            }else if(available[i].getPoint1().x <= demand[j].x){ //demand lebih banyak kebelakang

                Line split(available[i].getPoint1(), Point(demand[j].x-1, available[i].getPoint1().y,0));
                newAvailable.push_back(split);

                Line line(demand[j], Point(available[i].getPoint2().x,demand[j].y,0));
                line.color = c;
                line.draw(sb);

            }else if(demand[j+1].x <= available[i].getPoint2().x){ //demand lebih banyak di depan
                Line split(Point(demand[j+1].x+1,available[i].getPoint2().y,0), available[i].getPoint2());

                Line line(Point(available[i].getPoint1().x,demand[j+1].y,0),demand[j+1]);
                line.color = c;
                line.draw(sb);

                newAvailable.push_back(split);
            }
        }
    //update info available
    Available.push_back(newAvailable);

    }

}


vector<vector<Line> > ShapeGroup::initAvailable(int x1, int x2){
    vector<vector<Line> > available;
    vector<Line> init;
    Line l(Point(x1,0,0),Point(x2,0,0));
    init.push_back(l);
    available.push_back(init);

    return available;
}

void ShapeGroup::scanLineFill3D(ShadowBuffer& sb)
{    

    Point p1, p2;   

    int nShape = pointToPrint.size();
    //int edgesSize = v.size();
    int a=0;
    for(int k=0; k < nShape; k++){
        Shape tempShape = pointToPrint[k];
        Color c(225-a, 200-a, 200-a);
        a+=10;
        Point * tipPoints = getTipPoints();
        for(int i = tipPoints[0].y; i < tipPoints[1].y; i++) {
            vector<vector<Line> > available= initAvailable(0,1020);
            vector<Point> ListOfIntersectPoints;
            int edgesSize = tempShape.points.size();
            for(int j = 0; j < tempShape.points.size(); j++) {
                if(j != (edgesSize - 1)){
                    p1 = tempShape.points[j];
                    p2 = tempShape.points[j+1];
                }else{
                    p1 = tempShape.points[j];
                    p2 = tempShape.points[0];
                }
                int intersectX, intersectZ;
                if (findIntersection(p1,p2,i,intersectX, intersectZ)){
                    if(p1.y > p2.y){
                        std::swap(p1,p2);
                    }
                    Point intersect(intersectX, i,intersectZ);
                    if(intersect.y == p2.y)
                        continue;
                    ListOfIntersectPoints.push_back(intersect);
                }
            }

            vector<Point> result = sortVector(ListOfIntersectPoints);          
            splitAvailable(available, result, sb, c);            
        } 
    }
}