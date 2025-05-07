#include <cppunit/extensions/HelperMacros.h>
#include <sstream>
#include <iostream>
#include <vector>
#include "battleship.h"
#include <cppunit/ui/text/TestRunner.h>

using namespace std;



class BattleshipTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(BattleshipTest);
    CPPUNIT_TEST(testResetMenuDisplay);
    CPPUNIT_TEST(testResetMenuDisplay_EmptySource);
    CPPUNIT_TEST(testGetCoordinates_ValidInput);
    CPPUNIT_TEST(testCheckField_Hit);
    CPPUNIT_TEST(testCheckField_Miss);
    CPPUNIT_TEST(testCurrentField_CopyCheck);
    CPPUNIT_TEST(testCheckHits_GameNotWon);
    CPPUNIT_TEST(testCheckHits_GameWon);
    CPPUNIT_TEST(testShowOptions_MarkHitAndMiss);
    CPPUNIT_TEST(testCheckField_InvalidCoordinates);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override {
        // Initialize global variables before each test
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                currentPlayPen[i][j] = '-';

        for (int i = 0; i < 11; ++i)
            for (int j = 0; j < 11; ++j)
                showOptions[i][j] = '-';

        carrierHits = {5, 5, 5, 5, 5};
        battleshipHits = {4, 4, 4, 4};
        submarineHits = {3, 3, 3};
        destroyerHits = {2, 2};
        crusierHits = {3, 3, 3};
    }

    void testResetMenuDisplay() {
        char source[11][11];
        char dest[11][11];
        for (int i = 0; i < 11; ++i)
            for (int j = 0; j < 11; ++j)
                source[i][j] = 'x';

        resetMenuDisplay(source, dest);

        for (int i = 0; i < 11; ++i)
            for (int j = 0; j < 11; ++j)
                CPPUNIT_ASSERT_EQUAL(source[i][j], dest[i][j]);
    }

    void testResetMenuDisplay_EmptySource() {
        char source[11][11] = {};
        char dest[11][11] = {};

        resetMenuDisplay(source, dest);

        for (int i = 0; i < 11; ++i) {
            for (int j = 0; j < 11; ++j) {
                CPPUNIT_ASSERT_EQUAL(source[i][j], dest[i][j]);
            }
        }
    }

    void testGetCoordinates_ValidInput() {
        std::istringstream input("5\n3\n");
        std::streambuf* originalCin = std::cin.rdbuf();
        std::cin.rdbuf(input.rdbuf());

        vector<int> result;
        getCoordinates(result);

        std::cin.rdbuf(originalCin);
        CPPUNIT_ASSERT_EQUAL(5, result[0]);
        CPPUNIT_ASSERT_EQUAL(3, result[1]);
    }

    void testCheckField_Hit() {
        currentPlayPen[0][0] = 'c';
        showOptions[1][1] = '-';
        vector<int> attempt = {0, 0};

        checkField(attempt);

        CPPUNIT_ASSERT_EQUAL('x', currentPlayPen[0][0]);
        CPPUNIT_ASSERT_EQUAL('H', showOptions[1][1]);
        CPPUNIT_ASSERT(attempt.empty());
    }

    void testCheckField_Miss() {
        currentPlayPen[0][1] = '-';
        showOptions[1][2] = '-';
        vector<int> attempt = {0, 1};

        checkField(attempt);

        CPPUNIT_ASSERT_EQUAL('M', showOptions[1][2]);
        CPPUNIT_ASSERT(attempt.empty());
    }

    void testCurrentField_CopyCheck() {
        char src[10][10];
        char dst[10][10];

        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                src[i][j] = (i == 0 && j == 0) ? 'S' : '-';

        currentField(src, dst);

        CPPUNIT_ASSERT_EQUAL('S', dst[0][0]);
        CPPUNIT_ASSERT_EQUAL('-', dst[1][1]);
    }

    void testCheckHits_GameNotWon() {
        carrierHits = {1, 2};
        CPPUNIT_ASSERT(!checkHits());
    }

    void testCheckHits_GameWon() {
        carrierHits.clear();
        battleshipHits.clear();
        submarineHits.clear();
        destroyerHits.clear();
        crusierHits.clear();
        CPPUNIT_ASSERT(checkHits());
    }

    void testShowOptions_MarkHitAndMiss() {
        currentPlayPen[0][0] = 'b';
        currentPlayPen[0][1] = '-';
        showOptions[1][1] = '-';
        showOptions[1][2] = '-';

        vector<int> hit = {0, 0};
        vector<int> miss = {0, 1};

        checkField(hit);
        checkField(miss);

        CPPUNIT_ASSERT_EQUAL('H', showOptions[1][1]);
        CPPUNIT_ASSERT_EQUAL('M', showOptions[1][2]);
    }

    void testCheckField_InvalidCoordinates() {
        vector<int> attempt = {10, 10}; // Out-of-bounds coordinates

        checkField(attempt);

        // Ensure no changes were made to the playpen or options
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                CPPUNIT_ASSERT_EQUAL('-', currentPlayPen[i][j]);
            }
        }
        for (int i = 0; i < 11; ++i) {
            for (int j = 0; j < 11; ++j) {
                CPPUNIT_ASSERT_EQUAL('-', showOptions[i][j]);
            }
        }
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(BattleshipTest);

int main() {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    return runner.run() ? 0 : 1;
}
