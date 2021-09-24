#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
4.5.1 ���ֲ��ҵļ����㷨��ģ�塣
1. ���ֲ��ң������Ƿ��������ĳ��������Ԫ�ء�
2. upper-bound���Ͻ磬��һ������x��Ԫ�ص�λ�á�
3. lower-bound���½磬 ��һ�����ڵ���x��Ԫ�ص�λ�á�
4. ������ֲ���ģ�壬Ҫ���ҵ�һ������ĳ������Ԫ�ص�λ�ã�
����upper-boundģ�壬�������ĸļ��ɡ���Ҫ�������һ������ĳ������Ԫ�أ�
��ת��Ϊ��һ��������������λ��-1.
*/

// [left, right], -1 if not found. 0-based index.
int binarySearch(int A[], int left, int right, int x) {
  int mid;
  while (left <= right) {
    mid = (left + right) / 2; // ������������ left+(right-left)/2
    if (A[mid] == x) {
      return mid; // �������š�
    }
    if (A[mid] > x) {
      // ���ȥ
      right = mid - 1;
    } else {
      // �ұ�ȥ
      left = mid + 1;
    }
  }
  return -1;
}

/*
ע�⣬binarySearch���upper/lower-bound�������������
���߲��Ǹ�һ��Ķ��ֲ��ң���Ϊ���̽��Ƹ�Ҳ�������ú��ߡ�
*/

// ��һ������x��Ԫ�ص��±꣬ [0, n]
int upper_bound(int A[], int left, int right, int x) {
  int mid;
  // ע��û�е��ڡ�
  while (left < right) {
    // �ͱ�������ԣ���ߵ�һ�벻���㣬�ұߵ�һ�����������������һ�벢����
    // ���һ�룩��
    mid = (left + right) / 2;
    if (A[mid] > x) {
      // ������������˵���������ұ�����������һ�룬��������Ҫ�ҵ�������������
      // ��һ���������ߵķֽ��ߣ�����Ҫ����ȥ��
      right = mid;
    } else {
      // �е㲻����������˵�����ǻ�����߲������һ�룬����ȥ�ұߡ�
      left = mid + 1;
    }
    // ֱ������ֻ��һ��Ԫ�أ�˵�������Ѿ����˱߽��ߣ�����������������һ�ࡣ
    // left-1 �������һ��С�ڵ���x��Ԫ�ء�
  }
  // ����ģ��������ģ����ǵ�һ�������������±꣬Ҳ�������߷ֽ��߿�����������һ�ࡣ
  return left;
}

// ��һ�����ڵ���x��Ԫ�ص��±꣬[0,n]
int lower_bound(int A[], int left, int right, int x) {
  int mid;
  while (left < right) {
    if (A[mid] >= x) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}

/*
ע�⣬lower/upper-bound���ص��±귶Χ��0-n����������Խ����±꣬���Ա������ж�
�Ƿ�Խ�磬���������������顣
*/

/*
���ֲ���ͨ��ģ�塣��������ĳ�����ĵ�һ��Ԫ�ء�
ע�⣬����������������������Ȳ����㣬Ȼ�����㣬�����ø�ģ�壬�����Ҫ����ʵ�����������
left��right�ĳ�ֵ���븲�����п��ܵ�ȡֵ��
���ģ�岻��������������ң�Ҳ�����ڽ��������⣬����ľ���ָ͹��������Բ�뾶�����Ľ���ֵ��
��Щ�����������ɢ��ȡֵ��Ҳ������˳����ң������ֲ��ҿ������Ч�ʣ������������ȡֵ���������ֲ��ҡ�
*/
int Template(int left, int right) {
  int mid;
  while (left < right) {
    mid = (left + right) / 2;
    if (/* �������� */ 1) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}
