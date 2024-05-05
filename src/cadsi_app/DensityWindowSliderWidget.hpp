//
// Created by nyanbanan on 03.05.2024.
//

#ifndef CADSI_DENSITYWINDOWSLIDERWIDGET_HPP
#define CADSI_DENSITYWINDOWSLIDERWIDGET_HPP

#include <QFont>
#include <QFontMetrics>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

class DensityWindowSliderWidget : public QWidget {
    Q_OBJECT

    enum HoldType {
        NONE,
        MOVE_WINDOW_SIZE,
        MOVE_WINDOW,
    };

    struct HoldData {
        int click_pos{0};
        HoldType click_type{NONE};
    };

    struct DensityWindowData {
        int center_y;
        int bottom_window_line;
        int top_window_line;

        int pixelSize();
    };

    struct DensityData {
        int center_density;
        int size;
    };

public:
    DensityWindowSliderWidget(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    void setDensity(int max_density, int min_density);
signals:
    void windowValueChanged(int windowValue);
    void levelValueChanged(int levelValue);

private:
    void moveWindow(int y);
    void moveWindowMin(int y);
    void moveWindowSize(int y);

    void updatePixInDensity();
    void updateDensity();

    int getPixelByDensity(int density) const;

    HoldType getHoldType(int holded_y);

    HoldData _hold_data;
    DensityWindowData _window_data;
    DensityData _density_data;

    QFont _font;

    int _pix_in_density;

    int _max_density{2048};
    int _min_density{-2048};

    static inline int _min_level{255};
    static inline int _move_min_max_bar_height_level{5};
};

#endif    //CADSI_DENSITYWINDOWSLIDERWIDGET_HPP
