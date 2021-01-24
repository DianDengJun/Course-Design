#include "Maze.h"
#include "Stack.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using Status = bool;

// �˵�����
int menu();

// �ֶ��������ļ������Թ�
void InputMaze();

// �����Թ�
void InputMaze(Maze &maze, std::istream &In);

// �ǵݹ�����
Status MazePath(Maze &maze, Pos start, Pos end);

// �ݹ�����
void ReMazepath(Pos start, Pos end);

/**
 * @brief �����Թ�
 * @param maze �Թ����󣬽����뵽�˶�����
 * @param In �����󣬴Ӵ����������뵽maze��
*/
void InputMaze(Maze &maze, std::istream &In);

// ��һ���ڷ���
Pos NextPos(Pos curpos, int i);

// ��ӡ�Թ�·��ͼ
void PrintMaze(Maze &maze);

int dir[][2] = {{0, 1},   // ��
                {1, 0},   // ��
                {0, -1},  // ��
                {-1, 0}}; // ��
Maze maze;                // �Թ�����
Stack<Block> S;           // ջ����
int count = 0;            // �ݹ�����·������

int main() {
    while (true) {
        switch (menu()) {
            case 1: {
                InputMaze();
                Pos start, end;
                cout << "�������λ��:";
                cin >> start.i >> start.j;
                cout << "�������λ��:";
                cin >> end.i >> end.j;
                auto flag = MazePath(maze, start, end);
                if (flag) {
                    PrintMaze(maze);
                } else {
                    cout << "*****    ���Թ��޷�������ߵ��յ㡣   ******\n";
                }
            } break;
            case 2: {
                InputMaze();
                Pos start, end;
                cout << "�������λ��:";
                cin >> start.i >> start.j;
                cout << "�������λ��:";
                cin >> end.i >> end.j;
                ReMazepath(start, end);
            } break;
            case 0:
                cout << "���������ллʹ�ã�" << endl;
                exit(0);
        }
    }
    return 0;
}

int menu() {
    auto sn{0};
    cout << endl
         << "<---------------��ʾ�˵�---------------" << endl
         << "1. �ǵݹ������Թ�ͨ··��" << endl
         << "2. �ݹ������Թ�ͨ··��" << endl
         << "0. ��������" << endl
         << "---------------��ʾ�˵�--------------->" << endl
         << "����0-2:";
    while (true) {
        cin >> sn;
        if (sn < 0 || sn > 2)
            cout << "���������ѡ0��2:" << endl;
        else
            break;
    }
    return sn;
}

void InputMaze() {
    auto way{0};
    cout << "0�ֶ�����,1���ļ�����:";
    while (true) {
        cin >> way;
        if (way < 0 || way > 1)
            cout << "���������������0��1:" << endl;
        else
            break;
    }
    if (way) {
        std::string filename;
        cout << "�����ļ���:";
        cin >> filename;
        std::ifstream InputFile;
        InputFile.open(filename);
        if (!InputFile.is_open()) {
            std::cerr << "û���ҵ��ļ�" << filename << endl;
            exit(1);
        }
        InputMaze(maze, InputFile);
        InputFile.close();
    } else {
        cout << "�����������������Թ�����:" << endl;
        InputMaze(maze, std::cin);
    }
}

void InputMaze(Maze &maze, std::istream &In) {
    auto row{0}, col{0};
    In >> row >> col;
    maze.setRow(row);
    maze.setCol(col);
    char value;
    for (int i = 0; i < maze.getRow(); i++) {
        for (int j = 0; j < maze.getRow(); j++) {
            In >> value;
            maze.setMapValue(Pos{i, j}, value);
        }
    }
}

Status MazePath(Maze &maze, Pos start, Pos end) {
    Stack<Block> S;     // ʵ����һ��ջ����
    Pos curpos = start; // ��ǰ����
    Block e;            // ʵ����һ��ͨ�������
    int curstep = 1;    // ̽������

    do {
        if (maze.canPass(curpos)) {         // ��ǰλ�ÿ�ͨ��
            maze.setMapValue(curpos, '*');  // �����㼣
            e.setBlock(curstep, curpos, 0); // ���ô���ջ��ͨ����

            S.push(e); // ��ջ
            // �����յ�(����)
            if (curpos == end) {
                S.print();
                return true;
            }
            // ��һλ���ǵ�ǰλ�õĶ���
            curpos = NextPos(curpos, 0);
            // ̽����һ��
            curstep++;
        } else { // ��ǰ����ͨ��
            if (!S.isEmpty()) {
                S.pop(e); // ��ջ
                while (e.di == 3 && !S.isEmpty()) {
                    if (maze.getMapValue(e.seat) != '@')
                        maze.setMapValue(e.seat, '.');
                    S.pop(e); // ��ջ������һ��
                }
                if (e.di < 3) {
                    e.di++; // ����һ������̽��
                    S.push(e);
                    // �趨��ǰλ���Ǹ��·����ϵ����ڿ�
                    curpos = NextPos(e.seat, e.di);
                }
            }
        }
    } while (!S.isEmpty());
    return false;
}

void ReMazepath(Pos start, Pos end) {
    if (start == end) {
        // �����յ�
        maze.setMapValue(start, '*');
        S.push(Block{S.getSize() + 1, start, 1});
        cout << "�ҵ���" << ++count << "��ͨ·:" << endl;
        S.print();
        PrintMaze(maze);
        // �˳�ջ������һ��·��
        S.pop();
        // �ָ�ԭֵ
        maze.setMapValue(start, '.');
    } else {
        if (maze.canPass(start)) {
            int di = 0;
            while (di < 4) {
                // ���뵱ǰ����
                S.push(Block{S.getSize() + 1, start, di});
                // ��һλ��
                Pos next = NextPos(start, di);
                // ���������߶�
                maze.setMapValue(start, '*');
                // �ݹ�
                ReMazepath(next, end);
                // �˳�ջ��������Ԫ��
                S.pop();
                // �ָ�ԭֵ
                maze.setMapValue(start, '.');
                di++;
            }
        }
    }
}

Pos NextPos(Pos curpos, int i) {
    Pos ret = curpos;
    // ������
    ret.i += dir[i][0];
    ret.j += dir[i][1];
    return ret;
}

void PrintMaze(Maze &maze) {
    std::cout << "�Թ�·��ͼ: \n";
    for (int i = 0; i < maze.getRow(); i++) {
        std::cout << "      ";
        for (int j = 0; j < maze.getCol(); j++) {
            std::cout << std::setw(2) << maze.getMapValue(Pos{i, j});
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}