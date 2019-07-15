cmake_minimum_required(VERSION 3.10.2)
project(portals_debug)

##############################################################################
# ENABLE WHEN DEBUG
set(CMAKE_BUILD_TYPE Debug)
##############################################################################

set_property(GLOBAL PROPERTY CXX_STANDARD 17)

#-----------------------------------------------------------------------------
# Set here your code locations
set(MY_STB_DIR ~/my/portals_project/my_stb)                 # https://github.com/nothings/stb + my_stb (see below)
set(EASYBMP_DIR ~/my/portals_project/EasyBMP)               # https://sourceforge.net/projects/easybmp/
set(TWG_IMAGE_DIR ~/my/portals_project/twg_image)           # Not published
set(AGG_DIR ~/my/portals_project/agg-2.5)                   # http://antigrain.com/
set(COLOR_DIR ~/my/portals_project/color)                   # https://github.com/dmilos/color
set(GIF_DIR ~/my/portals_project/gif-h)                     # https://github.com/ginsweater/gif-h
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# my_stb lib:
# my_stb/
#   include/
#     stb_image.h       # from original repo
#     stb_image_write.h # from original repo
#   src/
#     stb_image.cpp:
#       #define STB_IMAGE_IMPLEMENTATION
#       #define STBI_MSC_SECURE_CRT
#       #include <stb_image.h>
#     stb_image_write.cpp:
#       #define STB_IMAGE_WRITE_IMPLEMENTATION
#       #define STBI_MSC_SECURE_CRT
#       #include <stb_image_write.h>
# It maked because I used stb in many projects and got link errors
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
find_package(Freetype REQUIRED) # sudo apt install libfreetype6-dev
include_directories(${FREETYPE_INCLUDE_DIRS})
link_libraries(${FREETYPE_LIBRARIES})
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
add_library(my_stb STATIC 
	${MY_STB_DIR}/src/stb_image.cpp 
	${MY_STB_DIR}/src/stb_image_write.cpp

	${MY_STB_DIR}/include/stb_image.h
	${MY_STB_DIR}/include/stb_image_write.h
)
include_directories(${MY_STB_DIR}/include)
link_libraries(my_stb)
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
add_library(easybmp STATIC 
	${EASYBMP_DIR}/EasyBMP.cpp 

	${EASYBMP_DIR}/EasyBMP.h
	${EASYBMP_DIR}/EasyBMP_DataStructures.h
	${EASYBMP_DIR}/EasyBMP_BMP.h
	${EASYBMP_DIR}/EasyBMP_VariousBMPutilities.h
)
include_directories(${EASYBMP_DIR}/)
link_libraries(easybmp)
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
include_directories(${COLOR_DIR}/src)
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
add_library(agg STATIC 
	${AGG_DIR}/src/agg_vpgen_clip_polygon.cpp
	${AGG_DIR}/src/agg_vpgen_clip_polyline.cpp
	${AGG_DIR}/src/agg_line_aa_basics.cpp
	${AGG_DIR}/src/agg_vpgen_segmentator.cpp
	${AGG_DIR}/src/agg_arrowhead.cpp
	${AGG_DIR}/src/agg_sqrt_tables.cpp
	${AGG_DIR}/src/agg_vcgen_stroke.cpp
	${AGG_DIR}/src/agg_gsv_text.cpp
	${AGG_DIR}/src/agg_rounded_rect.cpp
	${AGG_DIR}/src/agg_embedded_raster_fonts.cpp
	${AGG_DIR}/src/agg_bspline.cpp
	${AGG_DIR}/src/agg_vcgen_smooth_poly1.cpp
	${AGG_DIR}/src/agg_trans_double_path.cpp
	${AGG_DIR}/src/agg_image_filters.cpp
	${AGG_DIR}/src/agg_vcgen_markers_term.cpp
	${AGG_DIR}/src/agg_vcgen_bspline.cpp
	${AGG_DIR}/src/agg_trans_affine.cpp
	${AGG_DIR}/src/agg_trans_warp_magnifier.cpp
	${AGG_DIR}/src/agg_line_profile_aa.cpp
	${AGG_DIR}/src/agg_bezier_arc.cpp
	${AGG_DIR}/src/agg_trans_single_path.cpp
	${AGG_DIR}/src/agg_arc.cpp
	${AGG_DIR}/src/agg_curves.cpp
	${AGG_DIR}/src/agg_vcgen_contour.cpp
	${AGG_DIR}/src/agg_vcgen_dash.cpp

	${AGG_DIR}/src/ctrl/agg_spline_ctrl.cpp
	${AGG_DIR}/src/ctrl/agg_rbox_ctrl.cpp
	${AGG_DIR}/src/ctrl/agg_gamma_ctrl.cpp
	${AGG_DIR}/src/ctrl/agg_gamma_spline.cpp
	${AGG_DIR}/src/ctrl/agg_slider_ctrl.cpp
	${AGG_DIR}/src/ctrl/agg_cbox_ctrl.cpp
	${AGG_DIR}/src/ctrl/agg_bezier_ctrl.cpp
	${AGG_DIR}/src/ctrl/agg_polygon_ctrl.cpp
	${AGG_DIR}/src/ctrl/agg_scale_ctrl.cpp

	${AGG_DIR}/gpc/gpc.c
	${AGG_DIR}/font_freetype/agg_font_freetype.cpp

	# include
	${AGG_DIR}/gpc/gpc.h
	${AGG_DIR}/font_freetype/agg_font_freetype.h
	${AGG_DIR}/include/agg_renderer_markers.h
	${AGG_DIR}/include/agg_path_length.h
	${AGG_DIR}/include/agg_conv_concat.h
	${AGG_DIR}/include/agg_path_storage.h
	${AGG_DIR}/include/agg_span_pattern_rgba.h
	${AGG_DIR}/include/agg_renderer_raster_text.h
	${AGG_DIR}/include/agg_span_interpolator_trans.h
	${AGG_DIR}/include/agg_trans_bilinear.h
	${AGG_DIR}/include/agg_trans_warp_magnifier.h
	${AGG_DIR}/include/agg_pixfmt_transposer.h
	${AGG_DIR}/include/agg_glyph_raster_bin.h
	${AGG_DIR}/include/agg_span_image_filter_rgb.h
	${AGG_DIR}/include/agg_conv_close_polygon.h
	${AGG_DIR}/include/agg_bezier_arc.h
	${AGG_DIR}/include/agg_shorten_path.h
	${AGG_DIR}/include/agg_conv_unclose_polygon.h
	${AGG_DIR}/include/agg_scanline_u.h
	${AGG_DIR}/include/agg_vcgen_stroke.h
	${AGG_DIR}/include/agg_math_stroke.h
	${AGG_DIR}/include/agg_span_image_filter.h
	${AGG_DIR}/include/agg_gamma_lut.h
	${AGG_DIR}/include/agg_rasterizer_outline.h
	${AGG_DIR}/include/agg_span_gouraud_rgba.h
	${AGG_DIR}/include/agg_span_interpolator_persp.h
	${AGG_DIR}/include/agg_conv_curve.h
	${AGG_DIR}/include/agg_renderer_outline_aa.h
	${AGG_DIR}/include/agg_vcgen_markers_term.h
	${AGG_DIR}/include/agg_renderer_scanline.h
	${AGG_DIR}/include/agg_span_subdiv_adaptor.h
	${AGG_DIR}/include/agg_conv_marker.h
	${AGG_DIR}/include/agg_vcgen_vertex_sequence.h
	${AGG_DIR}/include/agg_span_interpolator_linear.h
	${AGG_DIR}/include/ctrl/agg_cbox_ctrl.h
	${AGG_DIR}/include/ctrl/agg_ctrl.h
	${AGG_DIR}/include/ctrl/agg_scale_ctrl.h
	${AGG_DIR}/include/ctrl/agg_spline_ctrl.h
	${AGG_DIR}/include/ctrl/agg_gamma_spline.h
	${AGG_DIR}/include/ctrl/agg_polygon_ctrl.h
	${AGG_DIR}/include/ctrl/agg_slider_ctrl.h
	${AGG_DIR}/include/ctrl/agg_rbox_ctrl.h
	${AGG_DIR}/include/ctrl/agg_gamma_ctrl.h
	${AGG_DIR}/include/ctrl/agg_bezier_ctrl.h
	${AGG_DIR}/include/agg_scanline_p.h
	${AGG_DIR}/include/agg_bitset_iterator.h
	${AGG_DIR}/include/agg_rendering_buffer_dynarow.h
	${AGG_DIR}/include/agg_conv_adaptor_vpgen.h
	${AGG_DIR}/include/agg_span_gradient_alpha.h
	${AGG_DIR}/include/agg_span_solid.h
	${AGG_DIR}/include/agg_rasterizer_sl_clip.h
	${AGG_DIR}/include/agg_pattern_filters_rgba.h
	${AGG_DIR}/include/agg_span_image_filter_gray.h
	${AGG_DIR}/include/util/agg_color_conv_rgb16.h
	${AGG_DIR}/include/util/agg_color_conv_rgb8.h
	${AGG_DIR}/include/util/agg_color_conv.h
	${AGG_DIR}/include/agg_blur.h
	${AGG_DIR}/include/agg_span_gouraud.h
	${AGG_DIR}/include/agg_trans_perspective.h
	${AGG_DIR}/include/agg_ellipse_bresenham.h
	${AGG_DIR}/include/agg_pixfmt_gray.h
	${AGG_DIR}/include/agg_conv_clip_polygon.h
	${AGG_DIR}/include/agg_span_image_filter_rgba.h
	${AGG_DIR}/include/agg_alpha_mask_u8.h
	${AGG_DIR}/include/agg_color_rgba.h
	${AGG_DIR}/include/agg_vpgen_clip_polyline.h
	${AGG_DIR}/include/agg_span_gouraud_gray.h
	${AGG_DIR}/include/agg_pixfmt_rgb_packed.h
	${AGG_DIR}/include/agg_basics.h
	${AGG_DIR}/include/agg_rendering_buffer.h
	${AGG_DIR}/include/agg_rasterizer_outline_aa.h
	${AGG_DIR}/include/agg_embedded_raster_fonts.h
	${AGG_DIR}/include/agg_scanline_boolean_algebra.h
	${AGG_DIR}/include/agg_trans_double_path.h
	${AGG_DIR}/include/agg_pixfmt_rgba.h
	${AGG_DIR}/include/agg_vertex_sequence.h
	${AGG_DIR}/include/platform/mac/agg_mac_pmap.h
	${AGG_DIR}/include/platform/win32/agg_win32_bmp.h
	${AGG_DIR}/include/platform/agg_platform_support.h
	${AGG_DIR}/include/agg_color_gray.h
	${AGG_DIR}/include/agg_scanline_storage_aa.h
	${AGG_DIR}/include/agg_path_storage_integer.h
	${AGG_DIR}/include/agg_pixfmt_amask_adaptor.h
	${AGG_DIR}/include/agg_rasterizer_compound_aa.h
	${AGG_DIR}/include/agg_trans_viewport.h
	${AGG_DIR}/include/agg_trans_affine.h
	${AGG_DIR}/include/agg_clip_liang_barsky.h
	${AGG_DIR}/include/agg_conv_gpc.h
	${AGG_DIR}/include/agg_rounded_rect.h
	${AGG_DIR}/include/agg_renderer_mclip.h
	${AGG_DIR}/include/agg_curves.h
	${AGG_DIR}/include/agg_span_allocator.h
	${AGG_DIR}/include/agg_vcgen_bspline.h
	${AGG_DIR}/include/agg_span_converter.h
	${AGG_DIR}/include/agg_renderer_outline_image.h
	${AGG_DIR}/include/agg_conv_clip_polyline.h
	${AGG_DIR}/include/agg_vcgen_dash.h
	${AGG_DIR}/include/agg_simul_eq.h
	${AGG_DIR}/include/agg_pixfmt_rgb.h
	${AGG_DIR}/include/agg_bounding_rect.h
	${AGG_DIR}/include/agg_font_cache_manager.h
	${AGG_DIR}/include/agg_gsv_text.h
	${AGG_DIR}/include/agg_span_gradient.h
	${AGG_DIR}/include/agg_conv_shorten_path.h
	${AGG_DIR}/include/agg_conv_contour.h
	${AGG_DIR}/include/agg_rasterizer_cells_aa.h
	${AGG_DIR}/include/agg_ellipse.h
	${AGG_DIR}/include/agg_gradient_lut.h
	${AGG_DIR}/include/agg_arc.h
	${AGG_DIR}/include/agg_conv_adaptor_vcgen.h
	${AGG_DIR}/include/agg_renderer_base.h
	${AGG_DIR}/include/agg_vpgen_segmentator.h
	${AGG_DIR}/include/agg_conv_transform.h
	${AGG_DIR}/include/agg_arrowhead.h
	${AGG_DIR}/include/agg_vcgen_contour.h
	${AGG_DIR}/include/agg_scanline_bin.h
	${AGG_DIR}/include/agg_math.h
	${AGG_DIR}/include/agg_span_pattern_rgb.h
	${AGG_DIR}/include/agg_conv_marker_adaptor.h
	${AGG_DIR}/include/agg_bspline.h
	${AGG_DIR}/include/agg_span_interpolator_adaptor.h
	${AGG_DIR}/include/agg_renderer_primitives.h
	${AGG_DIR}/include/agg_conv_segmentator.h
	${AGG_DIR}/include/agg_gamma_functions.h
	${AGG_DIR}/include/agg_vcgen_smooth_poly1.h
	${AGG_DIR}/include/agg_vpgen_clip_polygon.h
	${AGG_DIR}/include/agg_scanline_storage_bin.h
	${AGG_DIR}/include/agg_conv_stroke.h
	${AGG_DIR}/include/agg_rasterizer_scanline_aa.h
	${AGG_DIR}/include/agg_line_aa_basics.h
	${AGG_DIR}/include/agg_image_accessors.h
	${AGG_DIR}/include/agg_array.h
	${AGG_DIR}/include/agg_conv_smooth_poly1.h
	${AGG_DIR}/include/agg_span_pattern_gray.h
	${AGG_DIR}/include/agg_trans_single_path.h
	${AGG_DIR}/include/agg_dda_line.h
	${AGG_DIR}/include/agg_config.h
	${AGG_DIR}/include/agg_conv_dash.h
	${AGG_DIR}/include/agg_conv_bspline.h
	${AGG_DIR}/include/agg_image_filters.h
)
include_directories(${AGG_DIR}/include ${AGG_DIR}/font_freetype ${AGG_DIR}/gpc)
link_libraries(agg)
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
add_library(gif STATIC 
	${GIF_DIR}/gif.h
)
include_directories(${GIF_DIR})
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
add_library(twg_image STATIC 
	${TWG_IMAGE_DIR}/src/basics.cpp 
	${TWG_IMAGE_DIR}/src/color.cpp 
	${TWG_IMAGE_DIR}/src/image.cpp
	${TWG_IMAGE_DIR}/src/image_agg.cpp
	${TWG_IMAGE_DIR}/src/image_drawing_aa.cpp
	${TWG_IMAGE_DIR}/src/polygon_d.cpp 

	${TWG_IMAGE_DIR}/include/twg/twg.h
	${TWG_IMAGE_DIR}/include/twg/image.h
	${TWG_IMAGE_DIR}/include/twg/image/image_drawing.h
	${TWG_IMAGE_DIR}/include/twg/image/image_agg.h
	${TWG_IMAGE_DIR}/include/twg/basics.h
	${TWG_IMAGE_DIR}/include/twg/point.h
	${TWG_IMAGE_DIR}/include/twg/color.h
)
include_directories(${TWG_IMAGE_DIR}/include)
link_libraries(twg_image)
#-----------------------------------------------------------------------------

# Replace DEBUG to RELEASE if needed

add_executable(rgb_formulae_DEBUG ${TWG_IMAGE_DIR}/examples/rgb_formulae.cpp)
add_executable(fractal_on_line_DEBUG ${TWG_IMAGE_DIR}/examples/fractal_on_line.cpp)