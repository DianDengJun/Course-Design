//
// Created by hsing on 2020/11/19.
//

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fstream>
#include "sqlist.h"

using namespace std;

#define setLeft setiosflags(ios::left)

// ��ʼ��һ���յĶ�̬˳���
Status InitSqList(SqList &L, int n) {
    auto listsize{((n / 10) + 1) * 10}; // ȷ��˳����ʼ�ڴ�ռ�ÿռ�
    L.elem = new ElemType[listsize];    // �������ַ��˳����ڴ�
    if (!L.elem)    // �ڴ治��
        return OVERFLOW;
    L.length = 0;   // ��ʱ˳���û��Ԫ�أ�L.lengthΪ0
    L.listsize = listsize;
    return OK;
}

// �����ֿ�
void CreateWarehouse(SqList &L, int n, int sort_way) {
    cout << "��������" << n << "�ֵ��Ը��Ե��ͺš����ۡ�����:(�Կո�ָ�)" << endl;
    // ����n������Ԫ��
    for (int i = 0; i < n; i++)
        cin >> L.elem[i].type >> L.elem[i].price >> L.elem[i].number;
    // ����sort_way�Ըմ�����˳�������
    switch (sort_way) {
        case 1:
            // ���۸�����
            sort(L.elem, L.elem + n, cmp1);
            break;
        case 2:
            // ���۸���
            sort(L.elem, L.elem + n, cmp2);
            break;
        case 3:
            // ����������
            sort(L.elem, L.elem + n, cmp3);
            break;
        case 4:
            // ����������
            sort(L.elem, L.elem + n, cmp4);
            break;
        default:
            break;
    }
    // ����L�Ĳ���
    L.sortWay = sort_way;
    L.length = n;
    L.isInit = true;
}

// ���ļ��������ֿ�
void CreateWarehouse(SqList &L, int n, int sort_way, ifstream &ImportFile) {
    string s;
    // ���ļ�������n������Ԫ��
    for (int i = 0; i < n; i++) {
        ImportFile >> L.elem[i].type >> L.elem[i].price >> L.elem[i].number;
        getline(ImportFile, s);
    }
    // ����sort_way�Ըմ�����˳�������
    switch (sort_way) {
        case 1:
            sort(L.elem, L.elem + n, cmp1);
            break;
        case 2:
            sort(L.elem, L.elem + n, cmp2);
            break;
        case 3:
            sort(L.elem, L.elem + n, cmp3);
            break;
        case 4:
            sort(L.elem, L.elem + n, cmp4);
            break;
        default:
            break;
    }
    // ����L�Ĳ���
    L.sortWay = sort_way;
    L.length = n;
    L.isInit = true;
}

// ��ʾ�ֿ�
void PrintWarehouse(SqList L) {
    if (!L.length)
        cout << "��ǰ�ֿ�û������!" << endl;
    else {
        cout << "��ǰ�ֿ���������:" << endl;
        string sort_way;
        switch (L.sortWay) {
            case 1:
                sort_way = "(���ռ۸�����)";
                break;
            case 2:
                sort_way = "(���ռ۸���)";
                break;
            case 3:
                sort_way = "(������������)";
                break;
            case 4:
                sort_way = "(������������)";
                break;
            default:
                break;
        }
        cout << sort_way << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << setLeft
             << setw(5) << "���"
             << setw(20) << "�ͺ�"
             << setw(15) << "����"
             << setw(15) << "����"
             << endl;
        cout << "-------------------------------------------------------" << endl;
        for (int i = 0; i < L.length; i++)
            cout << setLeft
                 << setw(5) << i + 1
                 << setw(20) << L.elem[i].type
                 << setw(15) << L.elem[i].price
                 << setw(15) << L.elem[i].number
                 << endl;
        cout << "-------------------------------------------------------" << endl;
    }
}

// ���
Status Enter(SqList &L, const Computer &c) {
    // Ѱ�Ҳֿ����Ƿ��Ѿ��к�c.typeͬ���͵ĵ���
    for (int i = 0; i < L.length; i++) {
        if (strcmp(c.type, L.elem[i].type) == 0) {
            if (c.price == L.elem[i].price) {   // ���۸�۸��Ƿ���c.price���
                L.elem[i].number += c.number;
                return OK;
            } else {
                cout << "��ʾ:" << endl;
                showInfo(L.elem[i]);
                return ERROR;
            }

        }
    }

    // ���һ�������͵ĵ���
    if (L.length >= L.listsize) {   // ˳���ռ�ÿռ䲻��
        // �����µĻ���ַ���ڴ�ռ�
        auto *newbase = (ElemType *) realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            return OVERFLOW;
        L.elem = newbase;   // L�Ļ���ַ����Ϊnewbase
        L.listsize += LISTINCREMENT;
    }
    // ����L.sort_way�Բ��뵽˳�����
    int item{L.length}; // ȷ��Ҫ�����λ��
    for (int i = 0; i < L.length; i++) {
        switch (L.sortWay) {
            case 1: {
                if (c.price < L.elem[i].price) {
                    item = i;
                    goto change_sq;
                }
            }
                break;
            case 2: {
                if (c.price > L.elem[i].price) {
                    item = i;
                    goto change_sq;
                }
            }
                break;
            case 3: {
                if (c.number < L.elem[i].number) {
                    item = i;
                    goto change_sq;
                }
            }
                break;
            case 4: {
                if (c.number > L.elem[i].number) {
                    item = i;
                    goto change_sq;
                }
            }
                break;
        }
    }
    change_sq:
    ElemType *q = &L.elem[item];
    // ��q��q�Ժ��Ԫ��ȫ������һλ
    for (ElemType *p = L.elem + L.length - 1; p >= q; p--)
        *(p + 1) = *p;
    // ����Ԫ�ظ���q
    *q = c;
    L.length++;
    return OK;
}

// ����
Status Out(SqList &L, const char *type, int num) {
    // ȷ��Ҫ����Ԫ�ص�λ��
    int item{L.length + 1};
    for (int i = 0; i < L.length; i++) {
        if (strcmp(type, L.elem[i].type) == 0) {
            item = i;
            break;
        }
    }
    // û���ҵ�Ҫ����Ԫ�ص�λ��˵���ڲֿ���û��Ԫ�أ����ش���
    if (item > L.length)
        return -1;

    // ȷ��Ҫ����Ԫ�����п��������Ƿ���Գ���
    if (num < L.elem[item].number) {
        // ��������
        L.elem[item].number -= num;
        return OK;
    } else if (num == L.elem[item].number) {
        // ȫ������
        cout << "��ʾ:" << endl
             << L.elem[item].type << "�ͺŵĵ�����ȫ������!" << endl;

        // ��p��p�Ժ��Ԫ��ȫ������һλ
        for (ElemType *p = &L.elem[item + 1]; p <= &L.elem[L.length - 1]; p++) {
            *(p - 1) = *p;
        }
        L.length--;
        return OK;
    } else {
        // ��治��
        cout << "��ʾ:" << endl;
        showInfo(L.elem[item]);
        return ERROR;
    }
}

// �̵�ֿ�
void Check(SqList L) {
    int numSum{0};
    double priceSum{0.0}, priceMax{L.elem[0].price}, priceMin{L.elem[0].price}, priceAverage{0.0};
    vector<char *> priceMaxComputer;    // �洢�۸���ߵĵ��Ե�������
    vector<char *> priceMinComputer;    // �洢�۸���͵ĵ��Ե�������

    if (!L.length) {
        cout << "��ǰ�ֿ�û������!" << endl;
    } else {
        // ���������ܽ���߼ۡ���ͼ�
        for (int i = 0; i < L.length; i++) {
            numSum += L.elem[i].number;
            priceSum += L.elem[i].price * L.elem[i].number;
            priceMax = max(priceMax, L.elem[i].price);
            priceMin = min(priceMin, L.elem[i].price);
        }
        // ��¼�۸���ߡ���͵ĵ���������
        for (int i = 0; i < L.length; i++) {
            if (L.elem[i].price == priceMax)
                priceMaxComputer.push_back(L.elem[i].type);
            if (L.elem[i].price == priceMin)
                priceMinComputer.push_back(L.elem[i].type);
        }
        // ��ƽ����
        priceAverage = priceSum / numSum;
        // �����Ϣ
        cout << "�̵���������" << endl
             << "���Ե���̨��: " << numSum << endl
             << "���Ե��ܽ��: " << priceSum << endl
             << "���Ե���߼�: " << priceMax << endl
             << "           + ��Ӧ���ͺ���: ";
        for (const auto &c:priceMaxComputer)
            cout << c << "\t";
        cout << endl;
        cout << "���Ե���ͼ�: " << priceMin << endl
             << "           + ��Ӧ���ͺ���: ";
        for (const auto &c:priceMinComputer)
            cout << c << "\t";
        cout << endl;
        cout << "���Ե�ƽ���۸�: " << priceAverage << endl;
    }
}

// computer����ʽ�����۸�����
bool cmp1(const Computer &a, const Computer &b) {
    return a.price < b.price;
}

// computer����ʽ�����۸���
bool cmp2(const Computer &a, const Computer &b) {
    return a.price > b.price;
}

// computer����ʽ������������
bool cmp3(const Computer &a, const Computer &b) {
    return a.number < b.number;
}

// computer����ʽ������������
bool cmp4(const Computer &a, const Computer &b) {
    return a.number > b.number;
}

// ����ֿ����ݵ��ļ���
void output(SqList L, const string &filename) {
    // ��������ļ���filename.txt
    ofstream OutFile(filename + ".txt");
    // ����ļ�ͷ�������´�����ʱʶ���ļ�
    OutFile << "Computer Warehouse Data" << endl;
    if (!L.length)
        OutFile << "no data" << endl;
    else {
        OutFile << "The information is as follows:" << endl;
        switch (L.sortWay) {
            case 1:
                OutFile << "Sort Way: 1 (Ascending by price)" << endl;
                break;
            case 2:
                OutFile << "Sort Way: 2 (Descending by price)" << endl;
                break;
            case 3:
                OutFile << "Sort Way: 3 (Ascending by number)" << endl;
                break;
            case 4:
                OutFile << "Sort Way: 4 (Descending by number)" << endl;
                break;
            default:
                break;
        }
        OutFile << "Total Type: " << L.length << endl;

        // ���������Ϣ
        for (int i = 0; i < L.length; i++)
            OutFile << L.elem[i].type << " "
                    << L.elem[i].price << " "
                    << L.elem[i].number
                    << endl;
        // �ر��ļ�
        OutFile.close();
    }
}

// ���ⲿ�ļ��������ݵ��ֿ�
Status Import(SqList &L, const string &filename) {
    // �������������ļ���filename.txt
    ifstream InFile;
    InFile.open(filename + ".txt");
    // ����ļ��Ƿ����
    if (!InFile.is_open()) {
        InFile.close();
        return ERROR;
    }
    auto sort_way{0}, n{0};
    // ����ļ�ͷ�Ƿ���ȷ��ͬʱ���زֿ�����ʽ��������������
    switch (getFileHead(InFile, sort_way, n)) {
        case OK:
            break;
        case 2:
            return 2;
        case 3:
            return 3;
    }
    if (!InitSqList(L, n))
        return OVERFLOW;
    else
        // ���ú���CreateWarehouse�����ֿ�
        CreateWarehouse(L, n, sort_way, InFile);
    InFile.close();
    return OK;
}

// ����ⲿ�ļ�ͷ
Status getFileHead(ifstream &ImportFile, int &sort_way, int &total_type) {
    string s;
    getline(ImportFile, s);
    if (s != "Computer Warehouse Data") {
        ImportFile.close();
        return 2;
    }
    getline(ImportFile, s);
    if (s == "no data") {
        ImportFile.close();
        return 3;
    }
    if (s != "The information is as follows:") {
        ImportFile.close();
        return 2;
    }
    ImportFile >> s;
    if (s != "Sort") {
        ImportFile.close();
        return 2;
    }
    ImportFile >> s;
    if (s != "Way:") {
        ImportFile.close();
        return 2;
    }

    ImportFile >> sort_way;
    if (sort_way < 1 || sort_way > 4)
        return 2;
    getline(ImportFile, s);

    ImportFile >> s;
    if (s != "Total") {
        ImportFile.close();
        return 2;
    }
    ImportFile >> s;
    if (s != "Type:") {
        ImportFile.close();
        return 2;
    }

    ImportFile >> total_type;
    if (total_type < 1)
        return 2;

    getline(ImportFile, s);
    return OK;
}

// ��ȡ������Ϣ
void getInfo(SqList L, const char *type) {
    // ȷ��Ҫ���ҵĵ��Ե�Ԫ��λ��
    int item{L.length + 1};
    for (int i = 0; i < L.length; i++) {
        if (strcmp(type, L.elem[i].type) == 0) {
            item = i;
            break;
        }
    }
    if (item > L.length)
        cout << "û���ҵ�" << type << "�ͺŵĵ���" << endl;
    else {
        cout << "��Ϣ����:" << endl;
        showInfo(L.elem[item]);
    }
}

// ��ʾ������Ϣ
void showInfo(Computer c) {
    cout << "--------------------------------------------------" << endl
         << setLeft << setw(20) << "�ͺ�" << setw(15) << "����" << setw(15) << "���п������" << endl
         << "--------------------------------------------------" << endl
         << setLeft << setw(20) << c.type << setw(15) << c.price << setw(15) << c.number << endl
         << "--------------------------------------------------" << endl;
}