// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
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
#ifndef _H_MODEL_H_
#define _H_MODEL_H_

#include <ray/modhelp.h>

_NAME_BEGIN

class Model;
class EXPORT ModelHandler
{
public:
    virtual ~ModelHandler() noexcept {};

    virtual bool doCanRead(istream& stream) const noexcept = 0;

    virtual bool doLoad(Model& image, istream& stream) noexcept = 0;
    virtual bool doSave(Model& image, ostream& stream) noexcept = 0;
};

class EXPORT Model final
{
public:
    typedef std::shared_ptr<ModelHandler> _Myhandler;

    typedef std::vector<MeshPropertyPtr>      MeshList;
    typedef std::vector<MaterialPropertyPtr>  MaterialList;
    typedef std::vector<TexturePropertyPtr>   TextureList;
    typedef std::vector<AnimationPropertyPtr> AnimList;
    typedef std::vector<LightPropertyPtr>     LightList;
    typedef std::vector<CameraPropertyPtr>    CameraList;

public:
    Model() noexcept;
    Model(const char* filename, ModelType type = MT_UNKNOWN) noexcept;
    Model(const wchar_t* filename, ModelType type = MT_UNKNOWN) noexcept;
    Model(const std::string& filename, ModelType type = MT_UNKNOWN) noexcept;
    Model(const std::wstring& filename, ModelType type = MT_UNKNOWN) noexcept;
    ~Model() noexcept;

    bool load(const char* filename, ModelType type = MT_UNKNOWN) noexcept;
    bool load(const wchar_t* filename, ModelType type = MT_UNKNOWN) noexcept;
    bool load(const std::string& filename, ModelType type = MT_UNKNOWN) noexcept;
    bool load(const std::wstring& filename, ModelType type = MT_UNKNOWN) noexcept;
    bool load(istream& stream, ModelType type = MT_UNKNOWN) noexcept;

    bool save(const char* filename, ModelType type) noexcept;
    bool save(const wchar_t* filename, ModelType) noexcept;
    bool save(const std::string& filename, ModelType type) noexcept;
    bool save(const std::wstring& filename, ModelType type) noexcept;
    bool save(ostream& stream, ModelType type) noexcept;

    void clear() noexcept;

    void addMesh(MeshPropertyPtr mesh)          noexcept;
    void addTexture(TexturePropertyPtr texture) noexcept;
    void addMaterial(MaterialPropertyPtr mat)   noexcept;
    void addAnimtion(AnimationPropertyPtr anim) noexcept;
    void addLight(LightPropertyPtr light)       noexcept;
    void addCamera(CameraPropertyPtr camera)    noexcept;

    MeshList&     getMeshsList()     noexcept;
    TextureList&  getTexturesList()  noexcept;
    MaterialList& getMaterialsList() noexcept;
    AnimList&     getAnimationList() noexcept;
    LightList&    getLightList()     noexcept;
    CameraList&   getCameraList()    noexcept;

    const std::string&  getName()          const noexcept;
    const std::string&  getDirectory()     const noexcept;
    const MeshList&     getMeshsList()     const noexcept;
    const TextureList&  getTexturesList()  const noexcept;
    const MaterialList& getMaterialsList() const noexcept;
    const AnimList&     getAnimationList() const noexcept;
    const LightList&    getLightList()     const noexcept;
    const CameraList&   getCameraList()    const noexcept;

    bool hasMeshes()     const noexcept;
    bool hasMaterials()  const noexcept;
    bool hasLights()     const noexcept;
    bool hasTextures()   const noexcept;
    bool hasCameras()    const noexcept;
    bool hasAnimations() const noexcept;

    void applyProcess(int flags) noexcept;

    bool emptyHandler() const noexcept;
    bool addHandler(_Myhandler handler) noexcept;
    bool removeHandler(_Myhandler handler) noexcept;
    bool find(ModelType type, _Myhandler& handler) const noexcept;
    bool find(istream& stream, _Myhandler& handler) const noexcept;
    bool find(istream& stream, ModelType type, _Myhandler& handler) const noexcept;

private:
    Model& operator=(const Model&) noexcept = delete;
    Model(const Model&) noexcept = delete;

private:

    std::string _name;

    std::string _directory;

    std::uint32_t _flags;

    MeshList _meshes;

    TextureList _textures;

    MaterialList _materials;

    AnimList _animations;

    LightList _lights;

    CameraList _cameras;

    std::vector<_Myhandler> _handlers;
};

_NAME_END

#endif