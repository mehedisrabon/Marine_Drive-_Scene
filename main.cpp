#include <windows.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


using namespace std;
float busX = -0.0f;
float wheelAngle = 0.0f;
float wheelSpeed = 5.0f; // Faster rotation
float riverTime = 0.0f;
float waveTime = 0.0f;
float waveYOffset = 0.0f;  // This offset moves waves up and down
int currentScene = 0;
const float cloudSpacing = 300.0f;
const int totalClouds = 4;
float cloudBaseOffsetX = 0.0f;
float cloudSpeed =0.5f;
float birdX = 1000.0f;   // Start from right
float birdY = 550.0f;
float birdOffsetX = 0.0f;
float wingFlap = 0.0f;
bool wingUp = true;
float carX = 1000.0f; // Start from right side
float carAngle = 0.0f;
float greenCarX = -600.0f;         // Green car starts from the left
float greenCarWheelAngle = 0.0f;   // Green car wheel rotation
float carSpeed = 2.0f;  // Default car speed, will be modified with keypress


// Sun Variables
float sunX = 508.5f, sunY = 500.0f;
float targetSunX = 506.17f, targetSunY = 287.03f;
float sunAlpha = 1.0f;
bool sunShouldSet = false;  // New flag to control sunset
bool sunVisible = false;
//  Night Transition Flags
bool transitioningToNight = false;
bool nightScene = false;

// Moon Variables
bool moonVisible = false;
float moonAlpha = 0.0f;
float moonRadius = 40.01f;
float moonX = 514.53f, moonY = 560.0f; // Adjusted for visible space
float waveOffset = 0.0f;
bool waveDirectionRight = true;
bool birdActive = true;

const int NUM_RainADROPSA = 300;
float RainAX[NUM_RainADROPSA];
float RainAY[NUM_RainADROPSA];
bool rainActive = false;


struct RGB {
    float r, g, b;
};

RGB carColors[] = {
    {0.0f, 1.0f, 0.0f},  // Green
    {1.0f, 1.0f, 0.0f},  // Yellow
    {1.0f, 1.0f, 1.0f},  // White
    {0.0f, 0.5f, 1.0f},  // Light Blue
    {1.0f, 0.0f, 0.0f},  // Red
    {1.0f, 0.5f, 0.0f},  // Orange
    {0.6f, 0.0f, 1.0f},  // Purple
};
RGB reversedCarColors[] = {
    {0.6f, 0.2f, 1.0f},  // Purple
    {1.0f, 0.5f, 0.0f},  // Orange
    {1.0f, 1.0f, 0.0f},  // Yellow
    {0.0f, 0.0f, 1.0f},  // Blue
    {0.0f, 1.0f, 0.0f},  // Green
    {1.0f, 0.0f, 0.0f}   // Red
};

int currentCarColorIndex = 0;
const int totalCarColors = sizeof(carColors) / sizeof(carColors[0]);
int totalRightCarColors = sizeof(reversedCarColors) / sizeof(reversedCarColors[0]);
int currentRightCarColorIndex = 0;

void Mountain() {
    glColor3f(0.1647f, 0.651f, 0.376f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 420);
    glVertex2f(63.167576f, 459.29944f);
    glVertex2f(90.24429f, 467.84998f);
    glVertex2f(97.36974f, 467.84998f);
    glVertex2f(109.00797f, 467.61246f);
    glVertex2f(132.52196f, 460.48701f);
    glVertex2f(305.84545f, 366.79953f);
    glVertex2f(330.37374f, 354.15966f);
    glVertex2f(0,280);
    glVertex2f(327.3969732934661, 280);
    glVertex2f(330.37374f, 354.15966f);
    glVertex2f(376.59126f, 331.05090f);
    glVertex2f(420.57244f, 305.70582f);
    glVertex2f(453.74469f, 292.28783f);
    glVertex2f(472.75350f, 289.30605f);
    glVertex2f(495.48954f, 287.81517f);
    glVertex2f(533.4273298117228, 280);
    glVertex2f(327.3969732934661, 280);
    glVertex2f(420, 280);
    glVertex2f(515.61652, 288.18789);
    glVertex2f(533.4273298117228, 280);
    glEnd();
    glColor3f(0.1647f, 0.651f, 0.376f);
    glBegin(GL_POLYGON);
    glVertex2f(1000, 280);
    glVertex2f(633.1143738147599, 280);
    glVertex2f(533.4273298117228, 280);
    glVertex2f(515.61652, 288.18789);
    glVertex2f(530.1526771907593, 290.0515023851177);
    glVertex2f(565.9339782734854, 298.2513838832424);
    glVertex2f(637.1238585526593, 332.5417974208549);
    glVertex2f(791.0579975856373, 419.0132750374429);
    glVertex2f(823.9539302919059, 431.7646144905122);
    glVertex2f(834.59169f, 433.31595f);
    glVertex2f(849.21863f, 432.65109f);
    glVertex2f(875.36981f, 426.00248f);
    glVertex2f(914.59658f, 406.05667f);
    glVertex2f(925.23435f, 400.73778f);
    glVertex2f(931.66134f, 399.40806f);
    glVertex2f(938.08832f, 403.17560f);
    glVertex2f(950.05582f, 409.60259f);
    glVertex2f(967.12057f, 414.92147f);
    glVertex2f(980.19616f, 417.13768f);
    glVertex2f(1000, 414.03499f);
    glVertex2f(1000,280);
    glEnd();

  /*	glColor3ub(0, 150, 60);
    glBegin(GL_POLYGON);
      glVertex2f(90.2442903517034, 467.8499829270577);
     glVertex2f (97.3697413653854, 467.8499829270577);
      glVertex2f(109.0079780210659, 467.6124678932683);
      glVertex2f(132.5219663662164, 460.4870168795863);
     glVertex2f (305.8454582295434, 366.799536924656);
      glVertex2f(330.3737461455385, 354.1596668250019);
     glVertex2f (376.5912600440598, 331.0509098757413);
     glVertex2f (420.5724426249106, 305.7058216088104);
     glVertex2f (453.7446905036879, 292.2878337027881);
     glVertex2f (472.7535067038862, 289.3060586125609);
     glVertex2f (471.2579116713661, 279.0038384541085);
     glVertex2f (390.2087485959825, 294.6881336396401);
     glVertex2f (291.7183438886094, 324.0362845372906);
     glVertex2f (179.8201707872603, 388.3496340168639);
      glVertex2f(97.4044643068156, 442.2161088406819);
    glVertex2f  (89.7016233800942, 457.6215446340611);
    glVertex2f  (90.2442903517034, 467.8499829270577);
        glEnd();*/
}

void Ground() {
    glColor3ub(75, 200, 66);
    glBegin(GL_POLYGON);
    glVertex2f(1000, 0);//right
    glVertex2f(363.5773562996234, 0);//
    glVertex2f(569.117351837075, 86.5063829913481);
    glVertex2f(680.6093381246999, 146.7344532193056);
    glVertex2f(680.2156414076825, 162.5775669007505);//o1

    //glVertex2f(668.8757241491846, 174.6049186971978);//p1
    glVertex2f(648.8601861009611, 185.9650889407841);
    glVertex2f(550, 200);
    glVertex2f(478.4067575266481, 212.5854415141057);
    glVertex2f(480, 220);
    glVertex2f(500.953021648243, 226.3515975058789);
    glVertex2f(595.8235781374299, 249.4698670782187);
    glVertex2f(600.721309269282, 253.3396232763075);
    glVertex2f(598.0023606043301, 257.4180462737352);
    glVertex2f(588.4602562653189, 260.8318914314699);
    glVertex2f(533.4273298117228, 280);
    glVertex2f(1000, 280);
    glVertex2f(1000, 0);
    glEnd();


        /* glColor3ub(40, 120, 30);  // Darker green shade
    glBegin(GL_POLYGON);
    glVertex2f(503, 0);
    glVertex2f(598.1813602828379, 24.1232676242069);
    glVertex2f(692.5063824518793, 44.2045959076119);
    glVertex2f(821.1145164146965, 65.1829437677592);
    glVertex2f(848.4484745239662, 68.6144796342908);
    glVertex2f(893.2600111695475, 72.9120285607139);
    glVertex2f(1000, 76);
    glVertex2f(1000, 81);
    glVertex2f(972.1281242620574, 81.0285332204246);
    glVertex2f(891.7170778739836, 76.1643489398607);
    glVertex2f(820, 70);
    glVertex2f(722.6469372026964, 53.1551123453436);
    glVertex2f(666.6066355934564, 42.8071429834458);
    glVertex2f(565.2270714076178, 21.4943609663366);
    glVertex2f(480, 0);

        glEnd();
*/




    glColor3ub(75, 200, 66);
    glBegin(GL_POLYGON);
    glVertex2f(0, 213.0991406328661);
    glVertex2f(110.5519061818434, 230.171450760773);
    glVertex2f(185.1507693791696, 236.0123229204891);
    glVertex2f(220, 240);
    glVertex2f(225.3787385047249, 241.9923681836032);
    glVertex2f(223.597641200289, 244.7753327217843);
    glVertex2f(220.1467651729445, 246.6677486077474);
    glVertex2f(210, 250);
    glVertex2f(193.0963498618248, 255.239279385345);
    glVertex2f(130.752984185261, 274.417205239888);
    glVertex2f(116.9342392169839, 276.2384526071635);
    glVertex2f(94.5251167645594, 280);
    glVertex2f(55.0987578974713, 280);
    glVertex2f(16.0828408032757, 279.6467731054893);
    glVertex2f(0, 280);
    glEnd();
       glColor3ub(75, 200, 66);
    glBegin(GL_POLYGON);
     glVertex2f(0, 213.0991406328661);
     glVertex2f(0, 200);
    glVertex2f (111.7408391524158, 221.1637000231627);
     glVertex2f(187.0537644157997, 229.6919210831224);
     glVertex2f(222.2952057793262, 236.2206924196439);
     glVertex2f(229.1570082407906, 239.0225407844125);
     glVertex2f(231.0887950547965, 240.3293377468282);
     glVertex2f(229.327460018497, 242.9429316716598);
   glVertex2f (223.597641200289, 244.7753327217843);
    glVertex2f (225.3787385047249, 241.9923681836032);
    glVertex2f (220, 240);
     glVertex2f(185.1507693791696, 236.0123229204891);
     glVertex2f(110.5519061818434, 230.171450760773);
    glVertex2f (0, 200);
        glEnd();






}


void tree()
{

               	glColor3ub(160, 120, 60);

                glBegin(GL_QUADS);
                glVertex2f(832.9275319618605, 147);
                glVertex2f (851.3954851235526, 147);
                glVertex2f (851.3954851235526, 83.2713980807956);
                glVertex2f (832.9275319618605,83.2713980807956);
                glEnd();


                    glColor3ub(0, 120, 0);
                    glBegin(GL_TRIANGLES);
                    glVertex2f      (808.163459110026, 147);
                    glVertex2f  (843.9090672475985, 232);
                    glVertex2f (871.0550624401175, 147);
                     glEnd();




                    glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(862.9275, 147);
            glVertex2f(881.3955, 147);
            glVertex2f(881.3955, 83.2714);
            glVertex2f(862.9275, 83.2714);
            glEnd();


               glColor3ub(0, 120, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(838.1635, 147);
            glVertex2f(873.9091, 232);
            glVertex2f(901.0551, 147);
            glEnd();


                glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(802.9275, 147);
            glVertex2f(821.3955, 147);
            glVertex2f(821.3955, 83.2714);
            glVertex2f(802.9275, 83.2714);
            glEnd();


              glColor3ub(0, 120, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(778.1635, 147);
            glVertex2f(813.9091, 232);
            glVertex2f(841.0551, 147);
            glEnd();



            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(712.9275, 147);
            glVertex2f(731.3955, 147);
            glVertex2f(731.3955, 83.2714);
            glVertex2f(712.9275, 83.2714);
            glEnd();


            glColor3ub(0, 120, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(688.1635, 147);
            glVertex2f(723.9091, 232);
            glVertex2f(751.0551, 147);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(742.9275, 147);
            glVertex2f(761.3955, 147);
            glVertex2f(761.3955, 83.2714);
            glVertex2f(742.9275, 83.2714);
            glEnd();


            glColor3ub(0, 120, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(718.1635, 147);
            glVertex2f(753.9091, 232);
            glVertex2f(781.0551, 147);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(922.9275, 147);
            glVertex2f(941.3955, 147);
            glVertex2f(941.3955, 83.2714);
            glVertex2f(922.9275, 83.2714);
            glEnd();



            glColor3ub(0, 120, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(898.1635, 147);
            glVertex2f(933.9091, 232);
            glVertex2f(961.0551, 147);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(952.9275, 147);
            glVertex2f(971.3955, 147);
            glVertex2f(971.3955, 83.2714);
            glVertex2f(952.9275, 83.2714);
            glEnd();


            glColor3ub(0, 120, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(928.1635, 147);
            glVertex2f(963.9091, 232);
            glVertex2f(991.0551, 147);
            glEnd();

            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(832.9275, 177);
            glVertex2f(851.3955, 177);
            glVertex2f(851.3955, 113.2714);
            glVertex2f(832.9275, 113.2714);
            glEnd();


            glColor3ub(0, 120, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(808.1635, 177);
            glVertex2f(843.9091, 262);
            glVertex2f(871.0551, 177);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(832.9275, 117);
            glVertex2f(851.3955, 117);
            glVertex2f(851.3955, 53.2714);
            glVertex2f(832.9275, 53.2714);
            glEnd();


            glColor3ub(0, 130, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(808.1635, 117);
            glVertex2f(843.9091, 202);
            glVertex2f(871.0551, 117);
            glEnd();

            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(862.9275, 117);
            glVertex2f(881.3955, 117);
            glVertex2f(881.3955, 53.2714);
            glVertex2f(862.9275, 53.2714);
            glEnd();


            glColor3ub(0, 130, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(838.1635, 117);
            glVertex2f(873.9091, 202);
            glVertex2f(901.0551, 117);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(802.9275, 117);
            glVertex2f(821.3955, 117);
            glVertex2f(821.3955, 53.2714);
            glVertex2f(802.9275, 53.2714);
            glEnd();


            glColor3ub(0, 130, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(778.1635, 117);
            glVertex2f(813.9091, 202);
            glVertex2f(841.0551, 117);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(922.9275, 117);
            glVertex2f(941.3955, 117);
            glVertex2f(941.3955, 53.2714);
            glVertex2f(922.9275, 53.2714);
            glEnd();


            glColor3ub(0, 130, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(898.1635, 117);
            glVertex2f(933.9091, 202);
            glVertex2f(961.0551, 117);
            glEnd();

            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(742.9275, 117);
            glVertex2f(761.3955, 117);
            glVertex2f(761.3955, 53.2714);
            glVertex2f(742.9275, 53.2714);
            glEnd();


            glColor3ub(0, 130, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(718.1635, 117);
            glVertex2f(753.9091, 202);
            glVertex2f(781.0551, 117);
            glEnd();



            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(952.9275, 117);
            glVertex2f(971.3955, 117);
            glVertex2f(971.3955, 53.2714);
            glVertex2f(952.9275, 53.2714);
            glEnd();


            glColor3ub(0, 130, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(928.1635, 117);
            glVertex2f(963.9091, 202);
            glVertex2f(991.0551, 117);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(712.9275, 117);
            glVertex2f(731.3955, 117);
            glVertex2f(731.3955, 53.2714);
            glVertex2f(712.9275, 53.2714);
            glEnd();


            glColor3ub(0, 130, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(688.1635, 117);
            glVertex2f(723.9091, 202);
            glVertex2f(751.0551, 117);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(632.9275, 117);
            glVertex2f(651.3955, 117);
            glVertex2f(651.3955, 53.2714);
            glVertex2f(632.9275, 53.2714);
            glEnd();


            glColor3ub(0, 130, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(608.1635, 117);
            glVertex2f(643.9091, 202);
            glVertex2f(671.0551, 117);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(662.9275, 62);
            glVertex2f(681.3955, 62);
            glVertex2f(681.3955, -1.7286);
            glVertex2f(662.9275, -1.7286);
            glEnd();


            glColor3ub(0, 150, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(638.1635, 62);
            glVertex2f(673.9091, 147);
            glVertex2f(701.0551, 62);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(512.9275, 62);
            glVertex2f(531.3955, 62);
            glVertex2f(531.3955, -1.7286);
            glVertex2f(512.9275, -1.7286);
            glEnd();

            glColor3ub(0, 110, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(488.1635, 62);
            glVertex2f(523.9091, 147);
            glVertex2f(551.0551, 62);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(542.9275, 62);
            glVertex2f(561.3955, 62);
            glVertex2f(561.3955, -1.7286);
            glVertex2f(542.9275, -1.7286);
            glEnd();

            glColor3ub(0, 115, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(518.1635, 62);
            glVertex2f(553.9091, 147);
            glVertex2f(581.0551, 62);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(572.9275, 62);
            glVertex2f(591.3955, 62);
            glVertex2f(591.3955, -1.7286);
            glVertex2f(572.9275, -1.7286);
            glEnd();

            glColor3ub(0, 140, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(548.1635, 62);
            glVertex2f(583.9091, 147);
            glVertex2f(611.0551, 62);
            glEnd();

            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(602.9275, 62);
            glVertex2f(621.3955, 62);
            glVertex2f(621.3955, -1.7286);
            glVertex2f(602.9275, -1.7286);
            glEnd();

            glColor3ub(0, 150, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(578.1635, 62);
            glVertex2f(613.9091, 147);
            glVertex2f(641.0551, 62);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(662.9275, 62);
            glVertex2f(681.3955, 62);
            glVertex2f(681.3955, -1.7286);
            glVertex2f(662.9275, -1.7286);
            glEnd();

            glColor3ub(0, 110, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(638.1635, 62);
            glVertex2f(673.9091, 147);
            glVertex2f(701.0551, 62);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(692.9275, 62);
            glVertex2f(711.3955, 62);
            glVertex2f(711.3955, -1.7286);
            glVertex2f(692.9275, -1.7286);
            glEnd();

            glColor3ub(0, 115, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(668.1635, 62);
            glVertex2f(703.9091, 147);
            glVertex2f(731.0551, 62);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(722.9275, 62);
            glVertex2f(741.3955, 62);
            glVertex2f(741.3955, -1.7286);
            glVertex2f(722.9275, -1.7286);
            glEnd();

            glColor3ub(0, 120, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(698.1635, 62);
            glVertex2f(733.9091, 147);
            glVertex2f(761.0551, 62);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(752.9275, 62);
            glVertex2f(771.3955, 62);
            glVertex2f(771.3955, -1.7286);
            glVertex2f(752.9275, -1.7286);
            glEnd();

            glColor3ub(0, 105, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(728.1635, 62);
            glVertex2f(763.9091, 147);
            glVertex2f(791.0551, 62);
            glEnd();

            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(782.9275, 62);
            glVertex2f(801.3955, 62);
            glVertex2f(801.3955, -1.7286);
            glVertex2f(782.9275, -1.7286);
            glEnd();

            glColor3ub(0, 100, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(758.1635, 62);
            glVertex2f(793.9091, 147);
            glVertex2f(821.0551, 62);
            glEnd();



            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(842.9275, 62);
            glVertex2f(861.3955, 62);
            glVertex2f(861.3955, -1.7286);
            glVertex2f(842.9275, -1.7286);
            glEnd();

            glColor3ub(0, 120, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(818.1635, 62);
            glVertex2f(853.9091, 147);
            glVertex2f(881.0551, 62);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(842.9275, 62);
            glVertex2f(861.3955, 62);
            glVertex2f(861.3955, -1.7286);
            glVertex2f(842.9275, -1.7286);
            glEnd();

            glColor3ub(0, 100, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(818.1635, 62);
            glVertex2f(853.9091, 147);
            glVertex2f(881.0551, 62);
            glEnd();



            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(872.9275, 62);
            glVertex2f(891.3955, 62);
            glVertex2f(891.3955, -1.7286);
            glVertex2f(872.9275, -1.7286);
            glEnd();

            glColor3ub(0, 120, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(848.1635, 62);
            glVertex2f(883.9091, 147);
            glVertex2f(911.0551, 62);
            glEnd();


            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(902.9275, 62);
            glVertex2f(921.3955, 62);
            glVertex2f(921.3955, -1.7286);
            glVertex2f(902.9275, -1.7286);
            glEnd();

            glColor3ub(0, 100, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(878.1635, 62);
            glVertex2f(913.9091, 147);
            glVertex2f(941.0551, 62);
            glEnd();

            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(962.9275, 62);
            glVertex2f(981.3955, 62);
            glVertex2f(981.3955, -1.7286);
            glVertex2f(962.9275, -1.7286);
            glEnd();


            glColor3ub(0, 100, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(938.1635, 62);
            glVertex2f(973.9091, 147);
            glVertex2f(1001.0551, 62);
            glEnd();



            glColor3ub(160, 120, 60);
            glBegin(GL_QUADS);
            glVertex2f(932.9275, 62);
            glVertex2f(951.3955, 62);
            glVertex2f(951.3955, -1.7286);
            glVertex2f(932.9275, -1.7286);
            glEnd();

            glColor3ub(0, 110, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(908.1635, 62);
            glVertex2f(943.9091, 147);
            glVertex2f(971.0551, 62);
            glEnd();

            }

            void initializeRainDrops() {
                for (int i = 0; i < NUM_RainADROPSA; i++) {
                    RainAX[i] = rand() % 1280;
                    RainAY[i] = rand() % 720;
                }
            }
            void RainMehedi() {
                glColor3f(0.6f, 0.6f, 0.8f);
                glBegin(GL_LINES);
                for (int i = 0; i < NUM_RainADROPSA; i++) {
                    glVertex2f(RainAX[i], RainAY[i]);
                    glVertex2f(RainAX[i] - 2.0f, RainAY[i] - 10.0f);
                }
                glEnd();
            }



            void updateRain(int value) {
                if (rainActive) {
                    for (int i = 0; i < NUM_RainADROPSA; i++) {
                        RainAY[i] -= 9.0f;
                        RainAX[i] -= 2.5f;
                        if (RainAY[i] < 0 || RainAX[i] < 0) {
                            RainAX[i] = rand() % 1280 + 100;
                            RainAY[i] = 720 + rand() % 100;
                        }
                    }
                    glutPostRedisplay();
                    glutTimerFunc(20, updateRain, 0);
                }
            }


            void bridge() {
                glColor3ub(0,0,0);
                glBegin(GL_POLYGON);
                glVertex2f(0, 376);
                glVertex2f(1000, 376);
                glVertex2f(1000, 379);
                glVertex2f(0, 379);
                glEnd();

                glColor3ub(48, 70, 82);
                glBegin(GL_POLYGON);
                glVertex2f(0, 376);
                glVertex2f(1000, 376);
                glVertex2f(1000, 350);
                glVertex2f(0,350);
                glEnd();

                glColor3ub(48, 70, 82);
                glBegin(GL_POLYGON);
                glVertex2f(0, 350);
                glVertex2f(1000, 350);
                glVertex2f(1000, 347);
                glVertex2f(0,347);
                glEnd();

                glColor3ub(0,0,0);
                glBegin(GL_POLYGON);
                glVertex2f(0, 347);
                glVertex2f(1000, 347);
                glVertex2f(1000, 339);
                glVertex2f(0, 339);
                glEnd();

                glColor3ub(254, 242, 205);
                glBegin(GL_POLYGON);
                glVertex2f(0, 339);
                glVertex2f(1000,339);
                glVertex2f(1000, 335);
                glVertex2f(0, 335);
                glEnd();
}

void River() {
    glColor3ub(0, 115, 174);
    glBegin(GL_POLYGON);
    glVertex2f(231.0887950547965, 240.3293377468282);
    glVertex2f(230.670581999137, 241.9500361607316);
    glVertex2f(229.327460018497, 242.9429316716598);
    glVertex2f(226.4128556384091, 244.4942251698278);
    glVertex2f(221.431507757196, 246.4599299971225);
    glVertex2f(210, 250);
    glVertex2f(193.0963498618248, 255.239279385345);
    glVertex2f(130.752984185261, 274.417205239888);
    glVertex2f(116.9342392169839, 276.2384526071635);
    glVertex2f(112.9922373112199, 280);
    glVertex2f(327.3969732934661, 280);
    glVertex2f(420, 280);
    glVertex2f(533.4273298117228, 280);
    glVertex2f(588.4602562653189, 260.8318914314699);
    glVertex2f(598.0023606043301, 257.4180462737352);
    glVertex2f(600.721309269282, 253.3396232763075);
    glVertex2f(595.8235781374299, 249.4698670782187);
    glVertex2f(500.953021648243, 226.3515975058789);
    glVertex2f(480, 220);
    glVertex2f(478.4067575266481, 212.5854415141057);
    glVertex2f(550, 200);
    glVertex2f(648.8601861009611, 185.9650889407841);
    glVertex2f(668.8757241491846, 174.6049186971978);
    glVertex2f(680.2156414076825, 162.5775669007505);
    glVertex2f(680.6093381246999, 146.7344532193056);
    glVertex2f(631.6336932204257, 118.6045116972741);
    glVertex2f(569.117351837075, 86.5063829913481);
    glVertex2f(363.5773562996234, 0);
    glVertex2f(0, 0);
    glVertex2f(0, 200);
    glVertex2f(111.7408391524158, 221.1637000231627);
    glEnd();


    float waveYOffset = sinf(waveTime) * 3.0f;

    // Wave 1
    glPushMatrix();
    glColor3ub(0, 100, 174);
    glBegin(GL_POLYGON);
    glVertex2f(36.659258, 64.867026 + waveYOffset);
    glVertex2f(49.09273, 61.582713 + waveYOffset);
    glVertex2f(65.748891, 64.163245 + waveYOffset);
    glVertex2f(79.589925, 65.805402 + waveYOffset);
    glVertex2f(92.705901, 64.662498 + waveYOffset);
    glVertex2f(105.975693, 62.450866 + waveYOffset);
    glVertex2f(120.45183, 66.0699 + waveYOffset);
    glVertex2f(135.732197, 62.852981 + waveYOffset);
    glVertex2f(156.441115, 61.445579 + waveYOffset);
    glVertex2f(142.970266, 57.223372 + waveYOffset);
    glVertex2f(128.573215, 59.135956 + waveYOffset);
    glVertex2f(115.827509, 59.233947 + waveYOffset);
    glVertex2f(102.356659, 56.821257 + waveYOffset);
    glVertex2f(86.875235, 59.636062 + waveYOffset);
    glVertex2f(64.959972, 58.630774 + waveYOffset);
    glVertex2f(49.552137, 57.577477 + waveYOffset);
    glVertex2f(36.659258, 64.867026 + waveYOffset);
    glEnd();


glColor3ub(0, 100, 174);
glBegin(GL_POLYGON);

glVertex2f(286.6592580056518, 64.8670265002663 + waveYOffset);
glVertex2f(299.0927300049575, 61.5827131419592 + waveYOffset);
glVertex2f(315.748890607801, 64.1632450663433 + waveYOffset);
glVertex2f(329.5899254749527, 65.8054017454969 + waveYOffset);
glVertex2f(342.7059010773613, 64.6624981323341 + waveYOffset);
glVertex2f(355.975693303523, 62.4508660946405 + waveYOffset);
glVertex2f(370.4518302775176, 66.0699003381391 + waveYOffset);
glVertex2f(385.7321970834007, 62.8529810105848 + waveYOffset);

glVertex2f(406.4411152545319, 61.4455788047798 + waveYOffset);
glVertex2f(392.9702655703981, 57.2233721873649 + waveYOffset);
glVertex2f(378.5732148379827, 59.1359560044248 + waveYOffset);
glVertex2f(365.8275087441582, 59.2339467670863 + waveYOffset);
glVertex2f(352.3566590600243, 56.8212572714206 + waveYOffset);
glVertex2f(336.875234796169, 59.6360616830306 + waveYOffset);
glVertex2f(314.959971877205, 58.6307743931699 + waveYOffset);
glVertex2f(299.5521373670315, 57.57747660613 + waveYOffset);
glVertex2f(286.6592580056518, 64.8670265002663 + waveYOffset);
glEnd();

glColor3ub(0, 100, 174);
glBegin(GL_POLYGON);

glVertex2f(66.659258, 124.867027 + waveYOffset);
glVertex2f(79.09273, 121.582713 + waveYOffset);
glVertex2f(95.748891, 124.163245 + waveYOffset);
glVertex2f(109.589925, 125.805402 + waveYOffset);
glVertex2f(122.705901, 124.662498 + waveYOffset);
glVertex2f(135.975693, 122.450866 + waveYOffset);
glVertex2f(150.45183, 126.0699 + waveYOffset);
glVertex2f(165.732197, 122.852981 + waveYOffset);

glVertex2f(186.441115, 121.445579 + waveYOffset);
glVertex2f(172.970266, 117.223372 + waveYOffset);
glVertex2f(158.573215, 119.135956 + waveYOffset);
glVertex2f(145.827509, 119.233947 + waveYOffset);
glVertex2f(132.356659, 116.821257 + waveYOffset);
glVertex2f(116.875235, 119.636062 + waveYOffset);
glVertex2f(94.959972, 118.630774 + waveYOffset);
glVertex2f(79.552137, 117.577477 + waveYOffset);
glVertex2f(66.659258, 124.867027 + waveYOffset);

glEnd();

glColor3ub(0, 100, 174);
glBegin(GL_POLYGON);

glVertex2f(6.659258, 164.867027 + waveYOffset);
glVertex2f(19.09273, 161.582713 + waveYOffset);
glVertex2f(35.748891, 164.163245 + waveYOffset);
glVertex2f(49.589925, 165.805402 + waveYOffset);
glVertex2f(62.705901, 164.662498 + waveYOffset);
glVertex2f(75.975693, 162.450866 + waveYOffset);
glVertex2f(90.45183, 166.0699 + waveYOffset);
glVertex2f(105.732197, 162.852981 + waveYOffset);

glVertex2f(126.441115, 161.445579 + waveYOffset);
glVertex2f(112.970266, 157.223372 + waveYOffset);
glVertex2f(98.573215, 159.135956 + waveYOffset);
glVertex2f(85.827509, 159.233947 + waveYOffset);
glVertex2f(72.356659, 156.821257 + waveYOffset);
glVertex2f(56.875235, 159.636062 + waveYOffset);
glVertex2f(34.959972, 158.630774 + waveYOffset);
glVertex2f(19.552137, 157.577477 + waveYOffset);
glVertex2f(6.659258, 164.867027 + waveYOffset);


glEnd();
glColor3ub(0, 100, 174);
glBegin(GL_POLYGON);

glVertex2f(266.659258, 124.867027 + waveYOffset);
glVertex2f(279.09273, 121.582713 + waveYOffset);
glVertex2f(295.748891, 124.163245 + waveYOffset);
glVertex2f(309.589925, 125.805402 + waveYOffset);
glVertex2f(322.705901, 124.662498 + waveYOffset);
glVertex2f(335.975693, 122.450866 + waveYOffset);
glVertex2f(350.45183, 126.0699 + waveYOffset);
glVertex2f(365.732197, 122.852981 + waveYOffset);

glVertex2f(386.441115, 121.445579 + waveYOffset);
glVertex2f(372.970266, 117.223372 + waveYOffset);
glVertex2f(358.573215, 119.135956 + waveYOffset);
glVertex2f(345.827509, 119.233947 + waveYOffset);
glVertex2f(332.356659, 116.821257 + waveYOffset);
glVertex2f(316.875235, 119.636062 + waveYOffset);
glVertex2f(294.959972, 118.630774 + waveYOffset);
glVertex2f(279.552137, 117.577477 + waveYOffset);
glVertex2f(266.659258, 124.867027 + waveYOffset);


glEnd();


glColor3ub(0, 100, 174);
glBegin(GL_POLYGON);

glVertex2f(466.659258, 124.867027 + waveYOffset);
glVertex2f(479.09273, 121.582713 + waveYOffset);
glVertex2f(495.748891, 124.163245 + waveYOffset);
glVertex2f(509.589925, 125.805402 + waveYOffset);
glVertex2f(522.705901, 124.662498 + waveYOffset);
glVertex2f(535.975693, 122.450866 + waveYOffset);
glVertex2f(550.45183, 126.0699 + waveYOffset);
glVertex2f(565.732197, 122.852981 + waveYOffset);

glVertex2f(586.441115, 121.445579 + waveYOffset);
glVertex2f(572.970266, 117.223372 + waveYOffset);
glVertex2f(558.573215, 119.135956 + waveYOffset);
glVertex2f(545.827509, 119.233947 + waveYOffset);
glVertex2f(532.356659, 116.821257 + waveYOffset);
glVertex2f(516.875235, 119.636062 + waveYOffset);
glVertex2f(494.959972, 118.630774 + waveYOffset);
glVertex2f(479.552137, 117.577477 + waveYOffset);
glVertex2f(466.659258, 124.867027 + waveYOffset);


glEnd();
glColor3ub(0, 100, 174);
glBegin(GL_POLYGON);

glVertex2f(266.659258, 274.867027 + waveYOffset);
glVertex2f(279.09273, 271.582713 + waveYOffset);
glVertex2f(295.748891, 274.163245 + waveYOffset);
glVertex2f(309.589925, 275.805402 + waveYOffset);
glVertex2f(322.705901, 274.662498 + waveYOffset);
glVertex2f(335.975693, 272.450866 + waveYOffset);
glVertex2f(350.45183, 276.0699 + waveYOffset);
glVertex2f(365.732197, 272.852981 + waveYOffset);

glVertex2f(386.441115, 271.445579 + waveYOffset);
glVertex2f(372.970266, 267.223372 + waveYOffset);
glVertex2f(358.573215, 269.135956 + waveYOffset);
glVertex2f(345.827509, 269.233947 + waveYOffset);
glVertex2f(332.356659, 266.821257 + waveYOffset);
glVertex2f(316.875235, 269.636062 + waveYOffset);
glVertex2f(294.959972, 268.630774 + waveYOffset);
glVertex2f(279.552137, 267.577477 + waveYOffset);
glVertex2f(266.659258, 274.867027 + waveYOffset);

glEnd();
glColor3ub(0, 100, 174);
glBegin(GL_POLYGON);

glVertex2f(266.659258, 194.867027 + waveYOffset);
glVertex2f(279.09273, 191.582713 + waveYOffset);
glVertex2f(295.748891, 194.163245 + waveYOffset);
glVertex2f(309.589925, 195.805402 + waveYOffset);
glVertex2f(322.705901, 194.662498 + waveYOffset);
glVertex2f(335.975693, 192.450866 + waveYOffset);
glVertex2f(350.45183, 196.0699 + waveYOffset);
glVertex2f(365.732197, 192.852981 + waveYOffset);

glVertex2f(386.441115, 191.445579 + waveYOffset);
glVertex2f(372.970266, 187.223372 + waveYOffset);
glVertex2f(358.573215, 189.135956 + waveYOffset);
glVertex2f(345.827509, 189.233947 + waveYOffset);
glVertex2f(332.356659, 186.821257 + waveYOffset);
glVertex2f(316.875235, 189.636062 + waveYOffset);
glVertex2f(294.959972, 188.630774 + waveYOffset);
glVertex2f(279.552137, 187.577477 + waveYOffset);
glVertex2f(266.659258, 194.867027 + waveYOffset);

glEnd();
glColor3ub(0, 100, 174);
glBegin(GL_POLYGON);

glVertex2f(266.659258, 239.867027 + waveYOffset);
glVertex2f(279.09273, 236.582713 + waveYOffset);
glVertex2f(295.748891, 239.163245 + waveYOffset);
glVertex2f(309.589925, 240.805402 + waveYOffset);
glVertex2f(322.705901, 239.662498 + waveYOffset);
glVertex2f(335.975693, 237.450866 + waveYOffset);
glVertex2f(350.45183, 241.0699 + waveYOffset);
glVertex2f(365.732197, 237.852981 + waveYOffset);

glVertex2f(386.441115, 236.445579 + waveYOffset);
glVertex2f(372.970266, 232.223372 + waveYOffset);
glVertex2f(358.573215, 234.135956 + waveYOffset);
glVertex2f(345.827509, 234.233947 + waveYOffset);
glVertex2f(332.356659, 231.821257 + waveYOffset);
glVertex2f(316.875235, 234.636062 + waveYOffset);
glVertex2f(294.959972, 233.630774 + waveYOffset);
glVertex2f(279.552137, 232.577477 + waveYOffset);
glVertex2f(266.659258, 239.867027 + waveYOffset);;

glEnd();
glPopMatrix();
}

void updateWave(int value) {
    waveTime += 0.05f;
    if (waveTime > 10000.0f) waveTime = 0.0f;

    glutPostRedisplay();
    glutTimerFunc(30, updateWave, 0);
}


void DrawSingleCloud(float offsetX) {
    glPushMatrix();


 glTranslatef(offsetX - cloudBaseOffsetX, 0.0f, 0.0f);
    glTranslatef(150.0f, 550.0f, 0.0f);
    glScalef(0.8f, 0.8f, 1.0f);
    glTranslatef(-150.0f, -550.0f, 0.0f);

    glBegin(GL_POLYGON);
    //  glVertex2f(62.0985829072365, 507);
    glVertex2f(235.9528753967153, 507);
    glVertex2f(237.8638298144673, 507.9062897839827);
    glVertex2f(239.2757599791256, 509.847693760388);
   glVertex2f(239.5221354516795, 511.1174393683276);


    glVertex2f(239.6287425202902, 512.6715540897047);
    glVertex2f(238.510964473269, 514.495297219055);
 glVertex2f(238.9860931104018, 513.8480815779787);

    glVertex2f(238.510964473269, 514.495297219055);
    glVertex2f(79.8313110733818, 523.4513000815567);
    glVertex2f(235.6282737204249, 518.3781051718655);
    glVertex2f(232.9220742381632, 520.3783395717982);
    glVertex2f(226.8625406148379, 523.4963520187521);
    glVertex2f(213.5668648976388, 523.8493345599167);
    glVertex2f(212.7283405294141, 526.0411757394546);
    glVertex2f(210.8317239724085, 528.7654067940628);
    glVertex2f(205.7281012371934, 533.9035134666781);
    glVertex2f(201.6245126865812, 536.1794533350849);
    glVertex2f(197.9002474473702, 537.2829393318881);
    glVertex2f(193.3828516479568, 537.6967465806894);
    glVertex2f(189.6585864087457, 537.3863911440884);
    glVertex2f(186, 536);
    glVertex2f(183.2790579897268, 534.6276761520802);
    glVertex2f(182.8670076100048, 541.9633998121573);
    glVertex2f(179.5665111737951, 549.0666421422609);
    glVertex2f(174.3287668293753, 555.3088854020489);
    glVertex2f(162.6335294575887, 563.3448767249945);
    glVertex2f(149.2162939451709, 567.075872696362);
    glVertex2f(134.6510596723324, 564.0623759502574);
    glVertex2f(125.5837093960603, 557.3951525681455);
    glVertex2f(119.5866496653695, 548.1093826625595);
    glVertex2f(117.0717536492733, 537.856345058475);
    glVertex2f(108.5597979024863, 541.5319623127693);
    glVertex2f(95.4049572029064, 541.822142622319);
    glVertex2f(87.2799085355187, 537.6628915187753);
    glVertex2f(82.7216074749131, 533.4709942735321);
    glVertex2f(79.8313110733818, 527.3050286169318);
    glVertex2f(79.8313110733818, 523.4513000815567);
    glVertex2f(73.8580318435504, 524.8964482823224);
    glVertex2f(67.6920661869503, 523.6439865083255);
    glVertex2f(62.778562304347, 520.6573468934097);
    glVertex2f(58.4431177020501, 515.7438430108064);
    glVertex2f(58.4431177020501, 515.7438430108064);
    glVertex2f(57.1906559280532, 510.5413094880499);
    glVertex2f(58.8284905555876, 508.518102006978);
    glVertex2f(62.0985829072365, 507);
        glVertex2f(235.9528753967153, 507);
    glEnd();
  glPopMatrix();
}
void Clouds() {
    float screenWidth = 1280.0f;

    for (int i = 0; i < totalClouds + 2; ++i) {
        float xOffset = fmod((i * cloudSpacing) - cloudBaseOffsetX + screenWidth, screenWidth + cloudSpacing) - cloudSpacing;
        DrawSingleCloud(xOffset);
    }
}
void updateClouds(int value) {
    cloudBaseOffsetX += cloudSpeed;

    glutPostRedisplay();
    glutTimerFunc(16, updateClouds, 0);
}
void DrawSinglePillar(float xOffset) {
    // Top cap
    glColor3ub(130, 120, 115);
    glBegin(GL_POLYGON);
    glVertex2f(xOffset + 0, 335);
    glVertex2f(xOffset + 0, 327);
    glVertex2f(xOffset + 137, 327);
    glVertex2f(xOffset + 138, 335);
    glEnd();

    // Main body
    glColor3ub(160, 150, 145);
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 26, 167);
    glVertex2f(xOffset + 26, 305);
    glVertex2f(xOffset + 112, 305);
    glVertex2f(xOffset + 112, 167);
    glEnd();

    // Decorative top indent
    glColor3ub(140, 130, 125);
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 0, 327);
    glVertex2f(xOffset + 26, 305);
    glVertex2f(xOffset + 112, 305);
    glVertex2f(xOffset + 137, 327);
    glEnd();

    // Decorative bottom indent
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xOffset + 50, 185);
    glVertex2f(xOffset + 90, 185);
    glVertex2f(xOffset + 90, 180);
    glVertex2f(xOffset + 50, 180);
    glEnd();
}
void Pillar() {
    float pillarOffsets[] = {6, 224, 457, 650, 850};

    for (int i = 0; i < 5; i++) {
        DrawSinglePillar(pillarOffsets[i]);
    }
}

void Lane() {
    float startX = 51;
    float startY = 361;
    float spacing = 74;
    int numQuads = (1000 - startX) / spacing;

    // relative points from base position
    float relA[2] = {0, 0};
    float relB[2] = {-3, -3};
    float relC[2] = {27, -3};
    float relD[2] = {28, 0};

    glColor3ub(255, 255, 255);

    for (int i = 0; i <= numQuads; i++) {
        float offsetX = startX + i * spacing;
        float offsetY = startY;

        glBegin(GL_QUADS);
        glVertex2f(offsetX + relA[0], offsetY + relA[1]); // a
        glVertex2f(offsetX + relB[0], offsetY + relB[1]); // b
        glVertex2f(offsetX + relC[0], offsetY + relC[1]); // c
        glVertex2f(offsetX + relD[0], offsetY + relD[1]); // d
        glEnd();
    }
}

void drawBird(float offsetX, float offsetY) {
    glPushMatrix();
    glTranslatef(birdOffsetX + offsetX, offsetY, 0);

    // BODY
    glColor3ub(50, 50, 50);
    glBegin(GL_POLYGON);
    glVertex2f(284.5618566821689, 518.6143928717819);
    glVertex2f(288.715613773733, 513.6679625691373);
    glVertex2f(293.7671063391205, 519.0162093250615);
    glVertex2f(289.2866631144752, 520.42537976792);
    glVertex2f(288.0493895428671, 521.2819537790334);
    glEnd();

    // LEFT WING
    glPushMatrix();
    glTranslatef(283.0, 523.0, 0);
    glRotatef(wingFlap, 0, 0, 1);
    glTranslatef(-283.0, -523.0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(100, 100, 100);
    glVertex2f(288.0493895428671, 521.2819537790334);
    glVertex2f(283.3858199268056, 520.0446802074252);
    glVertex2f(277.7705014095071, 523.8516758123733);
    glVertex2f(272.7262322329509, 525.3744740543525);
    glVertex2f(272.4407075625798, 528.4200705383109);
    glVertex2f(277.5801516292597, 527.9441960876924);
    glVertex2f(283.1954701465582, 525.9455233950947);
    glEnd();
    glPopMatrix();

    // RIGHT WING
    glPushMatrix();
    glTranslatef(295.0, 524.0, 0);
    glRotatef(-wingFlap, 0, 0, 1);
    glTranslatef(-295.0, -524.0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(100, 100, 100);
    glVertex2f(293.7671063391205, 519.0162093250615);
    glVertex2f(295.4730309725159, 520.9964291086623);
    glVertex2f(299.6607261379589, 524.1372004827443);
    glVertex2f(305, 525);
    glVertex2f(304.7049953145151, 528.1345458679398);
    glVertex2f(298.7089772367218, 527.8490211975687);
    glVertex2f(293.3791833897944, 524.9937744938577);
    glVertex2f(290.8813336292031, 521.9750395719387);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}
void drawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}

void drawWheel(float radius) {
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);
        for (int i = 0; i <= 360; i++) {
            float angle = i * M_PI / 180;
            glVertex2f(cos(angle) * radius, sin(angle) * radius);
        }
    glEnd();
}

void drawBus() {
    float baseY = 365.0f + 15.0f;

    glPushMatrix();
    glTranslatef(busX, 0.0f, 0.0f);

    // Bus Body
    drawRectangle(200, baseY, 600, baseY + 100, 1.0, 0.0, 0.0);
    drawRectangle(350, baseY + 100, 550, baseY + 110, 0.6, 0.6, 0.6);
    drawRectangle(220, baseY + 50, 270, baseY + 90, 0.3, 0.6, 1.0);
    drawRectangle(290, baseY + 50, 340, baseY + 90, 0.3, 0.6, 1.0);
    drawRectangle(360, baseY + 50, 410, baseY + 90, 0.3, 0.6, 1.0);
    drawRectangle(430, baseY + 50, 480, baseY + 90, 0.3, 0.6, 1.0);
    drawRectangle(510, baseY, 560, baseY + 90, 0.6, 0.6, 0.6);

    // Front Wheel
    glPushMatrix();
    glTranslatef(250, baseY, 0.0f);
    glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0, 0.0, 0.0);
    drawWheel(20);
    glPopMatrix();

    // Rear Wheel
    glPushMatrix();
    glTranslatef(550, baseY, 0.0f);
    glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0, 0.0, 0.0);
    drawWheel(20);
    glPopMatrix();

    glPopMatrix();
}

void updateBird(int value) {

    if (birdActive) {
        birdOffsetX += 1.50f;


        if (birdOffsetX > 1000) {
            birdOffsetX = -300.0f;


            if (transitioningToNight) {
                birdActive = false;
            }
        }


        if (wingUp) {
            wingFlap += 0.7f;
            if (wingFlap > 15) wingUp = false;
        } else {
            wingFlap -= 0.7f;
            if (wingFlap < -15) wingUp = true;
        }
    } else {

        if (!transitioningToNight) {
            birdActive = true;
            birdOffsetX = -300.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateBird, 0);
}

void Background()
{
glColor3ub(18, 47, 80);

     glBegin(GL_POLYGON);
glVertex2f(0,700);
    glVertex2f(0, 420);
    glVertex2f(63.167576f, 459.29944f);
    glVertex2f(90.24429f, 467.84998f);
    glVertex2f(97.36974f, 467.84998f);
    glVertex2f(109.00797f, 467.61246f);
    glVertex2f(132.52196f, 460.48701f);
    glVertex2f(305.84545f, 366.79953f);

    glVertex2f(330.37374f, 354.15966f);

    glVertex2f(327.3969732934661, 280);
    glVertex2f(330.37374f, 354.15966f);

    glVertex2f(376.59126f, 331.05090f);

    glVertex2f(420.57244f, 305.70582f);
    glVertex2f(453.74469f, 292.28783f);
    glVertex2f(472.75350f, 289.30605f);

    glVertex2f(495.48954f, 287.81517f);

    glVertex2f(515.61652, 288.18789);

    glVertex2f(530.1526771907593, 290.0515023851177);
    glVertex2f(565.9339782734854, 298.2513838832424);
    glVertex2f(637.1238585526593, 332.5417974208549);
    glVertex2f(791.0579975856373, 419.0132750374429);
    glVertex2f(823.9539302919059, 431.7646144905122);
    glVertex2f(834.59169f, 433.31595f);
    glVertex2f(849.21863f, 432.65109f);
    glVertex2f(875.36981f, 426.00248f);
    glVertex2f(914.59658f, 406.05667f);
    glVertex2f(925.23435f, 400.73778f);
    glVertex2f(931.66134f, 399.40806f);
    glVertex2f(938.08832f, 403.17560f);
    glVertex2f(950.05582f, 409.60259f);
    glVertex2f(967.12057f, 414.92147f);
    glVertex2f(980.19616f, 417.13768f);

    glVertex2f(1000, 414.03499f);
    glVertex2f (1000, 700);
 glVertex2f(0, 700);
    glEnd();
}
void drawSun(float cx, float cy, float radius, float alpha = 1.0f, int segments = 100) {

float r = 1.0f;
float g = 0.3f + 0.5f * sunAlpha;
float b = 0.0f + 0.1f * sunAlpha;
glColor4f(r, g, b, alpha);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float x = cx + cos(angle) * radius;
        float y = cy + sin(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();

    glDisable(GL_BLEND);
}



void drawMoon(float cx, float cy, float radius, float alpha = 1.0f, int segments = 100) {
    glColor4f(0.9f, 0.9f, 1.0f, alpha);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float x = cx + cos(angle) * radius;
        float y = cy + sin(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();

    glDisable(GL_BLEND);
}
void updateMoon(int value) {
    if (moonAlpha < 1.0f) {
        moonAlpha += 0.01f;
        if (moonAlpha > 1.0f) moonAlpha = 1.0f;
        glutPostRedisplay();
        glutTimerFunc(33, updateMoon, 0);
    }
}
void updateSun(int value) {
    if (!sunVisible) {
        glutTimerFunc(33, updateSun, 0);
        return;
    }

    float speed = 0.5f;
    float dx = targetSunX - sunX;
    float dy = targetSunY - sunY;

    if (sunShouldSet && fabs(dx) < 1.0f && fabs(dy) < 1.0f) {
        sunAlpha -= 0.01f;
        if (sunAlpha <= 0.0f) {
            sunAlpha = 0.0f;
            sunVisible = false;

            glutTimerFunc(20000, [](int) {
    transitioningToNight = true;

    glutTimerFunc(10000, [](int) {
        moonVisible = true;
        moonAlpha = 0.0f;
        updateMoon(0);
        glutPostRedisplay();
    }, 0);
}, 0);
            }
        }
     else if (sunShouldSet) {
        float distance = sqrt(dx * dx + dy * dy);
        if (distance > 0.0f) {
            sunX += speed * dx / distance;
            sunY += speed * dy / distance;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(33, updateSun, 0);
}


void drawSkyBackground() {
    float topR, topG, topB;
    float bottomR, bottomG, bottomB;

    if (transitioningToNight) {

      // Lighter, bluish night
    topR = 0.2f; topG = 0.25f; topB = 0.4f;
    bottomR = 0.25f; bottomG = 0.3f; bottomB = 0.45f;
    } else {
        // Sunset transition based on sunAlpha
        topR = 0.3f * (1 - sunAlpha) + 0.0f * sunAlpha;
        topG = 0.1f * (1 - sunAlpha) + 0.6f * sunAlpha;
        topB = 0.3f * (1 - sunAlpha) + 0.8f * sunAlpha;

        bottomR = 1.0f * (1 - sunAlpha) + 0.9f * sunAlpha;
        bottomG = 0.4f * (1 - sunAlpha) + 0.9f * sunAlpha;
        bottomB = 0.2f * (1 - sunAlpha) + 0.5f * sunAlpha;
    }

    glBegin(GL_QUADS);
        glColor3f(topR, topG, topB);
        glVertex2f(0, 600); glVertex2f(1000, 600);

        glColor3f(bottomR, bottomG, bottomB);
        glVertex2f(1000, 280); glVertex2f(0, 280);
    glEnd();
}



void updateBus(int value) {
    busX += 2.0f;
    if (busX > 1000) busX = -600;

    wheelAngle += wheelSpeed;
    if (wheelAngle > 360) wheelAngle -= 360;

    glutPostRedisplay();
    glutTimerFunc(16, updateBus, 0);
}
void drawCar() {
    glPushMatrix();
    glTranslatef(carX, 368, 0);

    glScalef(-1.0f, 1.0f, 1.0f);


    glScalef(30.0f, 30.0f, 1.0f);

    glTranslatef(-0.5f, -0.5f, 0.0f);

    // ==== Car Body ====
    glBegin(GL_POLYGON);
RGB carColor = carColors[currentRightCarColorIndex];
glColor3f(carColor.r, carColor.g, carColor.b);

    glVertex2f(3.02, 0.39);
    glVertex2f(-3.24, 0.40);
    glVertex2f(-3.23, 1.02);
    glVertex2f(-2.49, 1.02);
    glVertex2f(-1.70, 1.70);
    glVertex2f(0.70, 1.66);
    glVertex2f(1.65, 1.01);
    glVertex2f(3, 1);
    glEnd();

    // ==== Roof ====
    glBegin(GL_POLYGON);
    glColor3ub(182, 183, 179);
    glVertex2f(-2.27, 1.08);
    glVertex2f(-1.66, 1.57);
    glVertex2f(0.60, 1.58);
    glVertex2f(1.42, 1.08);
    glEnd();

    // ==== Window Divider ====
    glBegin(GL_LINES);
glColor3f(carColor.r, carColor.g, carColor.b);

    glVertex2f(-0.52, 1.58);
    glVertex2f(-0.52, 1.08);
    glEnd();

    // ==== Wheels ====
    for (float offsetX : {-2.43f, 2.0f}) {
        glPushMatrix();
        glTranslatef(offsetX, 0.36, 0);
        glRotatef(carAngle, 0.0f, 0.0f, 1.0f);

        // Outer wheel
        glBegin(GL_POLYGON);
        for (int i = 0; i < 200; i++) {
            float angle = i * 2 * M_PI / 200;
            float r = 0.4f;
            glColor3ub(75, 79, 79);
            glVertex2f(cos(angle) * r, sin(angle) * r);
        }
        glEnd();

        // Inner hub
        glBegin(GL_POLYGON);
        for (int i = 0; i < 200; i++) {
            float angle = i * 2 * M_PI / 200;
            float r = 0.2f;
            glColor3ub(162, 168, 168);
            glVertex2f(cos(angle) * r, sin(angle) * r);
        }
        glEnd();

        glPopMatrix();
    }

    glPopMatrix();
}

void updateCar(int value) {
    carX -= 2.0f;
    if (carX < -100.0f) {
        carX = 1000.0f;

    currentRightCarColorIndex = (currentRightCarColorIndex - 1 + totalRightCarColors) % totalRightCarColors;

    }

    carAngle -= 5.0f;
    if (carAngle < -360.0f) carAngle += 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, updateCar, 0);
}

void car() {
    float baseY = 380.0f;

    glPushMatrix();
glTranslatef(greenCarX, baseY, 0);
 glScalef(30.0f, 30.0f, 1.0f);
    glTranslatef(-0.5f, -0.5f, 0.0f);

    // Car body
    glLineWidth(2);
    glBegin(GL_POLYGON);
    RGB c = carColors[currentCarColorIndex];
glColor3f(c.r, c.g, c.b);

    glVertex2f(3.02, 0.39);
    glVertex2f(-3.24, 0.40);
    glVertex2f(-3.23, 1.02);
    glVertex2f(-2.49, 1.02);
    glVertex2f(-1.70, 1.70);
    glVertex2f(0.70, 1.66);
    glVertex2f(1.65, 1.01);
    glVertex2f(3, 1);
    glEnd();

    // Car lines
  /*  glLineWidth(4);
    glBegin(GL_LINES);
    glColor3ub(1, 1, 1);
    glVertex2f(3.02, 0.39); glVertex2f(-3.24, 0.40);
    glVertex2f(-3.24, 0.40); glVertex2f(-3.23, 1.02);
    glVertex2f(-3.23, 1.02); glVertex2f(-2.49, 1.02);
    glVertex2f(-2.49, 1.02); glVertex2f(-1.70, 1.70);
    glVertex2f(-1.70, 1.70); glVertex2f(0.70, 1.66);
    glVertex2f(0.70, 1.66); glVertex2f(1.65, 1.01);
    glVertex2f(1.65, 1.01); glVertex2f(3, 1);
    glVertex2f(3, 1); glVertex2f(3.02, 0.39);
    glEnd();
*/
    // Car window
    glBegin(GL_POLYGON);
    glColor3ub(182, 183, 179);
    glVertex2f(-2.27, 1.08);
    glVertex2f(-1.66, 1.57);
    glVertex2f(0.60, 1.58);
    glVertex2f(1.42, 1.08);
    glEnd();

    // Window division
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.52, 1.58);
    glVertex2f(-0.52, 1.08);
    glEnd();


    auto drawCarWheel = [](float centerX) {
        glPushMatrix();
        glTranslatef(centerX, 0.36, 0);
      glRotatef(greenCarWheelAngle, 0.0f, 0.0f, 1.0f);

        glTranslatef(-centerX, -0.36, 0);

        glBegin(GL_POLYGON);
        for (int i = 0; i < 200; i++) {
            float A = (i * 2 * M_PI) / 200;
            float r = 0.40;
            glColor3ub(75, 79, 79);
            glVertex2f(centerX + r * cos(A), 0.36 + r * sin(A));
        }
        glEnd();

        glBegin(GL_POLYGON);
        for (int i = 0; i < 200; i++) {
            float A = (i * 2 * M_PI) / 200;
            float r = 0.20;
            glColor3ub(162, 168, 168);
            glVertex2f(centerX + r * cos(A), 0.36 + r * sin(A));
        }
        glEnd();
        glPopMatrix();
    };

    drawCarWheel(-2.43);
    drawCarWheel(1.99);

    glPopMatrix();
}
void updateGreenCar(int value) {
    greenCarX += 2.5f;
    if (greenCarX > 1000.0f) {
        greenCarX = -600.0f;


        currentCarColorIndex = (currentCarColorIndex + 1) % totalCarColors;
    }

    greenCarWheelAngle -= 8.0f;
    if (greenCarWheelAngle < -360.0f) greenCarWheelAngle += 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, updateGreenCar, 0);
}


void drawLandscapeScene() {
    Background();
    drawSkyBackground();
    if (sunVisible) {
    drawSun(sunX, sunY, 52.01f, sunAlpha);
}

if (moonVisible) {
    drawMoon(moonX, moonY, moonRadius, moonAlpha);
}

    Mountain();

    River();

    Ground();

    bridge();
    Lane();
    Clouds();
    Pillar();
 if (birdActive) {
    drawBird(0.0f, 0.0f);
    drawBird(-50.0f, -30.0f);
    drawBird(50.0f, -30.0f);
}

 drawBus();
 car();
     drawCar();

  tree();
  if (rainActive) {
    RainMehedi();
}


}



void display() {
    glClear(GL_COLOR_BUFFER_BIT);

            drawLandscapeScene();


    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1000.0, 0.0, 600.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {

            case 'd':
            case 'D':
                sunVisible = true;
                sunShouldSet = false;
                cout << "  Sun appeared." << endl;
                break;

              case 'a':
            case 'A':
                sunVisible = true;
                sunShouldSet = true;
                targetSunX = 506.17f;
                targetSunY = 287.03f;
                cout << " Sunset triggered." << endl;
                break;

                 case 'i':
                    case 'I':
                        transitioningToNight = true;
                        cout << " Night scene activated." <<endl;
                        break;
                    case 's':
                    case 'S':
                        if (!moonVisible) {
                            moonVisible = true;
                            moonAlpha = 0.0f;
                            updateMoon(0);
                           cout << "Moon appeared." << endl;
                        }
                        break;

                        case 'g':
            case 'G':
                rainActive = !rainActive;
                if (rainActive) {
                    initializeRainDrops();
                    glutTimerFunc(0, updateRain, 0);
                   cout << " Rain started!" << endl;
                } else {
                  cout << " Rain stopped!" << endl;
                }
                break;


    }
    glutPostRedisplay();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glDisable(GL_DEPTH_TEST);
}


void printInstructions() {
    cout << "=== Keyboard Controls ===" << endl;
    cout << "D  Show Sun" << endl;
    cout << "A  Start Sunset" << endl;
    cout << "I to Switch to Night Scene" << endl;
    cout << "S to  Show Moon" << endl;
    cout << "=========================" << endl;
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("CG Project");
    init();

sunVisible = false;


    glutTimerFunc(0, updateClouds, 0);
    glutTimerFunc(0, updateBird, 0);
    glutTimerFunc(0, updateCar, 0);
glutTimerFunc(30, updateWave, 0);

 glutTimerFunc(0, updateGreenCar, 0);
glutTimerFunc(0, updateSun, 0);
 printInstructions();
initializeRainDrops();

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

glutTimerFunc(0, updateBus, 0);

      glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
