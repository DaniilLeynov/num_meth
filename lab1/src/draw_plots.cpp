#include "draw_plots.h"
#include <cstdio>
#include <fstream>
#include <iostream>
void draw_plots() {
    FILE* gnuplot = popen("gnuplot -persist", "w");

    if (!gnuplot) {
        std::cout << "Gnuplot not found!" << std::endl;
        return;
    }

    // Settings for plots
    fprintf(gnuplot, "set terminal pngcairo size %d,%d enhanced font 'Arial,%d'\n",
            PLOT_WIDTH, PLOT_HEIGHT, FONT_SIZE_LABEL);
    fprintf(gnuplot, "set output '%s'\n", FILE_MAIN_PLOT);
    fprintf(gnuplot, "set multiplot layout 1,2 title 'Interpolation Comparison' font 'Arial,%d'\n",
            FONT_SIZE_MAIN_TITLE);

    // First plot - uniform grid
    fprintf(gnuplot, "set xlabel 'x' font 'Arial,%d'\n", FONT_SIZE_LABEL);
    fprintf(gnuplot, "set ylabel 'f(x)' font 'Arial,%d'\n", FONT_SIZE_LABEL);
    fprintf(gnuplot, "set title 'Uniform Grid' font 'Arial,%d'\n", FONT_SIZE_TITLE);
    fprintf(gnuplot, "set grid lw %d\n", LINE_WIDTH_GRID);
    fprintf(gnuplot, "set key top right font 'Arial,%d'\n", FONT_SIZE_LEGEND);
    fprintf(gnuplot, "set tics font 'Arial,%d'\n", FONT_SIZE_TICS);
    fprintf(gnuplot, "plot '%s' using 1:2 with lines lw %d lt rgb '%s' title 'Exact function', \\\n",
            DATA_FILE, LINE_WIDTH_INTERP, COLOR_EXACT);
    fprintf(gnuplot, "     '%s' using 1:3 with lines lw %d lt rgb '%s' title 'Interpolation', \\\n",
            DATA_FILE, LINE_WIDTH_INTERP, COLOR_UNIFORM);
    fprintf(gnuplot, "     '%s' using 1:5 with points pt %d ps %.1f lt rgb '%s' title 'Nodes'\n",
            DATA_FILE, POINT_TYPE_UNIFORM, NODE_SIZE_MAIN, COLOR_UNIFORM);

    // Second plot - Chebyshev grid
    fprintf(gnuplot, "set title 'Chebyshev Grid' font 'Arial,%d'\n", FONT_SIZE_TITLE);
    fprintf(gnuplot, "plot '%s' using 1:2 with lines lw %d lt rgb '%s' title 'Exact function', \\\n",
            DATA_FILE, LINE_WIDTH_INTERP, COLOR_EXACT);
    fprintf(gnuplot, "     '%s' using 1:4 with lines lw %d lt rgb '%s' title 'Interpolation', \\\n",
            DATA_FILE, LINE_WIDTH_INTERP, COLOR_CHEB);
    fprintf(gnuplot, "     '%s' using 1:6 with points pt %d ps %.1f lt rgb '%s' title 'Nodes'\n",
            DATA_FILE, POINT_TYPE_CHEB, NODE_SIZE_MAIN, COLOR_CHEB);

    fprintf(gnuplot, "unset multiplot\n");

    // Create separate error plot
    fprintf(gnuplot, "set terminal pngcairo size %d,%d enhanced font 'Arial,%d'\n",
            ERROR_PLOT_WIDTH, ERROR_PLOT_HEIGHT, FONT_SIZE_LABEL);
    fprintf(gnuplot, "set output '%s'\n", FILE_ERROR_PLOT);
    fprintf(gnuplot, "set xlabel 'x' font 'Arial,%d'\n", FONT_SIZE_LABEL);
    fprintf(gnuplot, "set ylabel '|Error|' font 'Arial,%d'\n", FONT_SIZE_LABEL);
    fprintf(gnuplot, "set title 'Error Comparison' font 'Arial,%d'\n", FONT_SIZE_TITLE);
    fprintf(gnuplot, "set grid lw %d\n", LINE_WIDTH_GRID);
    fprintf(gnuplot, "set logscale y\n");
    fprintf(gnuplot, "set tics font 'Arial,%d'\n", FONT_SIZE_TICS);
    fprintf(gnuplot, "set key top right font 'Arial,%d'\n", FONT_SIZE_LEGEND);
    fprintf(gnuplot, "plot '%s' using 1:(abs($2-$3)) with lines lw %d lt rgb '%s' title 'Error (uniform)', \\\n",
            DATA_FILE, LINE_WIDTH_INTERP, COLOR_UNIFORM);
    fprintf(gnuplot, "     '%s' using 1:(abs($2-$4)) with lines lw %d lt rgb '%s' title 'Error (Chebyshev)'\n",
            DATA_FILE, LINE_WIDTH_INTERP, COLOR_CHEB);

    // Create comparison plot with all curves together
    fprintf(gnuplot, "set terminal pngcairo size %d,%d enhanced font 'Arial,%d'\n",
            COMPARISON_WIDTH, COMPARISON_HEIGHT, FONT_SIZE_LABEL);
    fprintf(gnuplot, "set output '%s'\n", FILE_COMPARISON);
    fprintf(gnuplot, "unset logscale y\n");
    fprintf(gnuplot, "set title 'Comparison of Exact Function and Interpolations' font 'Arial,%d'\n",
            FONT_SIZE_MAIN_TITLE);
    fprintf(gnuplot, "set xlabel 'x' font 'Arial,%d'\n", FONT_SIZE_LABEL);
    fprintf(gnuplot, "set ylabel 'f(x)' font 'Arial,%d'\n", FONT_SIZE_LABEL);
    fprintf(gnuplot, "set grid lw %d\n", LINE_WIDTH_GRID);
    fprintf(gnuplot, "set tics font 'Arial,%d'\n", FONT_SIZE_TICS);
    fprintf(gnuplot, "set key top right font 'Arial,%d'\n", FONT_SIZE_LEGEND);
    fprintf(gnuplot, "plot '%s' using 1:2 with lines lw %d lt rgb '%s' title 'Exact function', \\\n",
            DATA_FILE, LINE_WIDTH_EXACT, COLOR_EXACT);
    fprintf(gnuplot, "     '%s' using 1:3 with lines lw %d lt rgb '%s' title 'Uniform', \\\n",
            DATA_FILE, LINE_WIDTH_INTERP, COLOR_UNIFORM);
    fprintf(gnuplot, "     '%s' using 1:4 with lines lw %d lt rgb '%s' title 'Chebyshev', \\\n",
            DATA_FILE, LINE_WIDTH_INTERP, COLOR_CHEB);
    fprintf(gnuplot, "     '%s' using 1:5 with points pt %d ps %.1f lt rgb '%s' title 'Uniform nodes', \\\n",
            DATA_FILE, POINT_TYPE_UNIFORM, NODE_SIZE_COMPARISON, COLOR_UNIFORM);
    fprintf(gnuplot, "     '%s' using 1:6 with points pt %d ps %.1f lt rgb '%s' title 'Chebyshev nodes'\n",
            DATA_FILE, POINT_TYPE_CHEB, NODE_SIZE_COMPARISON, COLOR_CHEB);

    pclose(gnuplot);

    std::cout << " Plots saved to files:\n";
    std::cout << "   - " << FILE_MAIN_PLOT << " (" << PLOT_WIDTH << "x" << PLOT_HEIGHT << ")\n";
    std::cout << "   - " << FILE_ERROR_PLOT << " (" << ERROR_PLOT_WIDTH << "x" << ERROR_PLOT_HEIGHT << ")\n";
    std::cout << "   - " << FILE_COMPARISON << " (" << COMPARISON_WIDTH << "x" << COMPARISON_HEIGHT << ")\n";
}
