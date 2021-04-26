/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include "recursion.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * This function draws a filled, black triangle on the provided GWindow
 * that is defined by the corner GPoints one, two, and three. This
 * function has been provided for you and does not need to be modified.
 */
void fillBlackTriangle(GWindow& window, GPoint one, GPoint two, GPoint three) {
    window.setColor("black");
    window.fillPolygon( {one, two, three} );
}
// Provided Helper Function from lecture
GPoint pointBetween(GPoint p1, GPoint p2, double fraction){
    double deltaX = p2.x - p1.x;
    double deltaY = p2.y - p1.y;
    double x = p1.x + fraction * deltaX;
    double y = p1.y + fraction * deltaY;
    GPoint newPoint(x, y);
    return newPoint;
}
/*
 * Draws the black triangles according to order on the demo.
 */
int drawSierpinskiTriangle(GWindow& window, GPoint one, GPoint two, GPoint three, int order) {
    if (order < 1) {
        fillBlackTriangle(window, one, two, three);
        return 1;
    } else {
        return drawSierpinskiTriangle(window, one, pointBetween(one, two, 0.5),
                                    pointBetween(one, three, 0.5), order - 1) +
               drawSierpinskiTriangle(window, two, pointBetween(two, one, 0.5),
                                    pointBetween(two, three, 0.5), order - 1) +
               drawSierpinskiTriangle(window, three, pointBetween(three, one, 0.5),
                                     pointBetween(three, two, 0.5), order - 1);
    }
}


/* * * * * * Test Cases * * * * * */

/*
 * Do not modify the code beyond this line! There are no
 * unit tests for this problem. You should do all testing
 * via the interactive demo.
 */

PROVIDED_TEST("Test fractal drawing interactively using graphical demo") {
    runInteractiveDemo();
}

