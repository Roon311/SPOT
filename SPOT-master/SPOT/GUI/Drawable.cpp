#include "Drawable.h"



Drawable::Drawable()
{
	Selected = false;
}

Drawable::~Drawable()
{
}

void Drawable::setGfxInfo(graphicsInfo g)
{
	GfxInfo = g;
}
Drawable::Drawable(const Drawable& CopiedDW)
{
	GfxInfo = CopiedDW.GfxInfo;
	Selected = CopiedDW.Selected;
}
graphicsInfo Drawable::getGfxInfo() const
{
	return GfxInfo;
}

bool Drawable::isSelected() const
{
	return Selected;
}

void Drawable::setSelected(bool sel)
{
	Selected = sel;
}

