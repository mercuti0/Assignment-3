/*
 * This function returns the
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "testing/SimpleTest.h"

using namespace std;

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
string operatorsFrom(string str) {
    Set<char> cleanOptions = {'(', ')', '{', '}', '[', ']'};
    if (str.size() < 1)
        return "";
    if (cleanOptions.contains(str[0]))
        return str[0] + operatorsFrom(str.substr(1));
    else {
        return operatorsFrom(str.substr(1));
    }
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
bool operatorsAreMatched(string ops) {
    Map<char, char> indexCheck = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
    Set<char> open = {'(', '{', '['};
    if (ops.size() < 1)
        return true;
    if (stringIndexOf(ops, indexCheck[ops[0]]) == -1 || ops.size() == 1 || !open.contains(ops[0]))
        return false;
    else if (ops[stringIndexOf(ops, indexCheck[ops[0]]) - 1] == ops[0]) {
        ops.erase(stringIndexOf(ops, indexCheck[ops[0]]) - 1, 2);
        return operatorsAreMatched(ops);
    } else if (open.contains(ops[stringIndexOf(ops, indexCheck[ops[0]]) - 1])){
        return false;
    } else {
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
