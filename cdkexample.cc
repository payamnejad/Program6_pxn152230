/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Payam Nejad
 * Email:  pxn152230@utdallas.edu
 */

#include <iostream>
#include "cdk.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdint.h>

#define MATRIX_WIDTH 3 //defining the num of rows
#define MATRIX_HEIGHT 5//defining the num of cols
#define BOX_WIDTH 15 //defining box width
#define MATRIX_NAME_STRING "Binary File Contents"


int length_max = 25;

using namespace std;

class BinaryFileHeader
{
public:
 uint32_t magicNumber; /* Should be 0xFEEDFACE */
 uint32_t versionNumber;
 uint64_t numRecords;
};

/*
* Records in the file have a fixed length buffer
* that will hold a C-Style string. This is the
* size of the fixed length buffer.
*/
const int maxRecordStringLength = 25;
class BinaryFileRecord
{
public:
 uint8_t strLength;
 char stringBuffer[maxRecordStringLength];
};


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c", "d", "e"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
