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
	bool steep = abs(p1.y - p0.y) > abs(p1.x - p0.x);//判断哪个方向是最大步长
	if (steep) {//若y方向是最大步长，那么我们将坐标中的xy对换，在最后存储点的时候反过来存储
		swap(p0.x, p0.y);
		swap(p1.x, p1.y);
	}
	if (p0.x>p1.x)//为了简化起见，我们画的点都是从左到右依次增大的
	{
		swap(p0.x, p1.x);
		swap(p0.y, p1.y);
	}
	int dx = p1.x - p0.x;//因为前面的调换，这里肯定是非负数
	int dy = abs(p1.y - p0.y);
	int d = -dx;//d的初值为-dx---d在推导的最开始为0，相当于是d先加上-0.5再乘以2dx
	int y = p0.y;
	vector<point> ans;
	for (int x = p0.x; x <= p1.x; x++) {
		if (steep)//如前面所说，如果y方向是最大步长，就需要反过来存储
			ans.push_back(point(y, x));
		else
			ans.push_back(point(x, y));
		d += 2 * dy;//d更新---最开始的更新是+k(k也是就dy/dx),由于前面初值的变化，这里需要乘以2dx也就变成了2dy。（-0.5只需要在初值是考虑，后面不需要考虑，也不知道咋说，就是加减和乘除的区别）
		if (d > 0) {//如果d>0,也就说明更偏向于y+1这个点，同时需要给d-1，由于初值的变换，这里同样需要乘以2dx
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
