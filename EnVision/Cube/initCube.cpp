#include "initCube.h"
#include "Base/envision.h"

#include <QMouseEvent>
#include <math.h>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
GLWidget_cube::GLWidget_cube(EnVision *main, Ui::EnVision_cubeUI* ui_cube, QWidget *parent) : QOpenGLWidget(parent),
texture01(0), texture02(0), angularSpeed(0), mousePressPosition(0, 0)
{
		this->main = main;

		//obsolet?
		this->ui_cube = ui_cube;
		//


		guiAccess();

		QSurfaceFormat format;
		format.setDepthBufferSize(24);
		QSurfaceFormat::setDefaultFormat(format);

		qface01 = QImage(10, 10, QImage::Format_Grayscale8);
		face02 = QImage(1, 1, QImage::Format_Grayscale8);
		face03 = QImage(1, 1, QImage::Format_Grayscale8);
		face04 = QImage(1, 1, QImage::Format_Grayscale8);
		face05 = QImage(1, 1, QImage::Format_Grayscale8);
		face06 = QImage(1, 1, QImage::Format_Grayscale8);

		memset(textures, 0, sizeof(textures));

		QObject::connect(ui_cube->hScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)), Qt::UniqueConnection);
		QObject::connect(ui_cube->vScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)), Qt::UniqueConnection);
}


//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
GLWidget_cube::~GLWidget_cube()
{
		// Make sure the context is current when deleting the texture
		// and the buffers.
		makeCurrent();
		delete texture01;
		delete texture02;
		//delete geometries;

		for (int i = 0; i < 6; ++i)
			delete textures[i];
		delete program;

		doneCurrent();
}

//==============================================================================
// void GLWidget_cube::guiAccess()
//------------------------------------------------------------------------------
//==============================================================================
void GLWidget_cube::guiAccess()
{
		this->ui_base = main->getBaseUI();
		this->ui_plot = main->getPlotUI();
		this->ui_cube = main->getCubeUI();
		this->ui_image = main->getImageUI();

	return;
}


//==============================================================================
// void GLWidget_cube::initializeGL()
//------------------------------------------------------------------------------
//==============================================================================
void GLWidget_cube::initializeGL()
{
		initializeOpenGLFunctions();

		glClearColor(0, 0, 0, 1);

		int shaders = initShaders();
		initTextures();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		makeObject();

		// Use QBasicTimer because its faster than QTimer
		timer.start(12, this);

		xPos = this->width() / 2;
		yPos = this->height() / 2;

		if (shaders > -1){
			initOk = 1;

			installEventFilter(this);
			setMouseTracking(true);
		}
	return;
}

void GLWidget_cube::makeObject()
{
		static const int coords[6][4][3] = {
			{ { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
			{ { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
			{ { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
			{ { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
			{ { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
			{ { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
		};


		QVector<GLfloat> vertData;
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 4; ++j) {
				// vertex position
				vertData.append(0.2 * coords[i][j][0]);
				vertData.append(0.2 * coords[i][j][1]);
				vertData.append(0.2 * coords[i][j][2]);
				// texture coordinate
				vertData.append(j == 0 || j == 3);
				vertData.append(j == 0 || j == 1);
			}
		}

		vbo.create();
		vbo.bind();
		vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
	return;
}


//==============================================================================
// void GLWidget_cube::initShaders()
//------------------------------------------------------------------------------
//==============================================================================
int GLWidget_cube::initShaders()
{
		// Compile vertex shader
		/*
		if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl")){
			close();
			return -1;
		}
		
		// Compile fragment shader
		if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl")){
			close();
			return -1;
		}

		// Link shader pipeline
		if (!program.link()){
			close();
			return -1;
		}

		// Bind shader pipeline for use
		if (!program.bind()){
			close();
			return -1;
		}
		*/

		QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
		const char *vsrc =
			"attribute highp vec4 vertex;\n"
			"attribute mediump vec4 texCoord;\n"
			"varying mediump vec4 texc;\n"
			"uniform mediump mat4 matrix;\n"
			"void main(void)\n"
			"{\n"
			"    gl_Position = matrix * vertex;\n"
			"    texc = texCoord;\n"
			"}\n";
		vshader->compileSourceCode(vsrc);

		QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
		const char *fsrc =
			"uniform sampler2D texture;\n"
			"varying mediump vec4 texc;\n"
			"void main(void)\n"
			"{\n"
			"    gl_FragColor = texture2D(texture, texc.st);\n"
			"}\n";
		fshader->compileSourceCode(fsrc);

		program = new QOpenGLShaderProgram;
		program->addShader(vshader);
		program->addShader(fshader);
		program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
		program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
		program->link();

		program->bind();
		program->setUniformValue("texture", 0);
	return 0;
}

//==============================================================================
// void GLWidget_cube::initTextures()
//------------------------------------------------------------------------------
//==============================================================================
void GLWidget_cube::initTextures()
{
		// load image
		
		texture01 = new QOpenGLTexture(QImage(qface01).mirrored());

		// Set nearest filtering mode for texture minification
		texture01->setMinificationFilter(QOpenGLTexture::NearestMipMapLinear);

		// Set bilinear filtering mode for texture magnification
		texture01->setMagnificationFilter(QOpenGLTexture::NearestMipMapLinear);

		// Wrap texture coordinates by repeating
		// f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
		texture01->setWrapMode(QOpenGLTexture::ClampToEdge);

		textures[0] = texture01;
		
		// load image
		texture02 = new QOpenGLTexture(QImage(qface01).mirrored());

		// Set nearest filtering mode for texture minification
		texture02->setMinificationFilter(QOpenGLTexture::NearestMipMapLinear);

		// Set bilinear filtering mode for texture magnification
		texture02->setMagnificationFilter(QOpenGLTexture::NearestMipMapLinear);

		// Wrap texture coordinates by repeating
		// f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
		texture02->setWrapMode(QOpenGLTexture::ClampToEdge);

		textures[1] = texture01;
		textures[2] = texture01;
		textures[3] = texture01;
		textures[4] = texture01;
		textures[5] = texture01;
	return;
}

//==============================================================================
// void GLWidget_cube::loadTextures()
//------------------------------------------------------------------------------
//==============================================================================
void GLWidget_cube::loadTextures()
{
		qface01 = ImageAttribute::Record[0].qface01;
		//cout << qface01.width() << " " << qface01.height() << endl;
		//face02 = QImage(":/cubetest.png");
		//cout << face02.width() << " " << face02.height() << endl;
		//face03;
		//face04;
		//face05;
		//face06;
		
		//!fac0x.isNull()
		
		/*
		if (!qface01.isNull() ){
			texture01->destroy();
			texture01->setData(QImage(qface01)); //LinearMipMapLinear
		}
		*/
	return;
}

//==============================================================================
// void GLWidget_cube::paintGL()
//------------------------------------------------------------------------------
//==============================================================================
void GLWidget_cube::paintGL()
{
		// Clear color and depth buffer
		/*
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		texture01->bind();

		// Calculate model view transformation
		QMatrix4x4 matrix;
		matrix.translate(-1 * (hScroll + xPos - this->width() / 2) / 20,  (vScroll + yPos - this->height() / 2) / 20, -29.0);
		matrix.rotate(rotation);
		matrix.scale(zPos * 20, zPos * 1, zPos * 1);

		// Set modelview-projection matrix
		program->setUniformValue("mvp_matrix", projection * matrix);

		// Use texture unit 0 which contains cube.png
		program->setUniformValue("texture01", 0);

		// Draw cube geometry
		//geometries->drawCubeGeometry(program);
		*/


	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		QMatrix4x4 matrix;
		matrix.ortho(-0.5f, +0.5f, +0.5f, -0.5f, 4.0f, 15.0f);
		matrix.translate(0.0f, 0.0f, -10.0f);
		matrix.rotate(rotation);
		matrix.scale(zPos * 20, zPos * 1, zPos * 1);

		program->setUniformValue("matrix", matrix);
		program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
		program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
		program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
		program->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

		for (int i = 0; i < 6; ++i) {
			textures[i]->bind();
			glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
		}

	return;
}

//==============================================================================
// void GLWidget_cube::resizeGL(int w, int h)
//------------------------------------------------------------------------------
//============================================================================== [5]
void GLWidget_cube::resizeGL(int w, int h)
{
		// Calculate aspect ratio
		qreal aspect = qreal(w) / qreal(h ? h : 1);

		// Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
		const qreal zNear = 1.0, zFar = 100.0, fov = 45.0;

		// Reset projection
		projection.setToIdentity();

		// Set perspective projection
		projection.perspective(fov, aspect, zNear, zFar);
	return;
}
