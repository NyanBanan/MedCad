//
// Created by nyanbanan on 03.05.2024.
//

#include "DensityWindowSliderWidget.hpp"

int DensityWindowSliderWidget::DensityWindowData::pixelSize() {
    return bottom_window_line - top_window_line;
}

DensityWindowSliderWidget::DensityWindowSliderWidget(QWidget* parent) : QWidget(parent), _font("Decorative", 7) {
    auto fmw = QFontMetrics(_font).tightBoundingRect(QString::number(_min_density)).width();
    setMinimumWidth(fmw + 20);
    setMaximumWidth(fmw + 20);

    setDensity(2048, -2048);
}

void DensityWindowSliderWidget::paintEvent(QPaintEvent* event) {
    QPainter painter{this};

    auto height = QWidget::height();
    _pix_in_density = height / (std::abs(_max_density) + std::abs(_min_density));
    auto streak_distance = _pix_in_density * 50;

    //    auto font_height = QFontMetrics(_font).height();

    auto curr_val = _max_density;
    int curr_streak_index = 0;
    for (auto curr_y = 0; curr_y <= height; curr_y += streak_distance) {
        if (curr_streak_index % 5 == 0) {
            painter.drawLine(0, curr_y, 15, curr_y);
            painter.drawText(16, curr_y, QString::number(curr_val));
            curr_val -= 250;
        } else {
            painter.drawLine(0, curr_y, _move_min_max_bar_height_level, curr_y);
        }
    }

    painter.setPen(QColor(20, 20, 140));
    painter.setBrush(QColor(20, 20, 140, 70));
    painter.drawRect(0, _window_data.bottom_window_line, 15, _window_data.pixelSize());

    painter.setPen(QColor(20, 20, 140));
    painter.setBrush(QColor(20, 20, 140, 70));
    painter.drawRect(0, _window_data.bottom_window_line, 15, _move_min_max_bar_height_level);
    painter.drawRect(0, _window_data.top_window_line, 15, _move_min_max_bar_height_level);
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
        case MOVE_WINDOW_SIZE: {
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
    auto new_center_y = _window_data.center_y + y;
    auto max_center_y = QWidget::height() - _window_data.pixelSize() / 2;
    auto min_center_y = _window_data.pixelSize() / 2;
    if (new_center_y > max_center_y) {
        _window_data.center_y = max_center_y;
    } else if (new_center_y < min_center_y) {
        _window_data.center_y = min_center_y;
    } else {
        _window_data.center_y = new_center_y;
    }
    updateDensity();
}

void DensityWindowSliderWidget::moveWindowSize(int y) {
    auto new_top = _window_data.top_window_line + y;
    auto new_bot = _window_data.bottom_window_line + y;

    new_top = new_top < 0 ? 0 : new_top;

    auto max_bottom = QWidget::height();

    new_bot = new_bot > max_bottom ? max_bottom : new_bot;

    DensityWindowData new_density{.center_y = _window_data.center_y,
                                  .bottom_window_line = new_bot,
                                  .top_window_line = new_top};
    if (new_density.pixelSize() < _min_level * _pix_in_density) {
        new_density.top_window_line = new_density.center_y - (int)std::ceil(_min_level / 2) * _pix_in_density;
        new_density.bottom_window_line = new_density.center_y + (int)std::ceil(_min_level / 2) * _pix_in_density;
    }

    _window_data = new_density;

    updateDensity();
}

void DensityWindowSliderWidget::moveWindowMin(int y) {
    updateDensity();
}

void DensityWindowSliderWidget::updateDensity() {
    _density_data.center_density = _max_density - _window_data.center_y / _pix_in_density;
    _density_data.size = _window_data.pixelSize() / _pix_in_density;
}

void DensityWindowSliderWidget::resizeEvent(QResizeEvent* event) {
    updatePixInDensity();
    QWidget::resizeEvent(event);
}

int DensityWindowSliderWidget::getPixelByDensity(int density) const {
    return density * _pix_in_density + _min_density;
}

DensityWindowSliderWidget::HoldType DensityWindowSliderWidget::getHoldType(int holded_y) {
    auto top_scale_bar_min_y = _window_data.center_y - _window_data.pixelSize() / 2;
    auto top_scale_bar_max_y = top_scale_bar_min_y + _move_min_max_bar_height_level;

    auto bottom_scale_bar_max_y = _window_data.center_y + _window_data.pixelSize() / 2;
    auto bottom_scale_bar_min_y = bottom_scale_bar_max_y - _move_min_max_bar_height_level;

    if ((holded_y >= top_scale_bar_min_y and holded_y <= top_scale_bar_max_y)
        or (holded_y >= bottom_scale_bar_min_y and holded_y <= bottom_scale_bar_max_y)) {
        return MOVE_WINDOW_SIZE;
    } else if (holded_y > top_scale_bar_max_y and holded_y < bottom_scale_bar_min_y) {
        return MOVE_WINDOW;
    } else {
        return NONE;
    }
}

void DensityWindowSliderWidget::setDensity(int max_density, int min_density) {
    _max_density = max_density;
    _min_density = min_density;
    updatePixInDensity();
}

void DensityWindowSliderWidget::updatePixInDensity() {
    _pix_in_density = QWidget::height() / (std::abs(_max_density) + std::abs(_min_density));
}
