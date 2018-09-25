#include "My_OpenGl.h"

/*
*默认是不锈钢颜色，顶点着色器和片段着色器
*/
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 color;\n"
    "layout (location = 2) in vec3 colorLine;\n"
    "out vec4 col;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "uniform bool useLineColor;\n"
    "void main()\n"
    "{\n"
    " gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    " if(useLineColor) col = vec4(colorLine.x/255.0f, colorLine.y/255.0f, colorLine.z/255.0f, 1.0);\n"
    " else col = vec4(color.x/255.0f, color.y/255.0f, color.z/255.0f, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec4 col;\n"
    "void main()\n"
    "{\n"
    " FragColor = col;\n"
    "}\n\0";

my_OpenGL::my_OpenGL(int width, int height ,QWidget *parent):QOpenGLWidget(parent)
{
    /*
    *初始化参数列表
    */
    windowWidth = width;
    windowHeight = height;
    setMinimumSize(windowWidth, windowHeight);
    m_nodeVector = nodeVector;
    m_indices = indices;
    if(dataType == 1)//位移数据
    {
        m_dataType = "Total Deformation";
        m_dataUnit = shiftUnit.remove("(").remove(")");
        m_iconPara = ModelInfo_MaxShift;
        m_iconParaLow = ModelInfo_MinShift;
        m_showIcon = true;
        gridDisplay = false;
        for(int i = 0; i<shiftVector.length(); i++)
        {
            if((shiftVector.at(i) <= m_iconPara) && (shiftVector.at(i) > 0.75f * m_iconPara))
            {
                m_colorVector.append(255.0);
                m_colorVector.append(1020.0f - 1020.0f*shiftVector.at(i)/m_iconPara);
                m_colorVector.append(0.0);
            }
            else if((shiftVector.at(i) <= 0.75f * m_iconPara) && (shiftVector.at(i) > 0.50f * m_iconPara))
            {
                m_colorVector.append(1020.0f*shiftVector.at(i)/m_iconPara - 1020.0/2.0);
                m_colorVector.append(255.0);
                m_colorVector.append(0.0);
            }
            else if((shiftVector.at(i) <= 0.50f * m_iconPara) && (shiftVector.at(i) > 0.25f * m_iconPara))
            {
                m_colorVector.append(0.0);
                m_colorVector.append(255.0);
                m_colorVector.append(1020.0/2.0 - 1020.0f*shiftVector.at(i)/m_iconPara);
            }
            else
            {
                m_colorVector.append(0.0);
                m_colorVector.append(1020.0f*shiftVector.at(i)/m_iconPara);
                m_colorVector.append(255.0);
            }
        }
    }
    else if(dataType == 2)//应变数据
    {
        m_dataType = "Equivalent Elastic Strain";
        m_dataUnit = strainUnit.remove("(").remove(")");
        m_iconPara = ModelInfo_MaxStrain;
        m_iconParaLow = ModelInfo_MinStrain;
        m_showIcon = true;
        gridDisplay = false;
        for(int i = 0; i<strainVector.length(); i++)
        {
            if((strainVector.at(i) <= m_iconPara) && (strainVector.at(i) > 0.75f * m_iconPara))
            {
                m_colorVector.append(255.0);
                m_colorVector.append(1020.0f - 1020.0f*strainVector.at(i)/m_iconPara);
                m_colorVector.append(0.0);
            }
            else if((strainVector.at(i) <= 0.75f * m_iconPara) && (strainVector.at(i) > 0.50f * m_iconPara))
            {
                m_colorVector.append(1020.0f*strainVector.at(i)/m_iconPara - 1020.0/2.0);
                m_colorVector.append(255.0);
                m_colorVector.append(0.0);
            }
            else if((strainVector.at(i) <= 0.50f * m_iconPara) && (strainVector.at(i) > 0.25f * m_iconPara))
            {
                m_colorVector.append(0.0);
                m_colorVector.append(255.0);
                m_colorVector.append(1020.0/2.0 - 1020.0f*strainVector.at(i)/m_iconPara);
            }
            else
            {
                m_colorVector.append(0.0);
                m_colorVector.append(1020.0f*strainVector.at(i)/m_iconPara);
                m_colorVector.append(255.0);
            }
        }
    }
    else if(dataType == 3)//应力数据
    {
        m_dataType = "Equivalent (von-Mises) Stress";
        m_dataUnit = stressUnit.remove("(").remove(")");
        m_iconPara = ModelInfo_MaxStress;
        m_iconParaLow = ModelInfo_MinStress;
        m_showIcon = true;
        gridDisplay = false;
        for(int i = 0; i<stressVector.length(); i++)
        {
            if((stressVector.at(i) <= m_iconPara) && (stressVector.at(i) > 0.75f * m_iconPara))
            {
                m_colorVector.append(255.0);
                m_colorVector.append(1020.0f - 1020.0f*stressVector.at(i)/m_iconPara);
                m_colorVector.append(0.0);
            }
            else if((stressVector.at(i) <= 0.75f * m_iconPara) && (stressVector.at(i) > 0.50f * m_iconPara))
            {
                m_colorVector.append(1020.0f*stressVector.at(i)/m_iconPara - 1020.0/2.0);
                m_colorVector.append(255.0);
                m_colorVector.append(0.0);
            }
            else if((stressVector.at(i) <= 0.50f * m_iconPara) && (stressVector.at(i) > 0.25f * m_iconPara))
            {
                m_colorVector.append(0.0);
                m_colorVector.append(255.0);
                m_colorVector.append(1020.0/2.0 - 1020.0f*stressVector.at(i)/m_iconPara);
            }
            else
            {
                m_colorVector.append(0.0);
                m_colorVector.append(1020.0f*stressVector.at(i)/m_iconPara);
                m_colorVector.append(255.0);
            }
        }
    }
    else//几何数据
    {
        m_dataType = "Geometry";
        m_dataUnit = "mm";//待改，几何数据中还没有单位信息
        m_colorVector.fill(190.0f, nodeVector.length());
        m_iconPara = 0.0;
        m_iconParaLow = 0.0;
        m_showIcon = false;
        gridDisplay = true;
    }
    m_lineVector.fill(0.0f, nodeVector.length());
    coordinateSize = ((int)qMax(qAbs(coordinateRange_Down), qAbs(coordinateRange_Up)) / 100 + 1) * 100.0f;

    /*
    *信息框嵌入显示
    */
    m_information = new Information_OpenGL(windowHeight ,this);
    m_information->setPara(m_iconPara, m_iconParaLow, m_dataType, m_dataUnit, m_showIcon);
    m_information->show();

    /*
    *OpenGL格式设置。深度缓冲与模板缓冲，未开启多重采样
    */
    QSurfaceFormat format;
//    format.setSamples(4);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    QSurfaceFormat::setDefaultFormat(format);

    /*
    *其他参数初始化
    */
    lastX = windowWidth / 2.0f;   //设置初始化位置
    lastY = windowHeight / 2.0f;
    firstMouse = true;         //记录是否第一次移动鼠标，防止抖动
    deltaTime = 0.0f;	        //记录当前帧与上一帧的时间差
    lastFrame = 0.0f;          //记录上一次运行时间
    m_frame = 0;

    /*
    *平移与缩放系数初始化
    */
    x_translation = 0.0;
    y_translation = 0.0;
    scaleNum = 0.0;
    scaleAll_xAndy = 1.0;

    /*
    *控制变量初始化
    */
    graphDisplay = false;

    /*
    *单击窗口获取窗口焦点，执行键盘事件
    */
    setFocusPolicy(Qt::ClickFocus);

    /*
    *初始化旋转球
    */
    m_arcball = new ArcBall(windowWidth, windowHeight);
}

my_OpenGL::~my_OpenGL()
{
    makeCurrent();

    delete m_vertex_shader;
    delete m_fragment_shader;
    delete m_program;

    glDeleteBuffers(1,&VAO);
    glDeleteBuffers(3, VBO);
    glDeleteBuffers(1,&EBO);

    doneCurrent();
}

void my_OpenGL::initializeGL()
{
    initializeOpenGLFunctions();
    setAutoFillBackground(false);

    m_vertex_shader = new QOpenGLShader(QOpenGLShader::Vertex);
    m_vertex_shader->compileSourceCode(vertexShaderSource);

    m_fragment_shader = new QOpenGLShader(QOpenGLShader::Fragment);
    m_fragment_shader->compileSourceCode(fragmentShaderSource);

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShader(m_vertex_shader);
    m_program->addShader(m_fragment_shader);
    m_program->link();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(3, VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_nodeVector.size(), &m_nodeVector[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_colorVector.size(), &m_colorVector[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_lineVector.size(), &m_lineVector[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, *(m_indices-4), m_indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthRange(0,1);
    glDisable(GL_MULTISAMPLE);

    if(windowWidth <= windowHeight)
        projection.ortho(-coordinateSize, coordinateSize, -coordinateSize*windowHeight/windowWidth, coordinateSize*windowHeight/windowWidth, -coordinateSize*10.0, coordinateSize*10.0);
    else
        projection.ortho(-coordinateSize*windowWidth/windowHeight, coordinateSize*windowWidth/windowHeight, -coordinateSize, coordinateSize, -coordinateSize*10.0, coordinateSize*10.0);
    view.lookAt(QVector3D(0,0,0),QVector3D(0,0,0),QVector3D(0,1,0));
}

void my_OpenGL::paintGL()
{
    //获取两次调用glutget函数的时间差
    float currentFrame = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    //计算帧率，每十帧图像更新一次FPS，否则更新太快，看不清
    if(m_frame % 10 == 0)
        m_information->m_FPS = 1000.0f / deltaTime;

    //显示视口，与屏幕分辨率有关
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    //清除颜色缓冲数据和深度缓冲数据
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //[1]渐变色背景
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-width() / 2.0f, -height() / 2.0f, -coordinateSize*9.0f);
    glVertex3f(width() / 2.0f, -height() / 2.0f, -coordinateSize*9.0f);
    glColor3f(0.42f, 0.55f, 0.87f);
    glVertex3f(width() / 2.0f, height() / 2.0f, -coordinateSize*9.0f);
    glVertex3f(-width() / 2.0f, height() / 2.0f, -coordinateSize*9.0f);
    glEnd();
    glPopMatrix();
    //[1]

    //[2]右下角坐标系
    glPushMatrix();
    glTranslatef(width() / 4.0f, -height() / 4.0f, coordinateSize*9.0f);
    float rotateMul[16];
    for(int i=0; i < 4; i++)
        for(int j=0; j < 4; j++)
            rotateMul[i*4+j] = model(j,i);
    glMultMatrixf(rotateMul);
    drawCoordinate(40.0f, 8.0f, 4.0f, 3.0f);
    glColor3f(0, 0.804f, 0.804f);
    drawSphere(20.0f, 20.0f, 20.0f, 5.0f, 30, 30);
    glPopMatrix();
    //[2]

    //[3]三维图形
    m_program->bind();
    glBindVertexArray(VAO);
    useLine = false;

    m_program->setUniformValue(m_program->uniformLocation("projection"), projection);
    m_program->setUniformValue(m_program->uniformLocation("view"), view);
    m_program->setUniformValue(m_program->uniformLocation("model"), model);
    m_program->setUniformValue(m_program->uniformLocation("useLineColor"), useLine);

    /*
    *画叶片
    */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPolygonOffset(1,1);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glDrawElements(GL_TRIANGLES, elementVector.count()*3, GL_UNSIGNED_INT, 0);
    glDisable(GL_POLYGON_OFFSET_FILL);

    /*
    *画网格
    */
    if(gridDisplay)
    {
        useLine = true;
        m_program->setUniformValue(m_program->uniformLocation("useLineColor"), useLine);
        glEnable(GL_BLEND);//开启颜色混合功能
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//则表示源颜色乘以自身的alpha 值，目标颜色乘以1.0减去源颜色的alpha值
        glHint(GL_LINE_SMOOTH,GL_NICEST);//告诉opengl以显示效果为重，速度不重要
        glEnable(GL_LINE_SMOOTH);//线抗锯齿
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//多边形前后填充均为线形式
        glPolygonOffset(-1,-1);//多边形偏移量
        glEnable(GL_POLYGON_OFFSET_LINE);//开启多边形偏移
        glDrawElements(GL_LINES, elementVector.size()*3, GL_UNSIGNED_INT, 0);
        glDisable(GL_POLYGON_OFFSET_LINE);//关闭多边形偏移
    }

    m_program->release();
    //[3]

    m_frame++;
    update();
}

void my_OpenGL::resizeGL(int w, int h)
{
    const qreal retinaScale = devicePixelRatio();
    glViewport (0, 0, (GLsizei) w * retinaScale, (GLsizei) h * retinaScale);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    if (w <= h)
        glOrtho (-coordinateSize, coordinateSize, -coordinateSize * (GLfloat)h / (GLfloat)w,
                 coordinateSize * (GLfloat )h / (GLfloat)w, -coordinateSize*10.0, coordinateSize*10.0);
    else
        glOrtho (-coordinateSize * (GLfloat)w / (GLfloat)h, coordinateSize * (GLfloat)w / (GLfloat)h,
                 -coordinateSize, coordinateSize, -coordinateSize*10.0, coordinateSize*10.0);
    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity () ;
    gluLookAt(0,0,50,0,0,0,0,1,0);

    projection.setToIdentity();
    if(w <= h)
        projection.ortho(-coordinateSize, coordinateSize, -coordinateSize*h/w, coordinateSize*h/w, -coordinateSize*10.0, coordinateSize*10.0);
    else
        projection.ortho(-coordinateSize*w/h, coordinateSize*w/h, -coordinateSize, coordinateSize, -coordinateSize*10.0, coordinateSize*10.0);

}

//按住鼠标左键移动
void my_OpenGL::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        QCursor new_cursor;
        new_cursor.setShape(Qt::SizeAllCursor);
        setCursor(new_cursor);   //改变光标形状为十字形状
        if(firstMouse)
        {
            lastX = event->x();
            lastY = event->y();
            firstMouse = false;
        }
        x_translation = (event->x() - lastX)*mouseMoveSensitivity;
        y_translation = (lastY - event->y())*mouseMoveSensitivity;
        lastX = event->x();
        lastY = event->y();
        view.translate(x_translation / scaleAll_xAndy, y_translation / scaleAll_xAndy, 0);
    }
    if(event->buttons() == Qt::MiddleButton)
    {
        if(!isDragging)
        {
            isDragging = true;
            LastRot = ThisRot;
            m_arcball->click(QPointF(event->x(), event->y()));
        }
        else
        {
            QQuaternion ThisQuat;
            m_arcball->drag(QPointF(event->x(), event->y()), &ThisQuat);
            ThisRot = ThisQuat.toRotationMatrix();
            ThisRot = ThisRot * LastRot;

            model = QMatrix4x4(ThisRot);
        }

    }
}

//点击鼠标右键显示空间坐标
void my_OpenGL::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        makeCurrent();

        GLint viewport[4];
        GLdouble modelview[16];
        GLdouble projection1[16];
        GLfloat winX, winY, winZ = 0.0;
        GLdouble posX, posY, posZ = 0.0;

        GLfloat green = 0.0f;
        GLfloat red = 0.0f;
        GLfloat blue = 0.0f;
        float resultOfRGB;

        QMatrix4x4 mv;
        mv = view * model;

        for(int i = 0; i<4; i++)
            for(int j = 0; j<4; j++)
            {
                modelview[i*4+j] = mv(j,i);
                projection1[i*4+j] = projection(j,i);
            }

        glGetIntegerv(GL_VIEWPORT, viewport);
        winX = (float)event->x();
        winY = (float)viewport[3] - (float)event->y();

        GLenum err = glGetError();

        glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

        gluUnProject(winX, winY, winZ, modelview, projection1, viewport, &posX, &posY, &posZ);

        glReadPixels(winX, winY, 1, 1, GL_GREEN, GL_FLOAT, &green);
        glReadPixels(winX, winY, 1, 1, GL_RED, GL_FLOAT, &red);
        glReadPixels(winX, winY, 1, 1, GL_BLUE, GL_FLOAT, &blue);

        err =  glGetError();

        World_x = posX;
        World_y = posY;
        World_z = posZ;

        doneCurrent();

        if((red == 1.0f) && (blue == 0.0f))
            resultOfRGB = m_iconPara * (1.0f - green / 4.0f);
        else if((green == 1.0f) && (blue == 0.0f))
            resultOfRGB = m_iconPara * (0.5f + red / 4.0f);
        else if((red == 0.0f) && (green == 1.0f))
            resultOfRGB = m_iconPara * (0.5f - blue / 4.0f);
        else if((red == 0.0f) && (blue == 1.0f))
            resultOfRGB = m_iconPara * green / 4.0f;
        else
            resultOfRGB = 0.0f;

        if(m_iconPara == ModelInfo_MaxShift)
            current_Shift = resultOfRGB;
        else if(m_iconPara == ModelInfo_MaxStrain)
            current_Strain = resultOfRGB;
        else if(m_iconPara == ModelInfo_MaxStress)
            current_Stress = resultOfRGB;
        else
            ;

        emit numChanged();
    }
}

//松开按键光标形状恢复原状
void my_OpenGL::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    cursor.setShape(Qt::ArrowCursor);
    setCursor(cursor);
    firstMouse = true;  //旋转操作时，防止发生跳动
    isDragging = false; //拖动停止
}

//滚动滚轮实现缩放
void my_OpenGL::wheelEvent(QWheelEvent *event)
{
    //每滚动一下滚轮event->delta()加减120;
    if(event->delta() >= 0.0)
    {
        scaleNum = (float)(event->delta() / mouseWheelSensitivity);
    }
    else
    {
        scaleNum = (float)(mouseWheelSensitivity / abs(event->delta()));
    }
    scaleAll_xAndy *= scaleNum;
    view.scale(scaleNum, scaleNum, 1);
}

//点击键盘WASD实现移动
void my_OpenGL::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
        view.translate(-keyboardMoveSensitivity * deltaTime /1000.0f, 0, 0);
    if(event->key() == Qt::Key_D)
        view.translate(keyboardMoveSensitivity * deltaTime /1000.0f, 0, 0);
    if(event->key() == Qt::Key_W)
        view.translate(0, keyboardMoveSensitivity * deltaTime /1000.0f, 0);
    if(event->key() == Qt::Key_S)
        view.translate(0, -keyboardMoveSensitivity * deltaTime /1000.0f, 0);
}

//图形平移旋转缩放恢复
void my_OpenGL::initialize_recovery()
{
    view.setToIdentity();
    model.setToIdentity();
    LastRot.setToIdentity();
    ThisRot.setToIdentity();
}

void my_OpenGL::drawCircle(int flag, float position, float radius)
{
    glBegin(GL_TRIANGLE_FAN);//扇形连续填充三角形串
    if(flag == x_axis)
        glVertex3f(position , 0.0f     , 0.0f    );
    else if(flag == y_axis)
        glVertex3f(0.0f     , position , 0.0f    );
    else if(flag == z_axis)
        glVertex3f(0.0f     , 0.0f     , position);
    else
        return;
    int i = 0;
    for (i = 0; i <= 390; i += 15)
    {
        float p = i * 3.14 / 180;
        if(flag == x_axis)
            glVertex3f(position, sin(p) * radius, cos(p)*radius);
        else if(flag == y_axis)
            glVertex3f(sin(p) * radius, position, cos(p)*radius);
        else if(flag == z_axis)
            glVertex3f(sin(p) * radius, cos(p)*radius, position);
        else
            return;
    }
    glEnd();
}

void my_OpenGL::drawCylinder(int flag, float length, float radius)
{
    glBegin(GL_QUAD_STRIP);//连续填充四边形串
    int i = 0;
    for (i = 0; i <= 390; i += 15)
    {
        float p = i * 3.14 / 180;
        if(flag == x_axis)
        {
            glVertex3f(length, sin(p) * radius, cos(p) * radius);
            glVertex3f(0.0f  , sin(p) * radius, cos(p) * radius);
        }
        else if(flag == y_axis)
        {
            glVertex3f(sin(p) * radius, length, cos(p) * radius);
            glVertex3f(sin(p) * radius, 0.0f  , cos(p) * radius);
        }
        else if(flag == z_axis)
        {
            glVertex3f(sin(p) * radius, cos(p) * radius, length);
            glVertex3f(sin(p) * radius, cos(p) * radius, 0.0f  );
        }
        else
            return;
    }
    glEnd();
}

void my_OpenGL::drawCone(int flag, float position, float length, float radius)
{
    glBegin(GL_QUAD_STRIP);//连续填充四边形串
    int i = 0;
    for (i = 0; i <= 390; i += 15)
    {
        float p = i * 3.14 / 180;
        if(flag == x_axis)
        {
            glVertex3f(position + length, 0.0f, 0.0f);
            glVertex3f(position, sin(p) * radius, cos(p) * radius);
        }
        else if(flag == y_axis)
        {
            glVertex3f(0.0f, position + length, 0.0f);
            glVertex3f(sin(p) * radius, position, cos(p) * radius);
        }
        else if(flag == z_axis)
        {
            glVertex3f(0.0f, 0.0f, position + length);
            glVertex3f(sin(p) * radius, cos(p) * radius, position);
        }
        else
            return;
    }
    glEnd();
    drawCircle(flag, position, radius);
}

void my_OpenGL::drawCoordinate(float position, float length, float radius, float ratio)
{
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCylinder(x_axis, position, radius/ratio);
    drawCone(x_axis, position, length, radius);
    glRasterPos3f(position + length + 0.3f, 0.0f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'x');
    glColor3f(0.0f, 1.0f, 0.0f);
    drawCylinder(y_axis, position, radius/ratio);
    drawCone(y_axis, position, length, radius);
    glRasterPos3f(0.0f, position + length + 0.3f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'y');
    glColor3f(0.0f, 0.0f, 1.0f);
    drawCylinder(z_axis, position, radius/ratio);
    drawCone(z_axis, position, length, radius);
    glRasterPos3f(0.0f, 0.0f, position + length + 0.3f);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'z');

    glColor3f(0, 0, 0);
    drawSphere(1.0f, 1.0f, 1.0f, 0.1f, 20, 20);
}

void my_OpenGL::drawSphere(float x_center, float y_center, float z_center, float radius, float M, float N)
{
    float step_z = PI/M;           //z方向每次步进的角度
    float step_xy = 2*PI/N;        //x,y平面每次步进的角度
    float x[4],y[4],z[4];          //用来存坐标

    float angle_z = 0.0;           //起始角度
    float angle_xy = 0.0;
    int i=0, j=0;
    glBegin(GL_QUADS);
    for(i=0; i<M; i++)
    {
        angle_z = i * step_z;      //每次步进step_z
        for(j=0; j<N; j++)
        {
            angle_xy = j * step_xy;//每次步进step_xy
            x[0] = radius * sin(angle_z) * cos(angle_xy);                 //第一个小平面的第一个顶点坐标
            y[0] = radius * sin(angle_z) * sin(angle_xy);
            z[0] = radius * cos(angle_z);

            x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);        //第一个小平面的第二个顶点坐标，下面类似
            y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
            z[1] = radius * cos(angle_z + step_z);

            x[2] = radius*sin(angle_z + step_z)*cos(angle_xy + step_xy);
            y[2] = radius*sin(angle_z + step_z)*sin(angle_xy + step_xy);
            z[2] = radius*cos(angle_z + step_z);

            x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
            y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
            z[3] = radius * cos(angle_z);
            for(int k=0; k<4; k++)
            {
                glVertex3f(x_center+x[k], y_center+y[k],z_center+z[k]);                     //画出这个平面
            }
        }                                                                 //循环画出这一层的平面，组成一个环
    }                                                                     //z轴++，画出剩余层
    glEnd();
}
