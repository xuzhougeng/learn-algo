#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValidStep(int (*metrics)[9], int row, int column, int value);
bool checkRow(int (*metrics)[9], int row, int column, int value );
bool checkColumn(int (*metrics)[9], int row, int column, int value );
bool checkGrid(int (*metrics)[9], int row, int column, int value );
void calcSudoku( int (*metrics)[9], int pos , int value);
void printSudoku(int (*metrics)[9]);

int main(int argc, char *argv[]){

	if ( argc == 1) {
		fprintf(stderr, "Usage: %s sudoku.txt\n", argv[0]);
		return -1;

	}

	// 读取数独
	FILE *fp;
	fp = fopen(argv[1], "r");
	int line = 0;
	int sudoku[9][9];
	while ( (fscanf(fp, "%d %d %d %d %d %d %d %d %d",
					&sudoku[line][0],
					&sudoku[line][1],
					&sudoku[line][2],
					&sudoku[line][3],
					&sudoku[line][4],
					&sudoku[line][5],
					&sudoku[line][6],
					&sudoku[line][7],
					&sudoku[line][8]
					) != EOF)) {
			line+= 1;
	}
	fclose(fp);

	//打印当前数独
	printSudoku(sudoku);

	calcSudoku(sudoku, 0, 1);

}

// 打印二维数组
void
printSudoku(int (*metrics)[9]){
	int i,j;
	for (i=0; i < 9; i++){
		for (j=0; j < 9; j++){
			printf("%d ",metrics[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void
calcSudoku( int (*metrics)[9],  int pos, int value ){

	if ( pos == 81 ){
		printSudoku(metrics);
		return ;
	}


	int row = pos / 9;
	int col = pos % 9;

	int val;
	// 如果为0, 说明此处可以进行修改
	if ( metrics[row][col] == 0 ){
  	    for ( val = 1; val < 10; val++){
			if ( isValidStep(metrics, row, col, val ) ){
		        metrics[row][col] = val;
				calcSudoku( metrics, pos + 1, val );
			}
		    metrics[row][col] = 0;
		}
	} else{
		// 当前记录如果不为0, 说明此处是已填写区域
		// 跳过这个地方
		calcSudoku( metrics, pos + 1, val );
	}
}

/* 分析当前步是否可靠
*/
	bool
isValidStep(int (*metrics)[9], int row, int column, int value)
{
	// 检查行
	if (!checkRow(metrics, row, column, value)) return false;
	// 检查列
	if (!checkColumn(metrics, row, column, value)) return false;
	//  检查9x9 的阵列
	if (!checkGrid(metrics, row, column, value)) return false;

	return true;

}

//对行进行检查, 保持列不变
	bool
checkRow(int (*metrics)[9], int row, int column, int value)
{
	int i ;
	for ( i = 0; i < 9; i++){
		if (metrics[i][column] == value && \
				i != row){
			return false;
		}
	}
	return true;
}

//对列进行检查，保持行不变
	bool
checkColumn(int (*metrics)[9], int row, int column, int value)
{
	int i ;
	for ( i = 0; i < 9; i++){
		if (metrics[row][i] == value &&
				i != column){
			return false;
		}
	}
	return true;
}

// 对当前网格进行检查
	bool
checkGrid(int (*metrics)[9], int row, int column, int value)
{
	int i, j;

	int row_start =  (row / 3) * 3;
	int row_end   =  (row / 3 + 1) * 3;

	int column_start =  (column / 3) * 3;
	int column_end   =  (column / 3 + 1) * 3;

	for (i = row_start ; i < row_end; i++ ){
		for ( j = column_start; j < column_end; j++){
			if ( metrics[i][j] == value && \
					row != i && \
					column != j){
				return false;
			}
		}
	}
	return true;
}
