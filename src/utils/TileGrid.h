#pragma once
#include <utils\Log.h>

struct TileGrid {

	int* data;
	int size;
	int total;

	TileGrid(int sz) {
		total = sz * sz;
		size = sz;
		data = new int[total];
		for (int i = 0; i < total; ++i) {
			data[i] = 0;
		}
	}

	~TileGrid() {
		delete[] data;
	}

	bool isValid(int x, int y) {
		if (x < 0 || x >= size || y < 0 || y >= size) {
			return false;
		}
		return true;
	}

	bool isUsed(int x, int y) {
		if (isValid(x, y)) {
			int idx = x + y * size;
			return data[idx] == 1;
		}
		return false;
	}

	void toggle(int idx) {
		if (idx >= 0 && idx < total) {
			if (data[idx] == 1) {
				data[idx] = 0;
			}
			else {
				data[idx] = 1;
			}
		}
	}

	void toggle(int x, int y) {
		if (isValid(x, y)) {
			int idx = x + y * size;
			if (data[idx] == 1) {
				data[idx] = 0;
			}
			else {
				data[idx] = 1;
			}
		}
	}

	int adjacents(int xp, int yp) {
		int cnt = 0;
		int sx = xp - 1;
		int sy = yp - 1;
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 3; ++x) {
				if (x != 1 && y != 1) {
					if (isUsed(sx + x, sy + y)) {
						++cnt;
					}
				}
			}
		}
		return cnt;
	}

	int free_adjacents(int xp, int yp, int* ret) {
		int cnt = 0;
		for (int y = -1; y < 2; ++y) {
			for (int x = -1; x < 2; ++x) {
				if (x == 0 && y == 0) {
					continue;
				}
				int idx = (xp + x) + (yp + y) * size;
				if (isValid(xp + x, yp + y)) {
					int idx = (xp + x) + (yp + y) * size;
					if (data[idx] == 0) {
						ret[cnt++] = idx;
					}
				}
			}
		}
		return cnt;
	}
};

struct SimpleGrid {

	int* data;
	int size;
	int total;

	SimpleGrid(int sz) {
		total = sz * sz;
		size = sz;
		data = new int[total];
		for (int i = 0; i < total; ++i) {
			data[i] = 0;
		}
	}

	~SimpleGrid() {
		delete[] data;
	}

	bool isValid(int x, int y) const {
		if (x < 0 || x >= size || y < 0 || y >= size) {
			return false;
		}
		return true;
	}

	bool isUsed(int x, int y) const {
		if (isValid(x, y)) {
			int idx = x + y * size;
			return data[idx] > 0;
		}
		return false;
	}

	bool equals(int x, int y, int v) const {
		if (isValid(x, y)) {
			int idx = x + y * size;
			return data[idx] == v;
		}
		return false;
	}

	int adjacents(int xp, int yp,int type) {
		int cnt = 0;
		if (equals(xp, yp - 1, type)) {
			cnt |= 1;
		}
		if (equals(xp + 1, yp, type)) {
			cnt |= 2;
		}		
		if (equals(xp, yp + 1, type)) {
			cnt |= 4;
		}
		if (equals(xp - 1, yp, type)) {
			cnt |= 8;
		}
		return cnt;
	}

	int adjacents(int xp, int yp) {
		int cnt = 0;
		if (isUsed(xp,yp - 1)) {
			cnt |= 1;
		}
		if (isUsed(xp + 1, yp)) {
			cnt |= 2;
		}
		if (isUsed(xp, yp + 1)) {
			cnt |= 4;
		}
		if (isUsed(xp - 1, yp)) {
			cnt |= 8;
		}
		return cnt;
	}

	const int get(int x, int y) const {
		if (isValid(x, y)) {
			int idx = x + y * size;
			return data[idx];
		}
		return -1;
	}

	void set(int x, int y, int v) {
		if (isValid(x, y)) {
			int idx = x + y * size;
			data[idx] = v;
		}
	}

	int free_adjacents(int xp, int yp, int* ret) {
		int cnt = 0;
		for (int y = -1; y < 2; ++y) {
			for (int x = -1; x < 2; ++x) {
				if (x == 0 && y == 0) {
					continue;
				}
				int idx = (xp + x) + (yp + y) * size;
				if (isValid(xp + x, yp + y)) {
					int idx = (xp + x) + (yp + y) * size;
					if (data[idx] == 0) {
						ret[cnt++] = idx;
					}
				}
			}
		}
		return cnt;
	}

	void debug() {
		LOG << " =================================================";
		char b[32];
		for (int y = 0; y < size; ++y) {
			std::string txt;
			for (int x = 0; x < size; ++x) {
				sprintf_s(b, 32, "%2d ", get(x, y));
				txt.append(b);
			}
			LOG << txt;
		}
	}
};

