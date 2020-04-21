#include<iostream>
#include<vector>
using namespace std;

struct point {
	int x, y;
	point(int a, int b) {
		x = a;
		y = b;
	}

};

vector<point> DDA(point p0, point p1) {
	int dx, dy, eps;
	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	if (abs(dx) < abs(dy))//斜率绝对值大于1，y方向为最大位移方向
		eps = abs(dy);
	else
		eps = abs(dx);
	float xIncrease = (float)dx / eps;//斜率k，若x方向为最大位移方向，那么这个值就等于1，反之为k
	float yIncrease = (float)dy / eps;
	vector<point> ans;
	float x = p0.x;
	float y = p0.y;
	for (int i = 0; i <= eps; i++) {
		ans.emplace_back(point((int)(x + 0.5), (int)(y + 0.5)));//四舍五入=》加0.5再向下取整
		x += xIncrease;
		y += yIncrease;
	}
	return ans;
}

vector<point> Bresenham(point p0, point p1) {
	bool steep = abs(p1.y - p0.y) > abs(p1.x - p0.x);
	if (steep) {
		swap(p0.x, p0.y);
		swap(p1.x, p1.y);
	}
	if (p0.x>p1.x)
	{
		swap(p0.x, p1.x);
		swap(p0.y, p1.y);
	}
	int dx = p1.x - p0.x;
	int dy = abs(p1.y - p0.y);
	int d = -dx;
	int ystep = p0.y < p1.y ? 1 : -1;
	int y = p0.y;
	vector<point> ans;
	for (int x = p0.x; x <= p1.x; x++) {
		if (steep)
			ans.push_back(point(y, x));
		else
			ans.push_back(point(x, y));
		d += 2 * dy;
		if (d > 0) {
			y += 1;
			d -= 2 * dx;
		}
	}
	return ans;
}

int main() {
	point p0(0, 0), p1(8, 5);
	vector<point> ans = DDA(p1, p0);
	for (point p : ans)
		cout << p.x << "," << p.y << endl;
	return 0;
}