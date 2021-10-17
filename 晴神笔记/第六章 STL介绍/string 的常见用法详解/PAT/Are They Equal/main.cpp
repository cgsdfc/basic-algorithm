#include <cassert>
#include <iostream>
#include <string>
using namespace std;

struct Float {
    string frac;
    int exp;

    Float() {}
    bool operator==(Float b) {
        return frac == b.frac && exp == b.exp;
    }

    // ���������0����Ψһ��ʾ��
    void Init0(int N) {
        exp = 0;
        while (N--) {
            frac.push_back('0');
        }
    }
    // �����
    friend ostream& operator<<(ostream& os, Float& f) {
        return os << "0." << f.frac << "*10^" << f.exp;
    }

    /*
    ����ָ����β��������׼��ʽ������������֣�������ȫ��ʾһ����������
    β������Nλ���ڴ˻����Ͻ��бȽϡ�

    ��ȥ��ǰ���㣬Ȼ����弸�������
    1. ���������֣���e=�������ֳ��ȣ�����û�е㣬����û��С����
    2.
    û���������֣��������ֿ���ֱ��û�У�������ȫ�㣬��e=-С���������㣨����һ������Ϊֹ����
    3. ÿ��������涼Ҫ����0����.0, 0 0.0 000 000.000 �ȵȡ�
    0�ı�ʾ��ʽΨһ������Ȼ��ֱ�Ӹ�ֵ��
    */

    Float(string str, int N) {
        // ��ȥ��ǰ���㡣
        while (str.size() && str[0] == '0') {
            str.erase(str.begin());
        }
        if (str.empty()) {
            // ����0.
            Init0(N);
            return;
        }
        if (str[0] == '.') {
            // ��С����
            str.erase(str.begin());
            exp = 0;
            // ɾ����󵽵�һ��������֮���0.
            // exp���Ǹ�����Щ��ĸ�����
            while (str.size() && str[0] == '0') {
                str.erase(str.begin());
                exp--;
            }
            if (str.empty()) {
                // ȥ��0���û���ˣ�˵������0.
                Init0(N);
                return;
            }
            // str ����β���ˣ����ǻ�û�нض�Nλ��
        } else {
            // �����������֡�
            // �������ֵĳ��ȣ�����exp��
            exp = 0;
            int k = 0;
            while (k < str.size() && str[k] != '.') {
                ++k;
                ++exp;
            }
            if (k != str.size()) {
                // ˵���е㡣�ѵ�ɾ����
                str.erase(str.begin() + k);
            }
            // ʣ�µ�str����frac�ˣ��Ͳ�ض�Nλ��
        }
        for (int i = 0; i < N; ++i) {
            if (i < str.size()) {
                frac.push_back(str[i]);
            } else {
                frac.push_back('0');
            }
        }
    }
};

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    int N;
    string s1, s2;

    cin >> N >> s1 >> s2;
    Float a = Float(s1, N);
    Float b = Float(s2, N);
    if (a == b) {
        cout << "YES " << a << "\n";
    } else {
        cout << "NO " << a << " " << b << "\n";
    }
    return 0;
}
