#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
����һ���ͺ󣬼�����ǰ����N������վ���Ե��
�취һ��
ȥ������͵ļ���վ������
����е�����ͬ�ģ���ȥ��Զ�Ǹ��� 

��������
ȥ��Զ�Ǹ�����վ���ͣ��������ͬԶ�ģ���ȥ����˵��Ǹ���

��������
ά����ǰ�Ĺ������ͻ���Ǯ����
���ҵ�ǰ�ܵ���ļ���վ������Ŀ�ĵء�
����޷��ﵽ�κεط���������޷����
���򣬼��� ����/���룬���п����ǵ���ü���վ�󣬼���������Ŀ�����
�����ǵ�ǰλ�õ�����վ��λ�á� 
ѡȡ��Сֵ��ȥ�Ǹ�����վ��
��ͱ�֤�ˣ�����ʹ�ÿ�������С�������뾡���󡣱����ҵ����뵱ǰ��Զ��������С�ļ���վ��
*/ 

typedef struct Current {
	double oil; // ��ǰ��ʣ������
	double dis; // ��ǰ���˶�Զ
	double cost; // ��ǰ���˶���Ǯ 
} Current;

typedef struct Station {
	double price;
	double dis;
} Station;

#define MAXN 505

/*
ע�⣬hangzhou�ǳ����ء�
*/ 
Station stations[MAXN];

int CMP(const void*_a, const void*_b) {
	Station* a=_a,*b=_b;
	return a->dis==b->dis? 0 : (a->dis < b->dis ? -1 : 1);
}

/*
	���ż��Ͳ��ԣ�
	�赱ǰ����վ��now���ڵ�ǰ�������ɴﷶΧ���������С�����������ɼ���վA��
	1. �� A Ϊ�գ�˵���޷�ǰ�������max travel distance��
	2. ��A�в��Ҿ���������ͼ۱�now�͵���վx�����ҵ�������now���㹻�� x���ͣ�
		������ǰ�����㹻���üӣ���
		��x�����ڣ����ҵ�A���ͼ���͵�վy������now������Ȼ��ǰ��y��
	�������յ�ʱ�㷨����������ܼ�Ǯ��
	
	������
	1. ÿ�μ��Ͳ��ؼ�������Ϊ��ǰ���Ͳ�һ������ˣ�������Ǽ�����������ǰ��
	ǰ������˵ļ���վ���Ӹ����˵��͵Ļ��ᡣ
	2. ̰�������ڣ�ÿ��Ѱ�Ҽ���վʱ��ѡ���ԭ����Ѱ�Ҹ��͵��ͼۣ������ں��Ƿ�Ҫ
	һ������ʻ�����ľ��롣��Ϊ�����Ǽ��͵Ĵ���Խ��Խ�ã��෴�������վ�ķֲ���Խ������ 
	Խ���ˣ���Ӧ��Ƶ�����ͣ�ʹ�õ�ǰ���͵ĵ�λ�۸���͡�
	3. ÿ��Ѱ����վ�����ڵ�ǰ�����ɴ�ķ�Χ��Ѱ�ң���һ����Ҳ�����׵ģ��ؼ�������Щ�ɴ�
	��վ��ѡ��Ĳ��ԡ�
	4. ��̰��ԭ��2����������ɴ���վ�����ͼ۵��ڵ�ǰ��վ�ģ����ʹ����·�εĳɱ��½����������
	ѡ�񡣲������ڵ�ǰ�ͼ۱Ⱥ������ڲ�����ԭ��1�£��ڵ�ǰ��վ�ӵ��Ͳ�Ӧ��̫�࣬��֤������һվ���ɡ�
	�ɼ���now�ӵ����������������Ľ�������ġ�
	5. ���4��˵����վ�����ڣ����ɴ���վ���ͼ۶���now�󣨻��ߵ���now����
	��now���ͱȺ����ı��ˣ�����Ӧ����now��������ͣ�����Ҫ�������ڿɴ���վ�У���Ҫѡ������ˣ��򲻱䣩����վ��
	6. ��4��������Ͷ����վ�ȵ�ǰ��վ���ˣ���Ӧ��ȥ����Ǹ�����Ϊȥ��Զ����վ����ζ��Ҫ�ڵ�ǰ��վ���󣩶�ӣ�
	������̰��׷��ֲ�����ԭ�� 
	7. ��5��������ж����Сֵ����ô�죿 ��ʱ�벻�������ȼ�����������������֣���������ˣ���ѡȡ��������ġ� 
	8. ע�⣬�ɴ���վ��������Χ������״̬�£���Ϊ����ǰ��Ҫ��now���͵ģ������Լ������������Ų���Ҳ�м���
	�����������˲��ǵ�ǰ������Ϊ������Χ�� 
	*/
	
int main(int argc, char *argv[]) {
	Current cur={0,0,0};
	double Cmax, D, Davg;
	int N;
	int i;
	int now;
	
	freopen("./in2.txt","r",stdin);
	
	scanf("%lf%lf%lf%d",&Cmax,&D, &Davg, &N);
//	
//	printf("Davg %f\n", Davg);
//	
//	printf("D %f\n", D);
	
	for (i=0;i<N;++i) {
		Station s;
		scanf("%lf%lf", &s.price, &s.dis);
		stations[i]=s; 
	}
	/*
	���յ㵱��һ������ļ���վ��ʹ��۸�Ϊ0��
	������������������D����������վ�б����Ų���ѡ����
	*/
	stations[N].dis=D;
	stations[N].price=0; 
	qsort(stations, N+1, sizeof(Station), CMP);
	
	// �ȼ���Ƿ����0�ż���վ����Ϊ��ʼ�͸�û���͡�
	if (stations[0].dis) {
		// ���������ͣ���Ϊ�Ӷ����ͺ���һվ���ͼ��й�ϵ��
		printf("The maximum travel distance = 0.00\n");
		return 0; 
	}
	
	now=0;
	// �������һվ����˵���ܹ������յ㡣 
	while (now < N) {
		double minprice;
		int maxdis=Davg*Cmax; // ������ȥ�ķ�Χ�� 
		int next=-1; // ��һվ�� 
		// ������һվ���������Ų��ԡ�
		int j;
		double oil; // �ӵ�ǰվ����һվ��Ҫ�����͡� 
		
		// ע�⣬�������յ��������վ��������ΪN+1�����һ��վ��N. 
		for (j=now+1;j<=N&&stations[j].dis-stations[now].dis <= maxdis;++j) {
			double price=stations[j].price;
			// ���1���Ҿ�������ģ���С�۸����վ�� 
			if (j==now+1 || price < minprice) {
				next=j;
				minprice=price;
				// ���2���Ҿ�������ģ������ڱ��˵���վ�� 
				if (minprice < stations[now].price) {
					/*
					ע�������2���ڣ������2��һ������С�۸���Ϊ��С�Ŀ����ں��档
					������2�����ڣ����ҵ���һ������С�ģ����Ҵ��ڵ���now���ͼۡ�
					*/ 
					break;
				}
			}
		}
		
//		printf("now %d next %d\n", now, next);
		
		if (next == -1) {
			/*
			������״̬�Ҳ�������վ����������ٿ�һ�����;��롣
			*/ 
			printf("The maximum travel distance = %.2f\n", cur.dis + maxdis);
			return 0;
		}
		
		oil= (stations[next].dis - stations[now].dis) / Davg;
//		printf("dis %f price %f oil %f\n", stations[next].dis-stations[now].dis,
//		stations[now].price, oil);
//		
		if (minprice < stations[now].price) {
			// ���1���ӹ���next���͡�
			if (cur.oil < oil) {
				// Ҫ���͡�
				cur.cost += stations[now].price * (oil - cur.oil); // ����oil�� 
				cur.oil=0; 
			} else {
				// �����͡�
				cur.oil -= oil; 
			}
		} else {
			// ����
			cur.cost += stations[now].price * (Cmax - cur.oil);
			cur.oil = Cmax - oil; 
		}
//		printf("cost %f\n", cur.cost);
		now=next;
	}
	
	printf("%.2f\n", cur.cost); 
	return 0;
}
