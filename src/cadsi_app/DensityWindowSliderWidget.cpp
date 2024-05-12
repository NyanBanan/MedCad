//
// Created by nyanbanan on 03.05.2024.
//

#include "DensityWindowSliderWidget.hpp"

DensityWindowSliderWidget::DensityWindowSliderWidget(QWidget* parent) : QWidget(parent), _font("Decorative", 7) {
    setMaxMinDensity(2048, -2048);
    setDensityWindowSize(500);
    setDensityCenter(0);

    auto fmw = QFontMetrics(_font).tightBoundingRect(QString::number(_min_density)).width();
    setMinimumWidth(fmw + 20);
    setMaximumWidth(fmw + 20);

    _density_window_data.line_height = QFontMetrics(_font).tightBoundingRect(QString::number(_min_density)).height() * 2;
}

void DensityWindowSliderWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setFont(_font);

    updatePixInDensity();
    auto streak_distance = _pix_in_density * 50;

    auto curr_val = _max_density;
    double curr_y = _density_window_data.line_height;
    //TODO: Now density window render perfect but last value isn't displayed, maybe fix it in future
    for (; curr_val >= _min_density; curr_val -= 50) {
        if (curr_val % 250 == 0) {
            painter.drawLine(QPointF(0, curr_y), QPointF(15, curr_y));
            painter.drawText(QPointF(16, curr_y), QString::number(curr_val));
        } else {
            painter.drawLine(QPointF(0, curr_y), QPointF(_move_size_bar_height, curr_y));
        }
        curr_y += streak_distance;
    }

    painter.setPen(QColor(20, 20, 140));
    painter.setBrush(QColor(20, 20, 140, 70));
    painter.drawRect(QRectF(0, _density_window_data.top_window_line, 15, densityToPixelsNum(_density_data.size)));

    painter.setPen(QColor(20, 20, 140));
    painter.setBrush(QColor(20, 20, 140, 70));

    painter.drawRect(QRectF(0, _density_window_data.bottom_window_line, 15, _move_size_bar_height));
    painter.drawRect(QRectF(0, _density_window_data.top_window_line, 15, _move_size_bar_height));
}

void DensityWindowSliderWidget::mousePressEvent(QMouseEvent* event) {
    if (event->buttons() == Qt::LeftButton) {
        auto y = event->pos().y();
        _hold_data.click_pos = y;
        _hold_data.click_type = getHoldType(y);
    }
}

void DensityWindowSliderWidget::mouseReleaseEvent(QMouseEvent* event) {
    _hold_data.click_pos = 0;
    _hold_data.click_type = NONE;
}

void DensityWindowSliderWidget::mouseMoveEvent(QMouseEvent* event) {
    auto y = event->pos().y();
    switch (_hold_data.click_type) {
        case NONE: {
            break;
        }
        case MOVE_MIN_WINDOW_SIZE: {
            moveWindowSize(-(_hold_data.click_pos - y));
            break;
        }
        case MOVE_MAX_WINDOW_SIZE: {
            moveWindowSize(_hold_data.click_pos - y);
            break;
        }
        case MOVE_WINDOW: {
            moveWindow(_hold_data.click_pos - y);
            break;
        }
    }
    _hold_data.click_pos = event->pos().y();
}

void DensityWindowSliderWidget::moveWindow(int y) {
    auto new_density_center = _density_data.center + pixelsNumToDensity(y);
    setDensityCenter(new_density_center);
}

void DensityWindowSliderWidget::setDensityCenter(int center_density) {
    auto max_density_center = _max_density - _density_data.size / 2;
    auto min_density_center = _min_density + _density_data.size / 2;

    center_density = center_density >= max_density_center ? max_density_center : center_density;
    center_density = center_density <= min_density_center ? min_density_center : center_density;
    if (center_density != _density_data.center) {
        _density_data.center = center_density;
        updateDensityWindowData();
        centerDensityChanged(_density_data.center);
        update();
    }
}

void DensityWindowSliderWidget::moveWindowSize(int y) {
    auto new_size = _density_data.size + pixelsNumToDensity(y * 2);

    auto new_top = _density_window_data.top_window_line + y;
    auto new_bot = _density_window_data.bottom_window_line - y;

    double above_max = _density_window_data.line_height - new_top;

    auto max_bottom = QWidget::height() - _density_window_data.line_height;
    auto below_max_bottom = new_bot - max_bottom;

    bool new_center_required{false};
    int new_center{0};
    if (above_max > 0 && below_max_bottom > 0) {
        return;
    } else if (above_max > 0) {
        new_center = _density_data.center - pixelsNumToDensity(above_max);
        new_center_required = true;
    } else if (below_max_bottom > 0) {
        new_center = _density_data.center + pixelsNumToDensity(below_max_bottom);
        new_center_required = true;
    }

    setDensityWindowSize(new_size);
    if (new_center_required) {
        setDensityCenter(new_center);
    }
}

void DensityWindowSliderWidget::setDensityWindowSize(int new_size) {
    if (new_size < _min_level) {
        new_size = _min_level;
    } else if (new_size > _max_size) {
        new_size = _max_size;
    }
    if (new_size != _density_data.size) {
        _density_data.size = new_size;
        updateDensityWindowData();
        windowValueChanged(new_size);
        update();
    }
}

void DensityWindowSliderWidget::resizeEvent(QResizeEvent* event) {
    updatePixInDensity();
    QWidget::resizeEvent(event);
}

double DensityWindowSliderWidget::getPixelByDensity(int density) const {
    return (int)((_max_density - density) * _pix_in_density);
}

int DensityWindowSliderWidget::getDensityByPixel(double pixel) const {
    return (int)(_max_density - (pixel / _pix_in_density));
}

DensityWindowSliderWidget::HoldType DensityWindowSliderWidget::getHoldType(int holded_y) {
    auto top_scale_bar_min_y = _density_window_data.top_window_line;
    auto top_scale_bar_max_y = top_scale_bar_min_y + _move_size_bar_height;

    auto bottom_scale_bar_min_y = _density_window_data.bottom_window_line;
    auto bottom_scale_bar_max_y = bottom_scale_bar_min_y + _move_size_bar_height;

    if (holded_y >= bottom_scale_bar_min_y and holded_y <= bottom_scale_bar_max_y) {
        return MOVE_MIN_WINDOW_SIZE;
    } else if (holded_y >= top_scale_bar_min_y and holded_y <= top_scale_bar_max_y) {
        return MOVE_MAX_WINDOW_SIZE;
    } else if (holded_y > top_scale_bar_max_y and holded_y < bottom_scale_bar_min_y) {
        return MOVE_WINDOW;
    } else {
        return NONE;
    }
}

void DensityWindowSliderWidget::setMaxMinDensity(int max_density, int min_density) {
    _max_density = max_density;
    _min_density = min_density;
    _max_size = _max_density - _min_density;
    updatePixInDensity();
}

void DensityWindowSliderWidget::updatePixInDensity() {
    _pix_in_density = double(QWidget::height() - _density_window_data.line_height * 2) / (std::abs(_max_density) + std::abs(_min_density));
    updateDensityWindowData();
    update();
}

double DensityWindowSliderWidget::densityToPixelsNum(int density) const {
    return density * _pix_in_density;
}

int DensityWindowSliderWidget::pixelsNumToDensity(double pixels) const {
    return (int)(pixels / _pix_in_density);
}

void DensityWindowSliderWidget::updateDensityWindowData() {
    //I'm subtracting _move_min_max_bar_height_level so that the lower face is at the level of the lower value of the window
    _density_window_data.bottom_window_line = getPixelByDensity(_density_data.center - _density_data.size / 2)
                                              + _density_window_data.line_height - _move_size_bar_height;
    _density_window_data.top_window_line = getPixelByDensity(_density_data.center + _density_data.size / 2)
                                           + _density_window_data.line_height;
}
