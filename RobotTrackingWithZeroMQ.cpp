#include <GL/glut.h>
#include <math.h>
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>
#include <pthread.h>


int refreshMills = 300;
GLfloat moveDistance = 0.0f;

GLfloat objMov = 0.0f;

GLfloat	angle=0.0;
GLfloat	m_x=1;
GLfloat m_z=1;
GLfloat eye_x=0, eye_y=0, eye_z=0;

GLfloat eye_xx=0.5, eye_yy=-1, eye_zz=-3;


void ground(){

   glBegin(GL_QUADS);
      glColor3f(0.9f, 0.6f, 0.2f);
      glVertex3f( 200.0f, -2.0f,  10.0f);
      glVertex3f(-200.0f, -2.0f,  10.0f);
      glVertex3f(-200.0f, -2.0f, -300.0f);
      glVertex3f( 200.0f, -2.0f, -300.0f);
   glEnd();

}


void rooms(){

   int roomNumbers=3;

   glPushMatrix();

 //  glScalef(1.2,1.2,1.2);
//   glRotatef(20, 1.0f, 1.0f, 0.0f);


   glBegin(GL_QUADS);

    for(int i= 0;i<roomNumbers;i++){
     glColor3f(0.3f, 0.45f, 0.2f);
     glVertex3f( 1.0f + (-2*i), -1.0f, -1.0f);
     glVertex3f(-1.0f + (-2*i) , -1.0f, -1.0f);
     glVertex3f(-1.0f + (-2*i) ,  1.0f, -1.0f);
     glVertex3f( 1.0f + (-2*i) ,  1.0f, -1.0f);
    }

    for(int i= 0;i<(roomNumbers+1);i++){
     glColor3f(0.5f, 0.3f, 0.2f);
     glVertex3f(1.0f + (-2*i),  1.0f,  1.0f);
     glVertex3f(1.0f + (-2*i),  1.0f, -1.0f);
     glVertex3f(1.0f + (-2*i), -1.0f, -1.0f);
     glVertex3f(1.0f + (-2*i), -1.0f,  1.0f);
     }

    for(int i= 0;i<0;i++){

     glColor3f(0.3f, 0.45f, 0.2f);
     glVertex3f( 1.0f + (-2*i), -1.0f, 1.0f);
     glVertex3f(-0.3f + (-2*i), -1.0f, 1.0f);
     glVertex3f(-0.3f + (-2*i),  1.0f, 1.0f);
     glVertex3f( 1.0f + (-2*i),  1.0f, 1.0f);

    }

   glEnd();


 glPopMatrix();

}


void init() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST);

}

void keyboard(GLubyte key, GLint xmouse, GLint ymouse)
{

  switch (key){
  	case 'x':
	 	glRotatef(-angle, 1,0,0);
	//	gluLookAt(0,cos(angle),sin(angle), 0,-cos(angle),-sin(angle), 0,1,0);
		glFlush ( );
		break;
	case 'y':
		glRotatef(angle, 0,1,0);
	//	gluLookAt(cos(angle),0,sin(angle), -cos(angle),0,-sin(angle), 0,1,0);
		glFlush ( );
		break;
	case 'z':// viewer rotates about z-axis
		glRotatef(angle, 0,0,1);
		glFlush ( );
		break;
	case 'r':
		angle+=0.035;
		m_x= sin(angle);
		m_z= -cos(angle);
		glLoadIdentity();
		gluLookAt(eye_x,eye_y,eye_z, eye_x+m_x,eye_y,eye_z+m_z, 0,1,0);
		break;
	case 'l':
		angle-=0.035;
		m_x= sin(angle);
		m_z= -cos(angle);
		glLoadIdentity();
		gluLookAt(eye_x,eye_y,eye_z, eye_x+m_x,eye_y,eye_z+m_z, 0,1,0);
		break;
	case 'f':
		eye_x+=m_x;
		eye_z+=m_z;
		glLoadIdentity();
		gluLookAt(eye_x,eye_y,eye_z, eye_x+m_x,eye_y,eye_z+m_z, 0,1,0);
		break;
	case 'b':
		eye_x-=m_x;
		eye_z-=m_z;
		glLoadIdentity();
		gluLookAt(eye_x,eye_y,eye_z, eye_x+m_x,eye_y,eye_z+m_z, 0,1,0);
		break;

    	case 'm':
        	objMov += 0.2;
		break;
    	case 'n':
        	objMov -= 0.2;
		break;
    	case 's':
        	glLoadIdentity();
		gluLookAt(eye_xx,eye_yy,eye_zz, eye_xx+eye_xx,eye_yy+eye_yy,eye_zz-5, 0,1,0);
		break;
	default: break;
  }

  glutPostRedisplay();

}


void display() {

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
     ground();
   glPopMatrix();

   glPushMatrix();
    glTranslatef(1.5f, 0.0f, -7.0f);
    rooms();
   glPopMatrix();

   glPushMatrix();
    glColor3f(0.3f, 0.55f, 0.5f);
  //  glTranslatef(0.5f+objMov, -1.0f, -5.0f);
    glTranslatef(0.5f, -1.0f, -5.0f-objMov);
    glutSolidCube(0.3);
   glPopMatrix();

   glutSwapBuffers();

}


void reshape(GLsizei width, GLsizei height) {

   if (height == 0) height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluLookAt(eye_x, eye_y, eye_z,  eye_x, eye_y, eye_z,  0,1,0);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(100.0, 1.4, 1, 500.0);

   glViewport(0, 0, width, height);

}

zmq::context_t context (1);
zmq::socket_t socket (context, ZMQ_REP);

void *tt(void *argument){


     std::cout << "out loop" << std::endl;

    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        socket.recv (&request);
        std::cout << "Received robot" << std::endl;
 
	#ifndef _WIN32
    	   sleep(1);
	#else
	   Sleep (1);
	#endif

        zmq::message_t reply (5);
        memcpy ((void *) reply.data (), "robot", 5);
        socket.send (reply);
    }

}

void *task(void *argument){
      char* msg;
      msg = (char*)argument;
      std::cout<<msg<<std::endl;
}

float prevValue=0;

void timer(int value) {

  // objMov += 0.2;

   zmq::message_t request;

   socket.recv (&request);

   std::cout << request << std::endl;

   std::string rpl = std::string(static_cast<char*>(request.data()), request.size());
   std::cout <<"Sout : " << rpl << std::endl;

   float diff = atof(rpl.c_str()) - prevValue;
  
   objMov += diff;

  // objMov += atof(rpl.c_str());
   
   prevValue = atof(rpl.c_str());;


  // sleep(1);

   zmq::message_t reply (5);
   memcpy ((void *) reply.data (), "Arr", 5);
   socket.send (reply);

   glutPostRedisplay();
   glutTimerFunc(refreshMills, timer, 0);

}


int main(int argc, char** argv) {

   glutInit(&argc, argv);

   socket.bind ("tcp://*:5555");

   glutInitDisplayMode(GLUT_DOUBLE);
   glutInitWindowSize(900, 600);
   glutInitWindowPosition(150, 150);
   glutCreateWindow("Comp");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutTimerFunc(0, timer, 0);
   glutMainLoop();


   return 0;
}
