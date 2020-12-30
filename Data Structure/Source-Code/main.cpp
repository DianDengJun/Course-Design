#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
#include "sqlist.h"

using namespace std;

/********************��������********************/
// �˵�
int menu();

// ����from��end��Χ�ڵ�����
int input_number(int from, int end);

// �������from������
int input_number(int from);

/********************��������********************/

// ������
int main() {
    cout << "��ӭʹ�õ��Բֿ����ϵͳ��" << endl;

    // ����˳���L
    SqList L;

    // ���ݲ˵�ѡ��ʵ�ֶ�Ӧ����
    while (true) {
        switch (menu()) {
            // ��ʼ���ֿ�
            case 1: {
                // ���ֿ��Ƿ��Ѿ�����
                if (L.isInit) {
                    cout << "�ֿ��Ѵ�����!" << endl;
                    break;
                }

                cout << "ѡ�񴴽��ֿ�ķ�ʽ" << endl
                     << "1.�ֶ�����  2.���ⲿ�ļ�����" << endl
                     << "ѡ��1-2:";
                auto sn = input_number(1, 2);

                if (sn == 1) {  // �ֶ������ֿ�
                    cout << "��������Ե�������:";
                    auto n = input_number(1);

                    if (!InitSqList(L, n)) {
                        cout << "�����ֿ�ʧ��!" << endl
                             << "ԭ��: �ڴ治�㡣" << endl;
                    } else {
                        cout << "������ֿ��������Ҫ��ʽ" << endl
                             << "1. ���۸����� 2. ���۸���" << endl
                             << "3. ���������� 4. ����������" << endl
                             << "ѡ��1-4:";
                        auto select = input_number(1, 4);
                        CreateWarehouse(L, n, select);
                        cout << "�����ֿ�ɹ�!" << endl
                             << "������ѡ��˵�2����ʾ�ֿ�" << endl;
                    }
                } else { // ���ļ������ֿ�
                    cout << "�������ļ���(�����ļ�����׺):";
                    string filename;
                    cin >> filename;
                    switch (Import(L, filename)) {
                        case OK: {
                            string sort_way;
                            cout << "����ɹ�!" << endl;
                            switch (L.sortWay) {
                                case 1:
                                    sort_way = "���ռ۸���������";
                                    break;
                                case 2:
                                    sort_way = "���ռ۸�������";
                                    break;
                                case 3:
                                    sort_way = "����������������";
                                    break;
                                case 4:
                                    sort_way = "����������������";
                                    break;
                            }
                            cout << "�����ļ�Ҫ��: �ֿ�����" + sort_way << endl;
                            cout << "������ѡ��˵�2����ʾ�ֿ⡣" << endl;
                        }
                            break;
                        case ERROR:
                            cout << "����ʧ��!" << endl
                                 << "ԭ��: û��" << filename << ".txt����ļ� / " << filename << ".txt�ļ��޷��򿪡�" << endl;
                            break;
                        case 2:
                            cout << "����ʧ��!" << endl
                                 << "ԭ��: " << filename << ".txt�ļ����ݲ�����Ҫ��" << endl;
                            break;
                        case 3:
                            cout << "����ʧ��!" << endl
                                 << "ԭ��: " + filename + ".txt�ļ�û�����ݡ�" << endl;
                            break;
                        case OVERFLOW:
                            cout << "����ʧ��!" << endl
                                 << "ԭ��: �ڴ治�㡣" << endl;
                            break;
                    }
                }
            }
                break;

            // ��ʾ�ֿ�
            case 2:
                // ���ֿ��Ƿ��Ѿ�����
                if (!L.isInit) {
                    cout << "�ֿ⻹δ��ʼ��!" << endl;
                    break;
                }
                PrintWarehouse(L);
                break;

            // ���
            case 3: {
                // ���ֿ��Ƿ��Ѿ�����
                if (!L.isInit) {
                    cout << "�ֿ⻹δ��ʼ��!" << endl;
                    break;
                }
                cout << "������Ҫ���ĵ����ͺš����ۡ�����:" << endl;
                Computer c;
                cin >> c.type >> c.price >> c.number;
                switch (Enter(L, c)) {
                    case OK:
                        cout << "���ɹ�!" << endl;
                        break;
                    case ERROR:
                        cout << "�޷���⣡" << endl
                             << "ԭ��: �����" << c.type << "�ͺŵ��Եĵ���" << c.price << "�����е��۲�һ�¡�" << endl;
                        break;
                    case OVERFLOW:
                        cout << "���ʧ��!" << endl
                             << "ԭ��: �ڴ治�㡣" << endl;
                        break;
                }
            }
                break;

            // ����
            case 4: {
                // ���ֿ��Ƿ��Ѿ�����
                if (!L.isInit) {
                    cout << "�ֿ⻹δ��ʼ��!" << endl;
                    break;
                }
                cout << "������Ҫ����ĵ����ͺš�����:" << endl;
                char type[50];
                int num{0};
                cin >> type >> num;
                if (num <= 0) {
                    cout << "�޷�����!" << endl
                         << "ԭ��: ��������С�ڵ���0" << endl;
                    break;
                }
                switch (Out(L, type, num)) {
                    case OK:
                        cout << "����ɹ�!" << endl;
                        break;
                    case -1:
                        cout << "����ʧ��!" << endl
                             << "ԭ��: " << type << "�ͺŵĵ��Բ��ڲֿ���!" << endl;
                        break;
                    case ERROR:
                        cout << "�޷�����!" << endl
                             << "ԭ��: Ҫ���������" << num << "���ڿ���е�������" << endl;
                        break;
                }
            }
                break;

            // ��ѯ
            case 5: {
                // ���ֿ��Ƿ��Ѿ�����
                if (!L.isInit) {
                    cout << "�ֿ⻹δ��ʼ��!" << endl;
                    break;
                }
                cout << "������Ҫ��ѯ�ĵ����ͺ�:";
                char type[50];
                cin >> type;
                getInfo(L, type);
            }
                break;

            // �̵�ֿ�
            case 6:
                // ���ֿ��Ƿ��Ѿ�����
                if (!L.isInit) {
                    cout << "�ֿ⻹δ��ʼ��!" << endl;
                    break;
                }
                Check(L);
                break;

            // �Բֿ���������
            case 7: {
                // ���ֿ��Ƿ��Ѿ�����
                if (!L.isInit) {
                    cout << "�ֿ⻹δ��ʼ��!" << endl;
                    break;
                }
                cout << "������Ҫ���¶Բֿ��������Ҫ��ʽ" << endl
                     << "1. ���۸����� 2. ���۸���" << endl
                     << "3. ���������� 4. ����������" << endl
                     << "ѡ��1-4:";
                auto select = input_number(1, 4);
                switch (select) {
                    case 1:
                        sort(L.elem, L.elem + L.length, cmp1);
                        break;
                    case 2:
                        sort(L.elem, L.elem + L.length, cmp2);
                        break;
                    case 3:
                        sort(L.elem, L.elem + L.length, cmp3);
                        break;
                    case 4:
                        sort(L.elem, L.elem + L.length, cmp4);
                        break;
                    default:
                        break;
                }
                L.sortWay = select;
                cout << "��������ɹ�!" << endl;
            }
                break;

            // �����ֿ����ݵ��ļ�
            case 8: {
                // ���ֿ��Ƿ��Ѿ�����
                if (!L.isInit) {
                    cout << "�ֿ⻹δ��ʼ��!" << endl;
                    break;
                }
                cout << "������Ҫ������ļ���(�����ļ�����׺):";
                string filename;
                cin >> filename;
                output(L, filename);
                cout << "�ѳɹ����ֿ����ݱ����ڳ��������ļ��е�" << filename << ".txt��" << endl;
            }
                break;

            // ��������
            case 0:
                cout << "���������ллʹ�ã�" << endl;
                system("Pause");
                exit(0);
        }
    }
}

// �˵�
int menu() {
    cout << endl
         << "<---------------��ʾ�˵�---------------" << endl
         << "1. ��ʼ���ֿ�" << endl
         << "2. ��ʾ�ֿ�" << endl
         << "3. ���" << endl
         << "4. ����" << endl
         << "5. ��ѯ" << endl
         << "6. �̵�ֿ�" << endl
         << "7. ���¶Բֿ�����" << endl
         << "8. �����ֿ����ݵ��ļ�" << endl
         << "0. ��������" << endl
         << "---------------��ʾ�˵�--------------->" << endl
         << "����0-8:";
    return input_number(0, 8);
}

// ����from��end��Χ�ڵ�����
int input_number(int from, int end) {
    auto select{0};
    string input;
    regex r("[0-9]*");  // ������ʽ:����0-9�����Գ��ֶ��
    while (true) {
        cin >> input;
        bool isNumber = regex_match(input,r);
        if (!isNumber)  // ���input��������ʽƥ��
            cout << "�����������������" << from << "-" << end << ":";
        else {
            select = atoi(input.c_str());
            if (select < from || select > end)
                cout << "���������������" << from << "-" << end << ":";
            else
                break;
        }
    }
    return select;
}

// �������from������
int input_number(int from) {
    auto number{0};
    string input;
    regex r("[0-9]*");  // ������ʽ:����0-9�����Գ��ֶ��
    while (true) {
        cin >> input;
        bool isNumber = regex_match(input,r);
        if (!isNumber)  // ���input��������ʽƥ��
            cout << "�����������������:";
        else {
            number = atoi(input.c_str());
            if (number < from)
                cout << "���������������:";
            else
                break;
        }
    }
    return number;
}