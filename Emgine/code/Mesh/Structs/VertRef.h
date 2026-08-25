#pragma once

struct VertRef
{
	VertRef(int v, int vt, int vn) : v(v), vt(vt), vn(vn) {}
	int v, vt, vn;
};