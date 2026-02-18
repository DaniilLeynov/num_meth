#ifndef DRAW_PLOTS
#define DRAW_PLOTS

constexpr const char* DATA_FILE = "data/interpolation_data.txt";
constexpr int PLOT_WIDTH = 1920;
constexpr int PLOT_HEIGHT = 1080;
constexpr int ERROR_PLOT_WIDTH = 1600;
constexpr int ERROR_PLOT_HEIGHT = 900;
constexpr int COMPARISON_WIDTH = 1920;
constexpr int COMPARISON_HEIGHT = 1200;


constexpr double NODE_SIZE_MAIN = 3.0;
constexpr double NODE_SIZE_COMPARISON = 3.5;


constexpr int LINE_WIDTH_EXACT = 4;
constexpr int LINE_WIDTH_INTERP = 3;
constexpr int LINE_WIDTH_GRID = 2;


constexpr int POINT_TYPE_UNIFORM = 7;
constexpr int POINT_TYPE_CHEB = 9;


constexpr const char* COLOR_EXACT = "#000000";
constexpr const char* COLOR_UNIFORM = "#FF0000";
constexpr const char* COLOR_CHEB = "#0000FF";


constexpr int FONT_SIZE_TITLE = 16;
constexpr int FONT_SIZE_LABEL = 14;
constexpr int FONT_SIZE_TICS = 12;
constexpr int FONT_SIZE_LEGEND = 12;
constexpr int FONT_SIZE_MAIN_TITLE = 18;


constexpr const char* FILE_MAIN_PLOT = "plots/interpolation_plot.png";
constexpr const char* FILE_ERROR_PLOT = "plots/error_plot.png";
constexpr const char* FILE_COMPARISON = "plots/comparison_all.png";

void draw_plots();

#endif
