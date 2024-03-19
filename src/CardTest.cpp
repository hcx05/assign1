 /* Copyright (c) 1999 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     CardTest.cc
   PURPOSE
     Testing card displaying
   NOTES

   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Oct 7, 1999: Created.
***************************************************************************/

/* $Log:$ */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
}

#include <iostream>
#include "AnsiPrint.h"
#include "Cards.h"

using namespace std;

/**
 * Print my id
 */
void
PrintMyID(const char* studId) {

    char* str = new char[sizeof(studId) + 5];
    // we put string in a buffer first
    sprintf(str, "ID: %s", studId);
    // print the buffer out with color
    AnsiPrint(str, yellow, red, true, true);
    cout << endl << endl;
    delete[] str;
}


/**
 * PrintUsage
 */
void
PrintUsage(const char* progName) {

    assert(progName);
    cout << "Usage: " << progName << " NCards [Seed]" << endl;

}

/**
 * Main Function Call
 */
int
main(int argc, char** argv) {
    int ncards = 0;  // number of cards to draw
    if (argc == 3) {
        long seed = atoi(argv[2]); // the third argument is the seed
        srand(seed);
        ncards = atoi(argv[1]); // the second argument is the number of cards
    }
    else if (argc == 2) {
        ncards = atoi(argv[1]);
    }
    else {
        PrintUsage(argv[0]);
        exit(-1);
    }

    // You are asked to fill in a few missing statements here

    static bool currcard[52];
    for (int i = 0; i < 52; i++) {
        currcard[i] = true;
    }

    for (int i = 0; i < ncards; i++) {
        int thiscard = rand() % kNCards; //thiscard: 0-51
        while (!currcard[thiscard])
            thiscard = rand() % kNCards;

        int hdcs = thiscard / 13;
        for (int j = 0; j < kCardHeight; j++) {
            string b = "";
            for (int k = 0; k < kCardWidth; k++) {
                char a = card[thiscard % 13][j][k];
                if (hdcs == 0)
                    if (a == 'x')
                        a = 'H';
                if (hdcs == 1)
                    if (a == 'x')
                        a = 'D';
                if (hdcs == 2)
                    if (a == 'x')
                        a = 'C';
                if (hdcs == 3)
                    if (a == 'x')
                        a = 'S';

                b += a;
            }
            //            if (hdcs == 0 || hdcs == 1) {
            //                AnsiPrint(&b, red, white, true, true);
            //            } else {
            //                AnsiPrint(&b, black, white, true, true);
            //            }
            const char* str = b.c_str();
            if (hdcs < 2) {
                AnsiPrint(str, red, white, true, true);
                cout << endl;
            }
            if (hdcs >= 2) {
                AnsiPrint(str, black, white, true, true);
                cout << endl;
            }
        }
        currcard[thiscard] = false;
        cout << endl;
    }

    // Print my id at the end of the program
    PrintMyID("112703030");

    return 0;

}

