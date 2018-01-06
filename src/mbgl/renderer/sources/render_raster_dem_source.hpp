#pragma once

#include <mbgl/renderer/render_source.hpp>
#include <mbgl/renderer/tile_pyramid.hpp>
#include <mbgl/style/sources/raster_dem_source_impl.hpp>

namespace mbgl {

class RenderRasterDEMSource : public RenderSource {
public:
    RenderRasterDEMSource(Immutable<style::RasterDEMSource::Impl>);

    bool isLoaded() const final;

    void update(Immutable<style::Source::Impl>,
                const std::vector<Immutable<style::Layer::Impl>>&,
                bool needsRendering,
                bool needsRelayout,
                const TileParameters&) final;

    void startRender(PaintParameters&) final;
    void finishRender(PaintParameters&) final;

    std::vector<std::reference_wrapper<RenderTile>> getRenderTiles() final;

    std::unordered_map<std::string, std::vector<Feature>>
    queryRenderedFeatures(const ScreenLineString& geometry,
                          const TransformState& transformState,
                          const std::vector<const RenderLayer*>& layers,
                          const RenderedQueryOptions& options,
                          const CollisionIndex& collisionIndex) const final;

    std::vector<Feature>
    querySourceFeatures(const SourceQueryOptions&) const final;

    void onLowMemory() final;
    void dumpDebugLogs() const final;

private:
    const style::RasterDEMSource::Impl& impl() const;

    TilePyramid tilePyramid;
    optional<std::vector<std::string>> tileURLTemplates;

protected:
    void onTileChanged(Tile&);
};

template <>
inline bool RenderSource::is<RenderRasterDEMSource>() const {
    return baseImpl->type == style::SourceType::RasterDEM;
}

} // namespace mbgl
