/*
 * This function returns whether or not the bracketing operators are properly nested and matched.
 * This can be applied to coding with C++ as all the operators need to be balanced.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "testing/SimpleTest.h"

using namespace std;

/*
 * This function goes through the entirety of string str, only
 * returning the bracketing operators, removing all the non-bracketing
 * operators.
 */
string operatorsFrom(string str) {
    Set<char> cleanOptions = {'(', ')', '{', '}', '[', ']'};
    if (str.size() < 1)
        return "";
    if (cleanOptions.contains(str[0]))
        return str[0] + operatorsFrom(str.substr(1));
    else {
        // Removes the non-bracketing operator
        return operatorsFrom(str.substr(1));
    }
}

/*
 * This function will run until the size of the given string ops is 0, if true. First,
 * if the string does not start with an opening bracket operator, or if there is only one
 * character, then the string was unbalanced. Then, if the closing pair of the first opening
 * operator actually has its opening pair next to it, we remove those. If this opening pair next
 * to it does not belong to this closing bracket, then it is unbalanced or just false. Lastly,
 * since we first determined that there was an open/close pair, and its not part of the listed
 * conditions, then they are a balanced pair that can be removed to continue checking ops.
 */
bool operatorsAreMatched(string ops) {
    Map<char, char> indexCheck = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
    Set<char> open = {'(', '{', '['};
    if (ops.size() < 1)
        return true;

    // This checks if the string starts with a close, or if size is just 1
    if (stringIndexOf(ops, indexCheck[ops[0]]) == -1 || ops.size() == 1)
        return false;

    // Checks if the closest closing pair actually has its opening pair behind it
    else if (ops[stringIndexOf(ops, indexCheck[ops[0]]) - 1] == ops[0]) {
        ops.erase(stringIndexOf(ops, indexCheck[ops[0]]) - 1, 2);
        return operatorsAreMatched(ops);

    // Checks if the opening pair behind the closing one does not belong to it
    } else if (open.contains(ops[stringIndexOf(ops, indexCheck[ops[0]]) - 1])) {
        return false;

    } else {
        // With the above conditions met, the respective pair can be removed
        ops.erase(stringIndexOf(ops, indexCheck[ops[0]]), 1);
        ops.erase(0, 1);
        return operatorsAreMatched(ops);
    }
}

/*
 * The isBalanced function assumes correct implementation of
 * the above two functions operatorsFrom and operatorsMatch.
 * It uses operatorsFrom to extract the operator characters
 * from the input string and then confirms that those
 * operators are balanced by using operatorsMatch.
 * You should not modify the provided code in the isBalanced
 * function.  If the previous two functions have been implemented
 * correctly, the provided isBalanced will correctly report whether
 * the input string has balanced bracketing operators.
 */
bool isBalanced(string str) {
    string ops = operatorsFrom(str);
    return operatorsAreMatched(ops);
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
}

PROVIDED_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{}"));
}

PROVIDED_TEST("isBalanced on example from writeup") {
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on non-balanced examples from writeup") {
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}

STUDENT_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("ROmeo"), "");
    EXPECT_EQUAL(operatorsFrom("[RO)()(meo]"), "[)()(]");
    EXPECT_EQUAL(operatorsFrom("{ROmeo}+!]["), "{}][");
}

STUDENT_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{()}"));
    EXPECT(operatorsAreMatched("[][{()}]"));
    EXPECT(!operatorsAreMatched("{(})"));
    EXPECT(operatorsAreMatched("({{}[]()})"));
    EXPECT(!operatorsAreMatched("()){{}[]()})"));
    EXPECT(!operatorsAreMatched("()([{}[]{{}[]()}))"));
    EXPECT(!operatorsAreMatched("{{}[]!()})"));
}
