#pragma once

#include <mbgl/renderer/render_layer.hpp>
#include <mbgl/style/layers/heatmap_layer_impl.hpp>
#include <mbgl/style/layers/heatmap_layer_properties.hpp>
#include <mbgl/util/optional.hpp>
#include <mbgl/util/offscreen_texture.hpp>
#include <mbgl/layout/circle_layout.hpp>

namespace mbgl {

class RenderHeatmapLayer: public RenderLayer {
public:
    RenderHeatmapLayer(Immutable<style::HeatmapLayer::Impl>);
    ~RenderHeatmapLayer() final = default;

    using StyleLayerImpl = style::HeatmapLayer::Impl;

    void transition(const TransitionParameters&) override;
    void evaluate(const PropertyEvaluationParameters&) override;
    bool hasTransition() const override;
    bool hasCrossfade() const override;
    void render(PaintParameters&, RenderSource*) override;

    style::HeatmapPaintProperties::PossiblyEvaluated paintProperties() const;

    bool queryIntersectsFeature(
            const GeometryCoordinates&,
            const GeometryTileFeature&,
            const float,
            const TransformState&,
            const float,
            const mat4&) const override;

    void updateColorRamp();

    std::unique_ptr<Layout> createLayout(const BucketParameters&, const std::vector<const RenderLayer*>&,
                                         std::unique_ptr<GeometryTileLayer>, GlyphDependencies&,
                                         ImageDependencies&) const override;
    // Paint properties
    style::HeatmapPaintProperties::Unevaluated unevaluated;
    style::HeatmapPaintProperties::PossiblyEvaluated evaluated;

    const style::HeatmapLayer::Impl& impl() const;

    PremultipliedImage colorRamp;
    optional<OffscreenTexture> renderTexture;
    optional<gl::Texture> colorRampTexture;
};

template <>
inline bool RenderLayer::is<RenderHeatmapLayer>() const {
    return type == style::LayerType::Heatmap;
}

} // namespace mbgl
