#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <vecmath.h>
using namespace std;

// Globals

//CONSTANTS
int MAX_BUFFER_SIZE = 10000;

// This is the list of points (3D vectors)
vector<Vector3f> vecv;

// This is the list of normals (also 3D vectors)
vector<Vector3f> vecn;

// This is the list of faces (indices into vecv and vecn)
vector<vector<unsigned> > vecf;

//Index for the currently selected teapot color
int colorIdx = 0;

//Floats for positioning the light
float lightX = 1.0f;
float lightY = 1.0f;


// You will need more global variables to implement color and position changes


// These are convenience functions which allow us to call OpenGL 
// methods on Vec3d objects
//inline void glVertex(const Vector3f &a) 
//{ glVertex3fv(a); }
//
//inline void glNormal(const Vector3f &a) 
//{ glNormal3fv(a); }


// This function is called whenever a "Normal" key press is received.
void keyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'c':
        // add code to change color here
	colorIdx++;
	if(colorIdx > 3) {
            colorIdx = 0;
	}
	cout << "Color changed. The colorIdx is:" << colorIdx << endl;
        break;
    case 'x': // Escape key
        exit(0);
        break;
    default:
        cout << "Unhandled key press " << key << "." << endl;        
    }

	// this will refresh the screen so that the user sees the color change
    glutPostRedisplay();
}

// This function is called whenever a "Special" key press is received.
// Right now, it's handling the arrow keys.
void specialFunc( int key, int x, int y )
{
    switch ( key )
    {
    case GLUT_KEY_UP:
        // add code to change light position
		lightY = lightY + 0.5f;
		cout << "Unhandled key press: up arrow." << endl;
		break;
    case GLUT_KEY_DOWN:
        // add code to change light position
		lightY = lightY - 0.5f;
		cout << "Unhandled key press: down arrow." << endl;
		break;
    case GLUT_KEY_LEFT:
        // add code to change light position
		lightX = lightX + 0.5f;
		cout << "Unhandled key press: left arrow." << endl;
		break;
    case GLUT_KEY_RIGHT:
        // add code to change light position
		lightX = lightX - 0.5f;
		cout << "Unhandled key press: right arrow." << endl;
		break;
    }

	// this will refresh the screen so that the user sees the light position
    glutPostRedisplay();
}

void drawInput() {
    for(int idx = 0; idx < vecf.size(); idx++) {
        unsigned a, b, c, d, e, f, g, h, i;
        vector<unsigned> face = vecf[idx];
        a = face[0];
        b = face[1];
        c = face[2];
        d = face[3];
        e = face[4];
        f = face[5];
        g = face[6];
        h = face[7];
        i = face[8];

        glBegin(GL_TRIANGLES);
        glNormal3d(vecn[c-1][0], vecn[c-1][1], vecn[c-1][2]);
        glVertex3d(vecv[a-1][0], vecv[a-1][1], vecv[a-1][2]);
        glNormal3d(vecn[f-1][0], vecn[f-1][1], vecn[f-1][2]);
        glVertex3d(vecv[d-1][0], vecv[d-1][1], vecv[d-1][2]);
        glNormal3d(vecn[i-1][0], vecn[i-1][1], vecn[i-1][2]);
        glVertex3d(vecv[g-1][0], vecv[g-1][1], vecv[g-1][2]);
        glEnd();
    }
}

// This function is responsible for displaying the object.
void drawScene(void)
{
    int i;

    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rotate the image
    glMatrixMode( GL_MODELVIEW );  // Current matrix affects objects positions
    glLoadIdentity();              // Initialize to the identity

    // Position the camera at [0,0,5], looking at [0,0,0],
    // with [0,1,0] as the up direction.
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Set material properties of object

	// Here are some colors you might use - feel free to add more
    GLfloat diffColors[4][4] = { {0.5, 0.5, 0.9, 1.0},
                                 {0.9, 0.5, 0.5, 1.0},
                                 {0.5, 0.9, 0.3, 1.0},
                                 {0.3, 0.8, 0.9, 1.0} };
    
	// Here we use the first color entry as the diffuse color
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColors[colorIdx]);

	// Define specular color and shininess
    GLfloat specColor[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess[] = {100.0};

	// Note that the specular color and shininess can stay constant
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  
    // Set light properties

    // Light color (RGBA)
    GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
    // Light position
	GLfloat Lt0pos[] = {lightX, lightY, 5.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
    glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

	// This GLUT method draws a teapot.  You should replace
	// it with code which draws the object you loaded.
	//glutSolidTeapot(1.0);
        drawInput();
    
    // Dump the image to the screen.
    glutSwapBuffers();


}

// Initialize OpenGL's rendering modes
void initRendering()
{
    glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
    glEnable(GL_LIGHTING);     // Enable lighting calculations
    glEnable(GL_LIGHT0);       // Turn on light #0.
}

// Called when the window is resized
// w, h - width and height of the window in pixels.
void reshapeFunc(int w, int h)
{
    // Always use the largest square viewport possible
    if (w > h) {
        glViewport((w - h) / 2, 0, h, h);
    } else {
        glViewport(0, (h - w) / 2, w, w);
    }

    // Set up a perspective view, with square aspect ratio
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 50 degree fov, uniform aspect ratio, near = 1, far = 100
    gluPerspective(50.0, 1.0, 1.0, 100.0);
}

vector<unsigned> faceTripletToVec(string faceTrip) {
    size_t firstSlashPos, secondSlashPos;

    //Get slash positions
    firstSlashPos = faceTrip.find('/');
    secondSlashPos = faceTrip.find('/', firstSlashPos + 1);
    
    //Get split strings
    string vertex = faceTrip.substr(0, firstSlashPos);
    string dunno = faceTrip.substr(
        firstSlashPos + 1,
        secondSlashPos - firstSlashPos - 1
    );
    string normal = faceTrip.substr(
        secondSlashPos + 1,
        string::npos
    );

    //Convert split strings to integers and add to final vector
    vector<unsigned> uVec;
    uVec.push_back(stoul(vertex));
    uVec.push_back(stoul(dunno));
    uVec.push_back(stoul(normal));

    return uVec;
}

vector<unsigned> combineFaceTriples(vector<unsigned> trip1,
        vector<unsigned> trip2, vector<unsigned> trip3) {
    vector<unsigned> v;
    v.push_back(trip1[0]);
    v.push_back(trip1[1]);
    v.push_back(trip1[2]);
    v.push_back(trip2[0]);
    v.push_back(trip2[1]);
    v.push_back(trip2[2]);
    v.push_back(trip3[0]);
    v.push_back(trip3[1]);
    v.push_back(trip3[2]);

    return v;
}

void loadInput()
{
    cout << "Loading input..." << endl;
    //Loop over stdin to get the obj file
    char buffer[MAX_BUFFER_SIZE];
    while(cin.getline(buffer, MAX_BUFFER_SIZE)) {
        stringstream fileLine(buffer);
        string charOne;
        fileLine >> charOne;
	if(charOne == "v") {
	    Vector3f v;
	    fileLine >> v[0] >> v[1] >> v[2];
            vecv.push_back(v);
	} else if(charOne == "vn") {
	    Vector3f v;
	    fileLine >> v[0] >> v[1] >> v[2];
            vecn.push_back(v);
	} else if(charOne == "f") {
            string strabc, strdef, strghi;
            fileLine >> strabc >> strdef >> strghi;

            vector<unsigned> trip1, trip2, trip3;
            trip1 = faceTripletToVec(strabc);
            trip2 = faceTripletToVec(strdef);
            trip3 = faceTripletToVec(strghi);

            vecf.push_back(combineFaceTriples(trip1, trip2, trip3));
	}
    }
    cout << "Vecv size: " << vecv.size() << endl;
    cout << "Vecn size: " << vecn.size() << endl;
    cout << "Vecf size: " << vecf.size() << endl;
}

// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
    loadInput();

    glutInit(&argc,argv);

    // We're going to animate it, so double buffer 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // Initial parameters for window position and size
    glutInitWindowPosition( 60, 60 );
    glutInitWindowSize( 360, 360 );
    glutCreateWindow("Assignment 0");

    // Initialize OpenGL parameters.
    initRendering();

    // Set up callback functions for key presses
    glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
    glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys

     // Set up the callback function for resizing windows
    glutReshapeFunc( reshapeFunc );

    // Call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );

    return 0;	// This line is never reached.
}
