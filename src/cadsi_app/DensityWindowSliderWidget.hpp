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
        MOVE_MAX_WINDOW_SIZE,
        MOVE_WINDOW,
        MOVE_MIN_WINDOW_SIZE,
    };

    struct HoldData {
        int click_pos{0};
        HoldType click_type{NONE};
    };

    struct DensityWindowData {
        double bottom_window_line{0};
        double top_window_line{0};
        uint line_height{0};
    };

    struct DensityData {
        int center{0};
        int size{0};
    };

public:
    DensityWindowSliderWidget(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    void setMaxMinDensity(int max_density, int min_density);
    uint getLineHeight();
public slots:
    void setDensityCenter(int center_density);
    void setDensityWindowSize(int new_size);
signals:
    void windowValueChanged(int windowValue);
    void centerDensityChanged(int levelValue);

private:
    void moveWindow(int y);
    void moveWindowSize(int y);

    void updatePixInDensity();
    void updateDensityWindowData();

    double getPixelByDensity(int density) const;
    int getDensityByPixel(double pixel) const;
    double densityToPixelsNum(int density) const;
    int pixelsNumToDensity(double pixels) const;

    HoldType getHoldType(int holded_y);

    HoldData _hold_data;
    DensityWindowData _density_window_data;
    DensityData _density_data;

    QFont _font;

    double _pix_in_density{0.0};

    int _max_density{0};
    int _min_density{0};
    int _max_size{0};

    static inline int _min_level{255};
    static inline int _move_size_bar_height{5};
};

#endif    //CADSI_DENSITYWINDOWSLIDERWIDGET_HPP
