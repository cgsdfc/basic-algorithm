#include <vector>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int N; // 磁盘数。
int S; // 条带大小（块）。
int L; // 现存磁盘数。

int bytes; // 一个磁盘的总字节数。
int blocks; // 总块数。
int strips; // 总条块数。

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

// 随便一个合法磁盘的下标。 
int valid;
struct Disk {
	vector<int> bytes;
	Disk() {
	}
	bool Valid() {
		return !this->bytes.empty();
	}
	void Read(char str[], int len) {
		// 读入字节内容。
		bytes.reserve(len/2);
		for (int i=0;i<len;i+=2) {
			// 一次一个字节。
			int val=Byte(str[i], str[i+1]);
			bytes.push_back(val);
		} 
		assert(bytes.size()==len/2);
	}
};

// 最大磁盘数。 
#define MAXN 1005

Disk disk[MAXN];

// 物理地址，磁盘号，条块号，块号。 
//块的地址。 
struct Address {
	int disk;
	int strip; 
	int blk;
	int ByteOff() {
		assert(0<=disk&&disk<N);
		
		//  块的开始的字节位置。
		return (strip*S+blk) * 4; 
	}
};

// 逻辑块号映射到物理块号。 
vector<Address> addrmp;

void InitDisk() {
	// 建立逻辑块号和物理块号的映射。 
	bytes=disk[valid].bytes.size();
	blocks=bytes/4;
	strips=blocks/S;
	
	// 核心逻辑。 
	int p=N-1; // 当前校验条块的位置（在哪个磁盘）。
	// 逐行放入数据，行数是磁盘数，列数是条带数。	
	for (int j=0;j<strips;++j) {
		int loop=N-1; 
		// 从校验条块的下一个开始，依次放入数据。 
		int i=(p+1)%N;
		while (loop--) {
			// 对条带内的块进行编号，映射到逻辑块号。
			for (int k=0;k<S;++k) {
				Address addr;
				addr.disk=i;
				addr.strip=j;
				addr.blk=k;
				addrmp.push_back(addr);
			}
			i=(i+1)%N;
		}
		// 放完了一行，p要变化。 
		// p的变化规律为先从右到左，再从右到左。 
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
	// 修复位于a的坏块并输出。
	memset(blk, 0, sizeof(int)*4);
	for (int i=0;i<N;++i) {
		if (i==a.disk) {
			assert(!disk[i].Valid());
			// 这是坏盘。
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
		// 输入正常的磁盘。
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
	// 查询。
	while (M--) {
		int id; // 逻辑块号。
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
				// 无法修复。 
				puts("-");
			} else {
				Fix(a, ans);
				PrintBlock(ans);
			}
		}
	} 
	return 0;
}
