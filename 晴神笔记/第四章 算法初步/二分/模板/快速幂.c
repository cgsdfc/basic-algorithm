/*
�����ݣ�a^b mod m.
Naive�������Ӷ���O(b)����b�ϴ�ʱ��ʱ��
���ַ��������Ӷ�ʱO(logb)�����ܼ��á�

���ƹ�ʽ��
a^b = a * a^(b-1) if a is odd.
a^b = a^(b/2) * a^(b/2) if a is even.

������������ʵ�֣�Ч������
1. �ݹ�ʵ�֣����ڵ��ƹ�ʽ�� 
2. ����ʵ�֣����ڽ�b���������ƣ����ҵ����ļ���
a^1, a^2, a^4, a^8,  ....
*/

typedef long long LL;

/*
�ݹ�д�������� pow(a, b) % m.
*/ 
LL binaryPow(LL a, LL b, LL m) {
	if (m == 1) return 0; // �κ�������1ȡ�࣬����0. 
	
	if (b == 0) return 1;
	if (b & 1) {
		return a * binaryPow(a, b-1, m) % m;
		// ������b-1 
	} else {
		// ż��������b/2.
		LL mul = binaryPow(a, b/2, m);
		return mul * mul % m; 
	}
} 

/*
����д����
*/
LL IterPow(LL a, LL b, LL m) {
	LL ans=1;
	while (b > 0) {
		if (b & 1) {
			// �����ȡ�� 
			ans = ans * a % m;
		}
		// �����Գˡ� 
		a = a * a % m;
		// ָ�����ơ� 
		b >>= 1;
	}
	return ans;
} 

