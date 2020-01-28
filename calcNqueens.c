// 用回溯算法处理8皇后问题
//make calcNqueens
//Usage: ./calcNqueens 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isValidStep(int *result, int row, int column, int maxColumn);
void printResult(int *result, int maxRow, int maxColumn);
void calcEightQueens(int *result, int row, int maxRow, int maxColumn);

int main(int argc, char *argv[])
{
	int queens = atoi(argv[1]);
	int result[queens];
	calcEightQueens(result, 0, queens, queens);
}


// 当前行的摆放方法
void
calcEightQueens(int *result, int row, int maxRow, int maxColumn)
{
	// 等于第N行时，结束(元素大小为N的数组，下标是0～N-1
	if ( row == maxRow) {
		printf("print result\n");
		printf("------------\n");
		printResult(result, maxRow, maxColumn);
		return;
	}

	int column;
	// 从第一列开始往后摆放
	for ( column = 0; column < maxColumn; ++column){
		if ( isValidStep(result, row, column, maxColumn)){
			result[row] = column;
			calcEightQueens(result, row + 1, maxRow, maxColumn);
		}
	}
}

//判断这一步是否正确
bool
isValidStep(int *result, int row, int column, int maxColumn)
{
	int up      = column    ;  // 上方
	int leftup  = column - 1;  // 左对角线
	int rightup = column + 1;  // 右对角线
	int i;

	// 逐行向上检查
	for ( i = row - 1; i >= 0; --i){
		//判断是否和上方元素重合
		//result[i] 第i行的摆放列
		if (result[i] == up) return false;

		if (leftup >= 0 ){
		//判断是否和左上方元素重合
			if (result[i] == leftup) return false;
			--leftup;
		}
		if ( rightup < maxColumn) {
		//判断是否和右上方元素重合
			if (result[i] == rightup) return false;
			++rightup;
		}
	}
	return true;
}

void
printResult(int *result, int maxRow, int maxColumn)
{
	int i,j;
	for (i = 0; i < maxRow; ++i){
		for (j = 0; j < maxColumn; ++j){
			if (result[i] == j) {
				printf("Q ");
			} else{
				printf("* ");
			}
		}
		printf("\n");
	}
	printf("\n");
}
