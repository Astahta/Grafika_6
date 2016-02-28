#include "Point.h"


Point::Point()
{
    //point
    x = 0;
    y = 0;
    z = 0;
    tag = 1; //elemen terakhir sebagai pelengkap, untuk keperluan transformasi

    //nilai default matrix (4x4)
    for(int i=0; i<4; i++){
        vector<float> row(4);
        for(int j=0; j<4; j++){
           matrix.push_back(row);
        }
    }
}


Point::Point(float xnew, float ynew, float znew){
    //point
    x = xnew;
    y = ynew;
    z = znew;
    tag = 1; //elemen terakhir sebagai pelengkap, untuk keperluan transformasi

    //nilai default matrix (4x4)
    for(int i=0; i<4; i++){
        vector<float> row(4);
        for(int j=0; j<4; j++){
           matrix.push_back(row);
        }
    }
}

Point::~Point()
{
    //dtor
}


 void Point::transformation (){
    //melakukan transformasi "matrix" terhadap "point"
    vector<float> temp;
    for (int i=0; i<4; i++){
        float result;
        result = x * matrix[0][i] + y * matrix[1][i] + z * matrix[2][i] + tag * matrix[3][i];
        temp.push_back(result);
    }

    //pembagian dengan komponen terakhir vektor 3d
    temp[0] = temp[0] / temp[3];
    temp[1] = temp[1] / temp[3];
    temp[2] = temp[2] / temp[3];


    //Asign nilai point dengan nilai baru
    x = temp[0];
    y = temp[1];
    z = temp[2];
    tag = temp[3];
}

void Point::clearMatrix(){
     for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
          matrix[j][i]=0;
        }
    }
}

 void Point::translation(float dx, float dy, float dz){
    clearMatrix();
    matrix[0][0]=1; //Transform_XAxis
    matrix[1][1]=1; //Transform_YAxis
    matrix[2][2]=1; //Transform_ZAxis
    matrix[3][3]=1; //nilai akhir matrix

    //nilai translasi
    matrix[3][0]=dx;
    matrix[3][1]=dy;
    matrix[3][2]=dz;
    transformation();
 }


void Point::scale(float scaleX, float scaleY, float scaleZ){
    clearMatrix();
    matrix[0][0]=scaleX;
    matrix[1][1]=scaleY;
    matrix[2][2]=scaleZ;
    matrix[3][3]=1; //nilai akhir matrix
    transformation();
}


void Point::rotateX(float degree){
    //ClockWise
    float degreeRadian = degree * PI / 180.0;
    clearMatrix();
    matrix[0][0]=1;
    matrix[3][3]=1;
    matrix[1][1]=cos(degreeRadian);
    matrix[1][2]=sin(degreeRadian);
    matrix[2][1]=sin(degreeRadian)*(-1);
    matrix[2][2]=cos(degreeRadian);
    transformation();
}


void Point::rotateY(float degree){
    //ClockWise
    float degreeRadian = degree * PI / 180.0;
    clearMatrix();
    matrix[1][1]=1;
    matrix[3][3]=1;
    matrix[0][0]=cos(degreeRadian);
    matrix[2][0]=sin(degreeRadian);
    matrix[0][2]=sin(degreeRadian)*(-1);
    matrix[2][2]=cos(degreeRadian);
    transformation();
}


void Point::rotateZ(float degree){
     //ClockWise
    float degreeRadian = degree * PI / 180.0;
    clearMatrix();
    matrix[2][2]=1;
    matrix[3][3]=1;
    matrix[0][0]=cos(degreeRadian);
    matrix[0][1]=sin(degreeRadian);
    matrix[1][0]=sin(degreeRadian)*(-1);
    matrix[1][1]=cos(degreeRadian);
    transformation();
}

vector< vector<float> > Point::getMatrix() {
    return matrix;
}

void Point::setX(float xnew) {
    x = xnew;
}

void Point::setY(float ynew) {
    y = ynew;
}

void Point::setZ(float znew) {
    z = znew;
}
