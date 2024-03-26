#include <stdio.h>
#include <conio.h>

int game[20][20] = { { 0, } , }; //2차원 배열의 바둑판을 생성하고 0~19줄 로 총 20줄로 이루어져 있다. 뒤에 {0,}는 모든 요소를 0으로 초기화 한다.

void printTitle();
void updatePlate();
int checkFive(int);
int checkFive2(int, int, int);

int main() {
    int input[2];
    int cache;  //메뉴에서 선택한 값을 입력 받을 변수이다.
    printTitle();   //오목판 위쭉 제목을 출력 하는 것
    printf("▣ 게임 시작 : 1\n▣ 게임 종료 : 0\n☞ 입력 : ");
    scanf_s("%d", &cache);  //메뉴를 선택 받음
    switch (cache) {
    case 0:         // 0 입력시 게임 종료             
        printf("게임 종료.\n");
        return;
        break;
    case 1:         // 1 입력시 게임 시작
        printf("게임을 시작합니다.\n");
        break;

    }
    for (;;) {          // 무한루프. for문 안에 있는 조건을 만족하면 break로 빠져나옴
        system("cls");      //화면에 있는걸 지우는 함수. 헤더파일 #include<windows.h>에 선언되어 있다
        printTitle();       //오목판 제목 출력
        updatePlate();      //오목판 출력
        if (checkFive(2)) {     // 만약 checkFive에서 백돌이 이기면 이쪽으로 들어옴
            printf("백돌 승!\n");
            _getch();
            break;
        }
        printf("흑돌 차례입니다.\n");
        scanf_s("%d %d", &input[0], &input[1]);     //놓을 위치의 오목판 좌표를 입력 받음
        if (input[0] == -1 && input[1] == -1) break;
        game[input[1]][input[0]] = 1;       //해당 오목판에 흑돌 표시
        system("cls");      //'흑돌 차례입니다'와 입력받은 좌표 화면 상에서 지워줌
        printTitle();       // 위에 system("cls"); 때문에 다지워지니까 다시 제목 출력
        updatePlate();      //위와 같은 이유. 오목판 출력
        if (checkFive(1)) {     // 만약 checkFive에서 흑돌일 이기면 이쪽으로 들어옴
            printf("흑돌 승!\n");
            _getch();
            break;
        }
        printf("백돌 차례입니다.\n");
        scanf_s("%d %d", &input[0], &input[1]);     //놓을 위치의 오목판 좌표를 입력 받음
        if (input[0] == -1 && input[1] == -1) break;
        game[input[1]][input[0]] = 2;       // 해당 오목판에 백돌 표시
    }
    printf("게임 종료\n");
    return 0;
}

void printTitle() {     // 오목판 제목
    printf("<오목 omok>\n");
    for (int n = 0; n < 45; n++) {
        printf("-");
    }
    printf("\n");
}

void updatePlate() {        //오목판을 그림
    printf("  ");
    for (int n = 0; n < 20; n++)   //오목판 상단 숫자: 0~19
        if (n > 9) printf("%d", n);     //두 자리 수이면 그대로 출력
        else printf(" %d", n);          //한 자리 수이면 숫자 앞에서 공백을 한개 출력
    printf("\n");
    for (int n = 0; n < 20; n++) {      //세로 숫자와 바둑판을 출력
        if (n > 9) printf("%d", n);     //세로 숫자 출력: 2자리 수이면 그대로 출력
        else printf(" %d", n);      //한자리 수이면 숫자 앞에 공백 출력
        for (int m = 0; m < 20; m++) {      //바둑판을 그린다. 옆으로 20개
            if (game[n][m] == 0) printf("□");       //game 배열이 0이면 빈칸
            else if (game[n][m] == 1) printf("●");  //1이면 검은돌
            else if (game[n][m] == 2) printf("⊙");  //2이면 흰돌
        }
        printf("\n");
    }
}

int checkFive(int color) {      // color: 1: 검은돌, 2: 흰돌 검사
    int cache;
    for (int n = 0; n < 20; n++) {      //바둑판을 한칸씩 검사
        for (int m = 0; m < 20; m++) {
            if (game[n][m] == 0) continue;    // 바둑판에 돌이 놓여있지 않으면 다른 칸 검사
            cache = checkFive2(n, m, color);         //바둑판에 돌이 놓여 있으면 5개가 연속으로 놓여있는지 검사(여기서 각 돌에 대해 check를 호출)
            if (cache == 1) return 1;        //위의 checkFive2 함수의 결과가 1이면 종료
        }
    }
    return 0;
}

int checkFive2(int x, int y, int color) {
    int count = 0;     // 가로 체크
    for (int n = 0; n < 5; n++) {
        if (x + n >= 20) return 0;      // 바둑판의 x좌표(가로) 5개가 안되면 리턴함
        if (game[x + n][y] == color) count++;
    }
    if (count == 5) return 1;
    count = 0;      // 세로 체크
    for (int n = 0; n < 5; n++) {
        if (y + n >= 20) return 0;      // 남은 칸이 5가 안 되면 0을 반환
        if (game[x][y + n] == color) count++;
    }
    if (count == 5) return 1;
    count = 0;      // 대각선(좌상에서 우하방향) 체크
    for (int n = 0; n < 5; n++) {
        if (x + n >= 20) return 0;      // 남은 칸(가로)이 5가 안 되면 0을 반환
        else if (y + n >= 20) return 0;     // 남은 칸(세로)이 5가 안 되면 0을 반환
        if (game[x + n][y + n] == color) count++;
    }
    if (count == 5) return 1;       // 같은 색의 돌이 5개이면 1을 반환
    count = 0;       // 대각선(좌하에서 우상방향) 체크
    for (int n = 0; n < 5; n++) {
        if (x + n >= 20) return 0;      // 남은 칸(가로)이 5가 안 되면 0을 반환
        else if (y - n < 0) return 0;       // 남은 칸(세로)이 5가 안 되면 0을 반환
        if (game[x + n][y - n] == color) count++;       // 같은 색의 돌이면 count 값에 1을 더함
    }
    if (count == 5) return 1;
    return 0;
}