#include <iostream>
#include <cstdlib>

const int N = 16;

#define LEFT(x) ((x)*2 + 1)
#define RIGHT(x) ((x)*2 + 2)
#define PARENT(x) (((x) - 1) / 2)

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void insert(int *heap, const int value, const int tail) {
	int now = tail;
	heap[now] = value;
	for (;;) {
		if (now <= 0)
			break;

		const int parent = PARENT(now);
		if (heap[parent] > heap[now])
			break;

		swap(&heap[parent], &heap[now]);
		now = parent;
	}
}

int remove_top(int *heap, const int tail) {
	// 根と末尾要素を入れ替える
	swap(&heap[0], &heap[tail]);

	// 根から下に降りていく（ヒープ構造の維持）
	int now = 0;
	for (;;) {
		const int left_child_index = LEFT(now);
		const int right_child_index = RIGHT(now);
		int next_index = -1;

		if (left_child_index >= tail) // 子供なし
			break;
			
		if (right_child_index >= tail) { 
			// 左の子のみ
			next_index = left_child_index;
		} else { 
			// 両方の子
			if (heap[left_child_index] > heap[right_child_index])
				next_index = left_child_index;
			else
				next_index = right_child_index;
		}

		if (heap[now] < heap[next_index]) {
			swap(&heap[now], &heap[next_index]);
			now = next_index;
		} else
			break;
	}

	return heap[tail];
}

void sort(int *heap, const int length) {
	// ヒープ木から根の要素を取得しつつ削除する
	for (int tail = N - 1; tail >= 0; --tail) {
		remove_top(heap, tail);
	}
}

int main() {
	int data[N];

	for (int i = 0; i < N; ++i) {
		data[i] = rand() % 32;
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;

	// ヒープ木作成
	int heap[N];
	for (int i = 0; i < N; ++i) {
		insert(heap, data[i], i);
	}

	for (int i = 0; i < N; ++i) {
		std::cout << heap[i] << " ";
	}
	std::cout << std::endl;

	// 上の要素を除外し続ける
	/*
	for (int i = N - 1; i >= 0; --i) {
		std::cout << remove_top(heap, i) << " ";
	}
	*/

	// ソート
	sort(heap, N);
	
	for (int i = 0; i < N; ++i) {
		std::cout << heap[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}