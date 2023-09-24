/*
We stack glasses in a pyramid, where the first row has 1 glass, the second row has 2 glasses, and so on until the 100th row.  Each glass holds one cup of champagne.

Then, some champagne is poured into the first glass at the top.  When the topmost glass is full, any excess liquid poured will fall equally to the glass immediately to the left and right of it.  When those glasses become full, any excess champagne will fall equally to the left and right of those glasses, and so on.  (A glass at the bottom row has its excess champagne fall on the floor.)

For example, after one cup of champagne is poured, the top most glass is full.  After two cups of champagne are poured, the two glasses on the second row are half full.  After three cups of champagne are poured, those two cups become full - there are 3 full glasses total now.  After four cups of champagne are poured, the third row has the middle glass half full, and the two outside glasses are a quarter full, as pictured below.



Now after pouring some non-negative integer cups of champagne, return how full the jth glass in the ith row is (both i and j are 0-indexed.)
*/

//
//
//
// I solved this with the help of the hints provided by Shubham Raj
// Link to his profile: https://leetcode.com/Shubham_Raj22/
//
//
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 101

double memo[MAX_ROW][MAX_ROW];

double max(double a, double b)
{
    return a > b ? a : b;
}

double min(double a, double b)
{
    return a < b ? a : b;
}

double contribution(int poured, int row, int glass)
{
    if (row < 0 || glass < 0 || row < glass || poured == 0)
    {
        return 0.0;
    }
    if (row == 0 && glass == 0)
    {
        return (double)(poured - 1) / 2.0;
    }

    if (memo[row][glass] != -1.0)
    {
        return memo[row][glass];
    }

    double result = ((max(0, contribution(poured, row - 1, glass)) + max(0, contribution(poured, row - 1, glass - 1))) - 1) / 2;
    memo[row][glass] = result;
    return result;
}

double champagneTower(int poured, int query_row, int query_glass)
{
    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_ROW; j++)
        {
            memo[i][j] = -1.0;
        }
    }
    // this is me being lazy to think
    double filled = (query_row == 0 && query_glass == 0 && poured >= 1) ? 1.0 : (contribution(poured, query_row - 1, query_glass - 1) + contribution(poured, query_row - 1, query_glass));
    return min(filled, 1.0);
}

int main()
{
    int poured = 1;
    int query_row = 0;
    int query_glass = 0;

    double result = champagneTower(poured, query_row, query_glass);
    printf("Result: %.6lf\n", result);

    return 0;
}
