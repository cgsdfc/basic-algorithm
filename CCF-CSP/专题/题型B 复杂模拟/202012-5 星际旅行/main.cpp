#include <cstdio>
#include <cstring>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int N; // N������װ�á�
int M; // M��������

typedef long long ll;

const ll MOD=1000000007;

//#define MAXN (1000000000+5)

/*
ȡģ������
ÿһ�β����󣬽���ȡģ���������֮ǰҲҪȡģ��
*/
 
struct Point {
	ll data[3];
	Point() {
		memset(data, 0, sizeof(data));
	}
};

//Point device[MAXN]; // ����װ�á�

// ����ϴ󣬿��ڶ��ϡ� 
Point* dev;

// ���в�������Ҫ���䡣�Ǳ����䡣 
ll L, R;

// �ۼӲ������������������ۼ�һ�������� 
void Add() {
	ll data[3];
	for (int i=0;i<3;++i) {
		scanf("%lld", &data[i]);
	}
	for (ll i=L;i<=R;++i) {
		for (int j=0;j<3;++j) {
			dev[i].data[j] = (dev[i].data[j]+data[j]) % MOD;
		}
	}
}

// ���˲������������ڵ������һ������ 
void Mult() {
	ll k;
	scanf("%lld", &k);
	for (ll i=L;i<=R;++i) {
		for (int j=0;j<3;++j) {
			dev[i].data[j] = (k * dev[i].data[j]) % MOD;
		}
	}
}

// ���������������ڵ��������xyz���ֻ��� 
void Change() {
	for (ll i=L;i<=R;++i) {
		ll x=dev[i].data[0];
		dev[i].data[0]=dev[i].data[1];
		dev[i].data[1]=dev[i].data[2];
		dev[i].data[2]=x;
	}
}

// ��ѯ�����������ڵ�������ӣ�Ȼ�������롣 
void Query() {
	ll ans=0;
	ll sum[3]={};
	for (int j=0;j<3;++j) {
		for (ll i=L;i<=R;++i) {
			sum[j] = (sum[j] + dev[i].data[j]) % MOD;
		}
	}
	for (int j=0;j<3;++j) {
		ans = (ans + (sum[j]*sum[j]) % MOD) % MOD;
	}
	printf("%lld\n", ans);
}

int main(int argc, char** argv) {
	scanf("%d%d", &N, &M);
	dev=new Point[N+5];
	while (M--) {
		int op;
		scanf("%d%lld%lld", &op, &L, &R);
		switch (op) {
			case 1:
				Add();
				break;
			case 2:
				Mult();
				break;
			case 3:
				Change();
				break;
			case 4:
				Query();
				break;
		}
	}
	return 0;
}
