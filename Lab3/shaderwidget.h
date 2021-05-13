#pragma once
#include<QtOpenGL>
#include<QTimer>
#include<qimage.h>
#include<algorithm>
#include<QOpenGLFunctions_4_3_Core>

class ShaderWidget : public QOpenGLWidget{
private:
    const double PI = acos(-1.);
    QOpenGLShaderProgram prog;
    GLfloat* data;
    int pos;
    int lightX, lightY, lightZ;
    QOpenGLFunctions_4_3_Core* functions;
    GLuint ssbo = 0;
    struct Sphere{
        QVector3D position;
        float radius;
        QVector3D color;
        int material_ind;
    };
    struct Camera{
        QVector3D pos;
        QVector3D view;
        QVector3D up;
        QVector3D side;
        double R;
    };
    struct Triangle{
        QVector3D v1, v2, v3;
        int material_ind;
    };

    Camera camera;
    double ang, phi, teta;


protected:
    void initializeGL() override;
    void resizeGL(int nwidth, int nheight) override;
    void paintGL() override;
public:
    ShaderWidget(QWidget* parent = 0, int x = 0, int y = 0, int z = 0);
    virtual ~ShaderWidget();
public slots:
    void keyPressEvent(QKeyEvent* event) override;
};

