/*
 * This function reproduces the Sierpinski triangle, given order n (where n > 0).
 * Where three triangles' (order n -1) side lengths are half of the original triangle's,
 * meeting corner to corner.
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

// Provided Helper Function from lecture to calculate the halfway point between p1 and p2.
GPoint pointBetween(GPoint p1, GPoint p2, double fraction) {
    double deltaX = p2.x - p1.x;
    double deltaY = p2.y - p1.y;
    double x = p1.x + fraction * deltaX;
    double y = p1.y + fraction * deltaY;
    GPoint newPoint(x, y);
    return newPoint;
}

/*
 * Draws the Sierpinski black triangles using the given three points
 * of the specified order. Returns the total number of triangles drawn.
 */
int drawSierpinskiTriangle(GWindow& window, GPoint one, GPoint two, GPoint three, int order) {
    if (order < 1) {
        fillBlackTriangle(window, one, two, three);
        return 1;
    } else {   // Finds the triangles on the bottom left side
        return drawSierpinskiTriangle(window, one, pointBetween(one, two, 0.5),
                                    pointBetween(one, three, 0.5), order - 1) +
               // Find the triangles on the top side
               drawSierpinskiTriangle(window, two, pointBetween(two, one, 0.5),
                                    pointBetween(two, three, 0.5), order - 1) +
               // Finds the triangles on the bottom right side
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

