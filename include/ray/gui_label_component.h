// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2014.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#ifndef _H_GUI_LABEL_COMPONENT_H_
#define _H_GUI_LABEL_COMPONENT_H_

#include <ray/gui_behaviour_component.h>
#include <ray/gui_layout_component.h>
#include <ray/font_bitmap.h>

_NAME_BEGIN

class GUILabelComponent : public GUIBehaviourComponent
{
	__DeclareSubClass(GUILabelComponent, GUIBehaviour)
public:
	GUILabelComponent() noexcept;
	~GUILabelComponent() noexcept;

	virtual GameComponentPtr clone() const except;

	virtual void setText(const std::string& text) noexcept;
	virtual const std::string& getText() const noexcept;

	virtual void setFont(const std::string& text) noexcept;
	virtual const std::string& getFont() const noexcept;

	virtual void setMaterial(MaterialPtr material) noexcept;
	virtual MaterialPtr getMaterial() const noexcept;

	virtual void buildUIControl(GUILayoutComponentPtr skin) noexcept;
	virtual GameComponentPtr hitTest(const Vector3& raycast) noexcept;

	virtual void load(iarchive& reader) noexcept;
	virtual void save(oarchive& write) noexcept;

protected:

	void _buildMaterial() noexcept;
	void _buildFontBitmap() noexcept;

protected:

	void onActivate() except;

private:

	Vector4 _color;

	std::string _text;
	std::string _fontName;
	std::string _materialName;

	TexturePtr _texture;
	MaterialPtr _material;

	std::uint16_t _fontSize;
	std::uint16_t _bitmapSize;

	std::map<wchar_t, std::shared_ptr<FontGlyph>> _glyphs;
};

_NAME_END

#endif