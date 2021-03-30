#include <vector>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int N; // ��������
int S; // ������С���飩��
int L; // �ִ��������

int bytes; // һ�����̵����ֽ�����
int blocks; // �ܿ�����
int strips; // ����������

const int MAXS=40*1024*2+5;
char buf[MAXS];

const char Name[]="0123456789ABCDEF";
 
int Digit(char c) {
	for (int i=0;i<15;++i) {
		if (c==Name[i]) return i;
	} 
	return -1;
}
int Byte(char hi, char low) {
	return Digit(hi)*16+Digit(low);
}

// ���һ���Ϸ����̵��±ꡣ 
int valid;
struct Disk {
	vector<int> bytes;
	Disk() {
	}
	bool Valid() {
		return !this->bytes.empty();
	}
	void Read(char str[], int len) {
		// �����ֽ����ݡ�
		bytes.reserve(len/2);
		for (int i=0;i<len;i+=2) {
			// һ��һ���ֽڡ�
			int val=Byte(str[i], str[i+1]);
			bytes.push_back(val);
		} 
		assert(bytes.size()==len/2);
	}
};

// ���������� 
#define MAXN 1005

Disk disk[MAXN];

// �����ַ�����̺ţ�����ţ���š� 
//��ĵ�ַ�� 
struct Address {
	int disk;
	int strip; 
	int blk;
	int ByteOff() {
		assert(0<=disk&&disk<N);
		
		//  ��Ŀ�ʼ���ֽ�λ�á�
		return (strip*S+blk) * 4; 
	}
};

// �߼����ӳ�䵽�����š� 
vector<Address> addrmp;

void InitDisk() {
	// �����߼���ź������ŵ�ӳ�䡣 
	bytes=disk[valid].bytes.size();
	blocks=bytes/4;
	strips=blocks/S;
	
	// �����߼��� 
	int p=N-1; // ��ǰУ�������λ�ã����ĸ����̣���
	// ���з������ݣ������Ǵ���������������������	
	for (int j=0;j<strips;++j) {
		int loop=N-1; 
		// ��У���������һ����ʼ�����η������ݡ� 
		int i=(p+1)%N;
		while (loop--) {
			// �������ڵĿ���б�ţ�ӳ�䵽�߼���š�
			for (int k=0;k<S;++k) {
				Address addr;
				addr.disk=i;
				addr.strip=j;
				addr.blk=k;
				addrmp.push_back(addr);
			}
			i=(i+1)%N;
		}
		// ������һ�У�pҪ�仯�� 
		// p�ı仯����Ϊ�ȴ��ҵ����ٴ��ҵ��� 
		p--;
		if (p<0) {
			p=N-1;
		} 
	}
}

void PrintBlock(int blk[]) {
	for (int i=0;i<4;++i) {
		printf("%02X", blk[i]);
	}
	puts("");
}

void FindBlk(Address a, int blk[]) {
	for (int i=0;i<4;++i) {
		blk[i]=disk[a.disk].bytes[a.ByteOff() +i];
	}	
}

void PrintAddr() {
	for (int i=0;i<addrmp.size();++i) {
		Address adr=addrmp[i];
		printf("%d: %d %d %d\n", i, adr.disk,adr.strip, adr.blk);
	}
}

void PrintDisk() {
	for (int i=0;i<N;++i) {
		if (disk[i].Valid()) {
			printf("%d:",i);
			for (int j=0;j<bytes;++j) {
				printf(" %02X", disk[i].bytes[j]);
			}
			puts("");
		}
	}
}

void Fix(Address a, int blk[]) {
	// �޸�λ��a�Ļ��鲢�����
	memset(blk, 0, sizeof(int)*4);
	for (int i=0;i<N;++i) {
		if (i==a.disk) {
			assert(!disk[i].Valid());
			// ���ǻ��̡�
			continue; 
		}
		for (int j=0;j<4;++j) {
			blk[j] ^= disk[i].bytes[a.ByteOff() +j];
		}
	}
}

int main(int argc, char** argv) {
	scanf("%d%d%d",&N,&S,&L);
	for (int i=0;i<L;++i) {
		// ���������Ĵ��̡�
		int id;
		scanf("%d%s",&id,buf);
		valid=id;
		disk[id].Read(buf, strlen(buf));
	}
	InitDisk();
//	PrintAddr();
//	PrintDisk();
//	
	bool canfix=(N-L)==1;
	int M;
	scanf("%d", &M);
	// ��ѯ��
	while (M--) {
		int id; // �߼���š�
		scanf("%d",&id);
		int ans[10]={};
		
		if (id >= addrmp.size()) {
			puts("-");
		} else {
			Address a=addrmp[id];
			if (disk[a.disk].Valid()) {
				FindBlk(a, ans);
				PrintBlock(ans);
			} else if (!canfix) {
				// �޷��޸��� 
				puts("-");
			} else {
				Fix(a, ans);
				PrintBlock(ans);
			}
		}
	} 
	return 0;
}
