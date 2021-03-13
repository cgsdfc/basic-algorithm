#include <cstdio>
#include <cstring>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int N; // N个动力装置。
int M; // M个操作。

typedef long long ll;

const ll MOD=1000000007;

//#define MAXN (1000000000+5)

/*
取模算术。
每一次操作后，进行取模，求最后结果之前也要取模。
*/
 
struct Point {
	ll data[3];
	Point() {
		memset(data, 0, sizeof(data));
	}
};

//Point device[MAXN]; // 动力装置。

// 数组较大，开在堆上。 
Point* dev;

// 所有操作都需要区间。是闭区间。 
ll L, R;

// 累加操作，给区间内坐标累加一个增量。 
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

// 倍乘操作，给区间内的坐标乘一个数。 
void Mult() {
	ll k;
	scanf("%lld", &k);
	for (ll i=L;i<=R;++i) {
		for (int j=0;j<3;++j) {
			dev[i].data[j] = (k * dev[i].data[j]) % MOD;
		}
	}
}

// 交换操作，区间内的坐标进行xyz的轮换。 
void Change() {
	for (ll i=L;i<=R;++i) {
		ll x=dev[i].data[0];
		dev[i].data[0]=dev[i].data[1];
		dev[i].data[1]=dev[i].data[2];
		dev[i].data[2]=x;
	}
}

// 查询操作，区间内的坐标相加，然后计算距离。 
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
