#pragma once
#include "Vec2.h"
#include "Colors.h"
#include "D3DGraphics.h"
#include <vector>
#include "dxflib\dl_dxf.h"
#include "dxflib\dl_creationadapter.h"
#include "Mat3.h"
#include <memory>

class PolyClosedLoader : public DL_CreationAdapter
{
public:
	PolyClosedLoader(std::string filename)
	{
		auto pDxf = std::make_unique<DL_Dxf>();
		pDxf->in(filename, this);
	}
	virtual void addVertex(const DL_VertexData& data) override
	{
		vertices.push_back({ (float)data.x,-(float)data.y });
	}
	std::vector<Vec2>& GetVertices()
	{
		return vertices;
	}
private:
	std::vector<Vec2> vertices;
};

class PolyClosed
{
public:
	PolyClosed(std::initializer_list<Vec2> vlist, D3DCOLOR color = WHITE)
		:
		vertices(vlist),
		color(color)
	{}
	PolyClosed(std::string filename, D3DCOLOR color = WHITE)
		:
		vertices(std::move(PolyClosedLoader(filename).GetVertices())),
		color(color)
	{}
	void Draw(Vec2 pos, float angle,float scale, D3DGraphics& gfx)
	{
		Mat3 trans = Mat3::Translation(pos) * Mat3::Rotation(angle) * Mat3::Scaling(scale) ;

		for (auto i = vertices.begin(), end = vertices.end()-1; i != end; i++)
		{
			
			gfx.DrawLineClip(trans * *i, trans * *(i + 1), color);
		}
		gfx.DrawLineClip(trans * vertices.back(), trans * vertices.front(), color);
	}
private:
	D3DCOLOR color;
	const std::vector<Vec2> vertices;
};