#pragma once
#include "DrawTarget.h"
#include "Vec2.h"

class Viewport : public DrawTarget
{
public:
	Viewport(DrawTarget& next, RectI rect)
		:
		next(next),
		clip(rect)
	{}
	virtual void Draw(Drawable& obj)
	{
		obj.Transform(Mat3::Translation({(float)clip.left,(float)clip.top}));
		obj.Clip(clip);
		next.Draw(obj);
	}
	int GetWidth() const
	{
		return clip.GetWidth();
	}
	int GetHeight() const
	{
		return clip.GetHeight();
	}
		 
private:
	DrawTarget& next;
	RectI clip;
};